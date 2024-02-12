#include <iostream>
using namespace std;

typedef struct pax  //define pacman class
{
    char charachter;
    int i;
    int j;
    int point;
    char direction;
    int state;
}pax;

typedef struct ghost  //define ghost class
{
    char charachter;
    int i;
    int j;
    char direction;
}ghost;

typedef struct ground  //define playground class
{
    char ** coords;
    int hight;
    int length;
    int wpoint;
}ground;

void Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int extract_map_from_file(pax * ppacman,ground * pground,ghost * list_of_ghosts,int which,char Uname[60])
{
    FILE* file = fopen(Uname, "r");
    char tmp[60];
    int check;
    int level;
    fread(tmp,60,1,file);
    fread(tmp,60,1,file);
    fread(&level,sizeof(int),1,file);
    fread(&check,sizeof(int),1,file); // is there any unfinished game?

    if (which==2 or !check) //if no unfinished game or player wants to play a new game
    {
        fclose(file);
        int random_map = rand() % 3;
        
        if (random_map == 0)
        {
            file = fopen("map1.bin", "r"); 
        }
        else if(random_map == 1)
        {
            file = fopen("map2.bin", "r"); 
        }
        else
        {
            file = fopen("map3.bin", "r"); 
        }
        
        int j;
        int i;
        fread(&i,sizeof(int),1,file);
        fread(&j,sizeof(int),1,file);
        pground->coords=(char **)malloc(sizeof(char *)*j);
        pground->hight=j;
        pground->length=i;
        int n_ghosts=0;
        for (int x = 0; x < j; x++)
        {
            pground->coords[x] = (char *)malloc(i);
            for (int y = 0; y < i; y++)
            {
                fread(&pground->coords[x][y],1,1,file);
                
                if (pground->coords[x][y]=='|' or pground->coords[x][y]=='-')
                {
                    pground->coords[x][y]='#';
                }
                else if (pground->coords[x][y]==' ')
                {
                    pground->coords[x][y]==' ';
                }
                else if (pground->coords[x][y]=='@')
                {
                    pground->coords[x][y]==' ';
                    ppacman->i=x;
                    ppacman->j=y;
                }
                else if (pground->coords[x][y]=='.')
                {
                    pground->coords[x][y]='o';
                    (pground->wpoint)++;
                }
                else if (pground->coords[x][y]=='G')
                {
                    pground->coords[x][y]=' ';
                    list_of_ghosts[n_ghosts].i=x;
                    list_of_ghosts[n_ghosts].j=y;
                    list_of_ghosts[n_ghosts].direction='d';
                    list_of_ghosts[n_ghosts].charachter='G';
                    n_ghosts++;
                }
            }
        }
        if (n_ghosts==1)
        {
            list_of_ghosts[n_ghosts].i=-1;
        }
        return level;
    }
    else //if you have an unfinished game and you wanna finish that
    {
        
        int j;
        int i;
        
        fread(&i,sizeof(int),1,file);
        fread(&j,sizeof(int),1,file);
        pground->coords=(char **)malloc(sizeof(char *)*j);
        pground->hight=j;
        pground->length=i;
        int n_ghosts=0;
        for (int x = 0; x < j; x++)
        {
            pground->coords[x] = (char *)malloc(i);
            for (int y = 0; y < i; y++)
            {
                fread(&pground->coords[x][y],1,1,file);
                
                if (pground->coords[x][y]=='|' or pground->coords[x][y]=='-')
                {
                    pground->coords[x][y]='#';
                }
                else if (pground->coords[x][y]=='@')
                {
                    pground->coords[x][y]=' ';
                    ppacman->i=x;
                    ppacman->j=y;
                }
                else if (pground->coords[x][y]=='.')
                {
                    pground->coords[x][y]='o';
                    (pground->wpoint)++;
                }
                else if (pground->coords[x][y]==' ')
                {
                    pground->coords[x][y]=' ';
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            fread(&list_of_ghosts[i].i,sizeof(int),1,file);
            fread(&list_of_ghosts[i].j,sizeof(int),1,file);
            list_of_ghosts[i].direction='d';
            list_of_ghosts[i].charachter='G';
            n_ghosts++;
        }
        
        if (n_ghosts==1)
        {
            list_of_ghosts[n_ghosts].i=-1;
        }
        fclose(file);
        return level;
    }
    
}

char getUserInput() 
{
    char key;
    //Sleep(300);
    if (_kbhit())   //check is there pressed key 
    {
        key=getch();    //read pressed key 
        fflush(stdin);  //and clear input buffer
        return key;
    }
    return '\0';
}

int move_point_achive_death(ground * pground,pax * ppacman,ghost * list_of_ghosts)
{
    char move = getUserInput();

    //is pressed key valid?
    if (move and move == 'w' or move == 'W' or move == 's' or move == 'S' or move == 'a' or move == 'A' or move == 'd' or move == 'D')
    {

    }
    else if(move == 27)
    {
        //pressed key is escape key
        return -1;
    }
    else
    {
        //if key is not valid, pacman will go on his way
        move=ppacman->direction;
    }
    
    if (move == 'w' or move == 'W')
    {
        if(pground->coords[ppacman->i-1][ppacman->j] != '#')  //check for wall
        {
            
            if ((list_of_ghosts[0].i == ppacman->i-1 and list_of_ghosts[0].j == ppacman->j) or (list_of_ghosts[1].i == ppacman->i-1 and list_of_ghosts[1].j == ppacman->j) and !ppacman->state)  //check for coin
            {
                return 0;
            }
            else if (pground->coords[ppacman->i-1][ppacman->j] == 'o')
            {
                (ppacman->point)++;
            }
            else if (pground->coords[ppacman->i-1][ppacman->j] == 'P')  //check for energy
            {
                pground->coords[ppacman->i-1][ppacman->j] = ' ';
                ppacman->state=7;
            }
            
            pground->coords[ppacman->i][ppacman->j] = ' ';
            (ppacman->i)--;
            ppacman->direction=move;
        }
    }
    else if (move == 's' or move == 'S')
    {
        
        if(pground->coords[ppacman->i+1][ppacman->j] != '#')
        {

            if ((list_of_ghosts[0].i == ppacman->i+1 and list_of_ghosts[0].j == ppacman->j) or (list_of_ghosts[1].i == ppacman->i+1 and list_of_ghosts[1].j == ppacman->j) and !ppacman->state)
            {
                return 0;
            }

            else if (pground->coords[ppacman->i+1][ppacman->j] == 'o')
            {
                (ppacman->point)++;
            }
            
            else if (pground->coords[ppacman->i+1][ppacman->j] == 'P')
            {
                pground->coords[ppacman->i+1][ppacman->j] = ' ';
                ppacman->state=7;
            }
            pground->coords[ppacman->i][ppacman->j] = ' ';
            (ppacman->i)++;
            ppacman->direction=move;
        }
    }
    else if (move == 'a' or move == 'A')
    {
        if(pground->coords[ppacman->i][ppacman->j-1] != '#')
        {

            if ((list_of_ghosts[0].i == ppacman->i and list_of_ghosts[0].j == ppacman->j-1) or (list_of_ghosts[1].i == ppacman->i and list_of_ghosts[1].j == ppacman->j-1) and !ppacman->state)
            {
                return 0;
            }

            else if (pground->coords[ppacman->i][ppacman->j-1] == 'o')
            {
                (ppacman->point)++;
            }
            
            else if (pground->coords[ppacman->i][ppacman->j-1] == 'P')
            {
                pground->coords[ppacman->i][ppacman->j-1] = ' ';
                ppacman->state=7;
            }
            pground->coords[ppacman->i][ppacman->j] = ' ';
            (ppacman->j)--;
            ppacman->direction=move;
        }
    }
    else if (move == 'd' or move == 'D')
    { 
       if(pground->coords[ppacman->i][ppacman->j+1] != '#')
        {
            if ((list_of_ghosts[0].i == ppacman->i and list_of_ghosts[0].j == ppacman->j+1) or (list_of_ghosts[1].i == ppacman->i and list_of_ghosts[1].j == ppacman->j+1) and !ppacman->state)
            {
                return 0;
            }

            else if (pground->coords[ppacman->i][ppacman->j+1] == 'o')
            {
                (ppacman->point)++;
            }
            
            else if (pground->coords[ppacman->i][ppacman->j+1] == 'P')
            {
                pground->coords[ppacman->i][ppacman->j+1] = ' ';
                ppacman->state=7;
            }
            pground->coords[ppacman->i][ppacman->j] = ' ';
            (ppacman->j)++;
            ppacman->direction=move;
        }
    }
    if (ppacman->state>0)  //if you eat energy, one move reduce your energy
    {
        ppacman->state--;
    }
    
    return 1;
}

void refresh(pax * ppacman,ground * pground,ghost * list_of_ghost)
{
    //characters for 2D playground
    char pacr[5][8] = {"   +   "," +++o+ ","+++++  "," +++++ ","   +   "};
    char pacl[5][8] = {"   +   "," +o+++ ","  +++++"," +++++ ","   +   "};
    char pacd[5][8] = {"   +   "," +++++ ","+++++++"," o+ ++ ","       "};
    char pacu[5][8] = {"       "," o+ ++ ","+++++++"," +++++ ","   +   "};
    char ghosty[5][8] = {" +++++ "," +o+o+ "," +++++ "," +++++ "," + + + "};
    char coin[5][8] = {"       ","  +++  "," +   + ","  +++  ","       "};
    char cherry[5][8] = {"       ","   +   ","  / \\  ","  O O  ","       "};
    char wall[5][8] = {"#######","#######","#######","#######","#######"};
    char space[5][8] = {"       ","       ","       ","       ","       "};


    //print characters in a beautiful way with a perfect algorithm!
    for (int i = 0; i < pground->hight; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            for (int j = 0; j< pground->length; j++)
            {
                if (ppacman->i == i and ppacman->j == j)
                {
                    Color(14);
                    if (ppacman->direction == 'w')
                    {
                        cout<<pacu[k];
                    }
                    else if (ppacman->direction == 'a')
                    {
                        cout<<pacl[k];
                    }
                    else if (ppacman->direction == 's')
                    {
                        cout<<pacd[k];
                    }
                    else
                    {
                        cout<<pacr[k];
                    }
                }
                else if (i==list_of_ghost[0].i and j==list_of_ghost[0].j or i==list_of_ghost[1].i and j==list_of_ghost[1].j)
                {
                    Color(13);
                    cout<<ghosty[k];
                }
                else if (pground->coords[i][j]=='#')
                {
                    Color(10);
                    cout<<wall[k];
                }
                else if (pground->coords[i][j]=='o')
                {
                    Color(6);
                    cout<<coin[k];
                }
                else if (pground->coords[i][j]=='P')
                {
                    Color(12);
                    cout<<cherry[k];
                }
                else
                {
                    cout<<space[k];
                }
                
            }
            cout<<'\n';
        }
        
    }
    Color(15);
    cout<<"\npress Esc to exit";
    cout<<"\nmoves to normal mode : "<<ppacman->state;
    Sleep(250);
}

char choose_way(ghost ghosty,ground * pground)
{
    //check  available ways and choose one of them for ghosts
    int ways=0;
    char lways[4];
    if (pground->coords[ghosty.i+1][ghosty.j]!='#')
    {
        lways[ways]='s';
        ways++;
    }
    if (pground->coords[ghosty.i-1][ghosty.j]!='#')
    {
        lways[ways]='w';
        ways++;
    }
    if (pground->coords[ghosty.i][ghosty.j+1]!='#')
    {
        lways[ways]='d';
        ways++;
    }
    if (pground->coords[ghosty.i][ghosty.j-1]!='#')
    {
        lways[ways]='a';
        ways++;
    }
    
    return lways[rand()%ways];
}

int dancing_ghosts(pax * pacman,ghost * list_of_ghosts,ground * pground)
{
    int iswall=0;  //there is a wall bitween pacman and ghost
    int not_in_line_flag; //pacman is not in a line with ghost
    char newway;  //what is new way for ghost
    static int move_counter[2]={0,0};  //change diraction if you are moving in a stright line for 2 or more moves
    //chasing paxman
    for (int c = 0; c < 2; c++)
    {
        newway=0;
        iswall=0;
        not_in_line_flag=1; 
        if (list_of_ghosts[c].i==-1)
        {
            break;
        }
        
        if (list_of_ghosts[c].i == pacman->i)
        {
            if (list_of_ghosts[c].j < pacman->j)
            {
                for (int j = list_of_ghosts[c].j; j <= pacman->j; j++)
                {
                    if (pground->coords[pacman->i][j]=='#')
                    {
                        iswall=1;
                        break;
                    }
                }
            }
            else if (list_of_ghosts[c].j > pacman->j)
            {
                for (int j = pacman->j; j <= list_of_ghosts[c].j; j++)
                {
                    if (pground->coords[pacman->i][j]=='#')
                    {
                        iswall=1;
                        break;
                    }
                }
            }
            
            if (!iswall)
            {
                move_counter[c]=0;
                if (!pacman->state)
                {
                    
                    if ((list_of_ghosts[c].j)-(pacman->j)<0 and list_of_ghosts[c].direction=='d')
                    {
                        list_of_ghosts[c].j++;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                    else if ((list_of_ghosts[c].j)-(pacman->j)>0 and list_of_ghosts[c].direction=='a')
                    {
                        list_of_ghosts[c].j--;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                }
                else
                {
                    if ((list_of_ghosts[c].j)-(pacman->j)<0 and pground->coords[list_of_ghosts[c].i][list_of_ghosts[c].j-1] != '#')
                    {
                        list_of_ghosts[c].j--;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                    else if ((list_of_ghosts[c].j)-(pacman->j)>0 and pground->coords[list_of_ghosts[c].i][list_of_ghosts[c].j+1] != '#')
                    {
                        list_of_ghosts[c].j++;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                }
            }
        }
        else if (list_of_ghosts[c].j == pacman->j)
        {
            if (list_of_ghosts[c].i < pacman->i)
            {
                for (int i = list_of_ghosts[c].i; i <= pacman->i; i++)
                {
                    if (pground->coords[i][pacman->j]=='#')
                    {
                        iswall=1;
                        break;
                    }
                }
            }
            else if (list_of_ghosts[c].j > pacman->j)
            {
                for (int i = pacman->i; i <= list_of_ghosts[c].i; i++)
                {
                    if (pground->coords[i][pacman->j]=='#')
                    {
                        iswall=1;
                        break;
                    }
                }
            }

            if (!iswall)
            {
                
                if (!pacman->state)
                {
                    if ((list_of_ghosts[c].i)-(pacman->i)<0 and list_of_ghosts[c].direction=='s')
                    {
                        list_of_ghosts[c].i++;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                    else if ((list_of_ghosts[c].j)-(pacman->j)>0 and list_of_ghosts[c].direction=='w')
                    {
                        list_of_ghosts[c].i--;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                }
                else
                {
                    if ((list_of_ghosts[c].i)-(pacman->i)<0 and pground->coords[list_of_ghosts[c].i-1][list_of_ghosts[c].j] != '#')
                    {
                        list_of_ghosts[c].i--;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                    else if ((list_of_ghosts[c].j)-(pacman->j)>0 and pground->coords[list_of_ghosts[c].i+1][list_of_ghosts[c].j] != '#')
                    {
                        list_of_ghosts[c].i++;
                        not_in_line_flag=0;
                        move_counter[c]=0;
                    }
                }
            }
        }
        if (not_in_line_flag)
        {
            if (list_of_ghosts[c].direction=='a')
            {
                if (pground->coords[list_of_ghosts[c].i][list_of_ghosts[c].j-1]!='#' and move_counter[c]<3)
                {
                    list_of_ghosts[c].j--;
                    move_counter[c]++;
                }
                else
                {
                    move_counter[c]=0;
                    newway=choose_way(list_of_ghosts[c],pground);
                    if (newway=='s')
                    {
                        list_of_ghosts[c].i++;
                        list_of_ghosts[c].direction='s';
                    }
                    else if (newway=='d')
                    {
                        list_of_ghosts[c].j++;
                        list_of_ghosts[c].direction='d';
                    }
                    else if (newway=='w')
                    {
                        list_of_ghosts[c].i--;
                        list_of_ghosts[c].direction='w';
                    }
                    else if (newway=='a')
                    {
                        list_of_ghosts[c].j--;
                        list_of_ghosts[c].direction='a';
                    }
                }
            }

            else if (list_of_ghosts[c].direction=='d')
            {
                if (pground->coords[list_of_ghosts[c].i][list_of_ghosts[c].j+1]!='#' and move_counter[c]<3)
                {
                    list_of_ghosts[c].j++;
                    move_counter[c]++;
                }
                else
                {
                    move_counter[c]=0;
                    newway=choose_way(list_of_ghosts[c],pground);
                    if (newway=='s')
                    {
                        list_of_ghosts[c].i++;
                        list_of_ghosts[c].direction='s';
                    }
                    else if (newway=='a')
                    {
                        list_of_ghosts[c].j--;
                        list_of_ghosts[c].direction='a';
                    }
                    else if (newway=='w')
                    {
                        list_of_ghosts[c].i--;
                        list_of_ghosts[c].direction='w';
                    }
                    else if (newway=='d')
                    {
                        list_of_ghosts[c].j++;
                        list_of_ghosts[c].direction='d';
                    }
                }
            }

            else if (list_of_ghosts[c].direction=='s')
            {
                if (pground->coords[list_of_ghosts[c].i+1][list_of_ghosts[c].j]!='#' and move_counter[c]<3)
                {
                    list_of_ghosts[c].i++;
                    move_counter[c]++;
                }
                else
                {
                    move_counter[c]=0;
                    newway=choose_way(list_of_ghosts[c],pground);
                    if (newway=='s')
                    {
                        list_of_ghosts[c].i++;
                        list_of_ghosts[c].direction='s';
                    }
                    else if (newway=='w')
                    {
                        list_of_ghosts[c].i--;
                        list_of_ghosts[c].direction='w';
                    }
                    else if (newway=='d')
                    {
                        list_of_ghosts[c].j++;
                        list_of_ghosts[c].direction='d';
                    }
                    else if (newway=='a')
                    {
                        list_of_ghosts[c].j--;
                        list_of_ghosts[c].direction='a';
                    }
                }
            }
            
            else if (list_of_ghosts[c].direction=='w')
            {
                if (pground->coords[list_of_ghosts[c].i-1][list_of_ghosts[c].j]!='#' and move_counter[c]<3)
                {
                    list_of_ghosts[c].i--;
                    move_counter[c]++;
                }
                else
                {
                    move_counter[c]=0;
                    newway=choose_way(list_of_ghosts[c],pground);
                    if (newway=='s')
                    {
                        list_of_ghosts[c].i++;
                        list_of_ghosts[c].direction='s';
                    }
                    else if (newway=='d')
                    {
                        list_of_ghosts[c].j++;
                        list_of_ghosts[c].direction='d';
                    }
                    else if (newway=='a')
                    {
                        list_of_ghosts[c].j--;
                        list_of_ghosts[c].direction='a';
                    }
                    else if (newway=='w')
                    {
                        list_of_ghosts[c].i--;
                        list_of_ghosts[c].direction='w';
                    }
                }
            }
        }
        if (list_of_ghosts[c].i==pacman->i and list_of_ghosts[c].j==pacman->j and !pacman->state)
        {
            return 0;
        }
    }
    return 1;
}

void save_game(ground * field,char fname[60],pax * pacman,ghost * list_of_ghosts,int how,int level)
{
    //save game in file in two ways which user choose
    char Uname[60];
    char pass[60];
    int y=1;
    int n=0;
    FILE * file = fopen(fname,"rb");
    fread(Uname,60,1,file);
    fread(pass,60,1,file);
    fclose(file);
    file = fopen(fname,"wb");
    char charmap[6]={'|','.','G','@',' ','P'};
    if (how)
    {
        fwrite(Uname,60,1,file);
        fwrite(pass,60,1,file);
        fwrite(&level,sizeof(int),1,file);
        fwrite(&y,sizeof(int),1,file);
        fwrite(&field->length,sizeof(int),1,file);
        fwrite(&field->hight,sizeof(int),1,file);
        for (int i = 0; i < field->hight; i++)
        {
            for (int j = 0; j < field->length ; j++)
            {
                if (pacman->i == i and pacman->j == j)
                {
                    fwrite(&charmap[3],1,1,file);
                }
                else if (field->coords[i][j]=='#')
                {
                    fwrite(&charmap[0],1,1,file);
                }
                else if (field->coords[i][j]=='o')
                {
                    fwrite(&charmap[1],1,1,file);
                }
                else if (field->coords[i][j]=='P')
                {
                    fwrite(&charmap[5],1,1,file);
                }
                else
                {
                    fwrite(&charmap[4],1,1,file);
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            fwrite(&list_of_ghosts[i].i,sizeof(int),1,file);
            fwrite(&list_of_ghosts[i].j,sizeof(int),1,file);
        }
        
    }
    else
    {
        fwrite(Uname,60,1,file);
        fwrite(pass,60,1,file);
        fwrite(&level,sizeof(int),1,file);
        fwrite(&n,sizeof(int),1,file);
    }
    fclose(file);

}

int game(char * Uname,int which)
{
    system("CLS");
    int res;
    int start_wait=0;//flag shows start of a game

    pax * pacman=(pax *)malloc(sizeof(pax)); //make pacman object
    pacman->direction='d';
    pacman->point=0;
    pacman->state=0;

    ground * field=(ground *)malloc(sizeof(ground)); //make play ground object
    field->wpoint=0; //count coins of play ground
    ghost list_of_ghosts[2]; //make a list from ghosts 

    int level = extract_map_from_file(pacman,field,list_of_ghosts,which,Uname); //extract map and game objects from map or player account file and output the level of player
    
    while (1)
    {
        refresh(pacman,field,list_of_ghosts); //make an output
        
        if (!start_wait)//make a delay at the start of the game
        {
            Sleep(3000);
            start_wait=1;
        }
        
        system("CLS");

        res=move_point_achive_death(field,pacman,list_of_ghosts); //moves pacman

        if (res == -1) //breaks the game loop if escape key pressed
        {
            return level;
        }
        
        if(!res) //is there any thoch bitween pacman and ghosts
        {
            save_game(field,Uname,pacman,list_of_ghosts,0,level-1); //delete datas from game map and make the last game checker variable 0
            cout<<"looser!";
            Sleep(4000);
            return level-1;
        }

        res=dancing_ghosts(pacman,list_of_ghosts,field);
        if(!res)
        {
            save_game(field,Uname,pacman,list_of_ghosts,0,level-1); //delete game map and make the last game checker variable 0 in player account file
            cout<<"looser!";
            Sleep(4000);
            return level-1;
        }
        if (pacman->point==field->wpoint)
        {
            save_game(field,Uname,pacman,list_of_ghosts,0,level+3); //delete game map and make the last game checker variable 0 in player account file
            
            cout<<"winner!";
            Sleep(4000);
            return level+3;
        }
        save_game(field,Uname,pacman,list_of_ghosts,1,level); //save datas in the player account file
    }
}



