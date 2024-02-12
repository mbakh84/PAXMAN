int main_page();
int sign_in(char fname[60],int * level);
char * authentication();
void sign_up();
void del_account();

int authentication(char Fname[60])
{
    int choose;
    int loop_breaker;
    char fname[60];
    int level;
    while (1)
    {
        
        //loop will break just when you sign in
        system("CLS");
        int choose=main_page(); //provides simple GUI and choose option
        if(choose==1)
        {
            loop_breaker=sign_in(fname,&level); //wrong password or account not exict checker
            if (loop_breaker)
            {
                break;
            }
            
        }
        else if(choose==2)
        {
            sign_up();
        }
        else if (choose==3)
        {
            del_account();
        }
        
    }
    strcpy(Fname,fname);
    return level;
}

int main_page()
{
    //provides simple GUI and choose option
    int checker = 1;
    char input;
    while (1)
    {
        system("CLS");
        if (checker == 1)
        {
            cout<<">>Sign in\n";
            cout<<"  Sign up\n";
            cout<<"  delete account\n";
            cout<<"  EXIT\n";


            input=getch();
            //system("CLS");
            if (input==13)
            {
                break;
            }
            else if (input=='w' or input=='W')
            {
                checker=4;
            }
            else if (input=='s' or input=='S')
            {
                checker=2;
            }
            
        }
        else if(checker == 2)
        {
            cout<<"  Sign in\n";
            cout<<">>Sign up\n";
            cout<<"  delete account\n";
            cout<<"  EXIT\n";

            input=getch();
            //system("CLS");
            if (input==13)
            {
                break;
            }
            else if (input=='w' or input=='W')
            {
                checker=1;
            }
            else if (input=='s' or input=='S')
            {
                checker=3;
            }
        }
        else if (checker == 3)
        {
            cout<<"  Sign in\n";
            cout<<"  Sign up\n";
            cout<<">>delete account\n";
            cout<<"  EXIT\n";

            input=getch();
            //system("CLS");
            if (input==13)
            {
                break;
            }
            else if (input=='w' or input=='W')
            {
                checker=2;
            }
            else if (input=='s' or input=='S')
            {
                checker=4;
            }
        }
        
        else if (checker == 4)
        {
            cout<<"  Sign in\n";
            cout<<"  Sign up\n";
            cout<<"  delete account\n";
            cout<<">>EXIT\n";

            input=getch();
            //system("CLS");
            if (input==13)
            {
                exit(0);
            }
            else if (input=='w' or input=='W')
            {
                checker=3;
            }
            else if (input=='s' or input=='S')
            {
                checker=1;
            }
        }
    }
    return checker;
}

int sign_in(char fname[60],int *level)
{
    system("CLS");

    char uname[60];
    char pass[60];

    //make a string that is a file name with your username in D Drive
    cout<<"please enter your user name :";
    cin.getline(uname,50);
    int len = strlen(uname);
    char * unamecheck=(char *)malloc(60);
    strcpy(unamecheck,uname);
    unamecheck=strcat(unamecheck,".bin");
    char * unamecheck2=(char *)malloc(60);
    unamecheck2[0]='D';
    unamecheck2[1]=':';
    unamecheck2[2]='\\';
    int i=0;
    while (unamecheck[i])
    {
        unamecheck2[i+3]=unamecheck[i];
        i++;
    }
    unamecheck2[i+3]=0;

    FILE * check = fopen(unamecheck2,"rb"); //check avalablity of an account
    if (check)
    {
        strcpy(fname,unamecheck2);
        fread(uname,60,1,check);
        cout<<"please enter password : ";
        cin.getline(pass,50);
        fread(uname,60,1,check);
        fread(level,sizeof(int),1,check);
        if (!strcmp(uname,pass))
        {
            cout<<"sign in succesfully done";
            Sleep(4000);
            fclose(check);
            return 1;
        }
        else
        {
            cout<<"wrong password!";
            Sleep(4000);
            fclose(check);
            return 0;
        }
    }
    else
    {
        cout<<"this username has not an account";
        Sleep(4000);
        fclose(check);
        return 0;
    } 
}

void sign_up()
{
    system("CLS");
    int map_exict=0; //last game checker

    //make a string that is a file name with your username in D Drive
    char uname[60];
    cout<<"please enter your user name :";
    cin.getline(uname,50);
    int len = strlen(uname);
    char * unamecheck=(char *)malloc(60);
    strcpy(unamecheck,uname);
    unamecheck=strcat(unamecheck,".bin");
    char * unamecheck2=(char *)malloc(60);
    unamecheck2[0]='D';
    unamecheck2[1]=':';
    unamecheck2[2]='\\';
    int i=0;
    while (unamecheck[i])
    {
        unamecheck2[i+3]=unamecheck[i];
        i++;
    }
    unamecheck2[i+3]=0;

    FILE * check = fopen(unamecheck2,"rb"); //check avalablity of an account
    if (check)
    {
        cout<<"this username has an account";
        Sleep(4000);
        fclose(check);
    }
    else
    {
        fclose(check);
        FILE * check = fopen(unamecheck2,"w");
        fwrite(uname,60,1,check);
        cout<<"please enter password : ";
        cin.getline(uname,50);
        fwrite(uname,60,1,check);
        fwrite(&map_exict,sizeof(int),1,check); //level (using an avaliable variable)
        fwrite(&map_exict,sizeof(int),1,check); //not ended game checker
        //id is same as user name(it is uniqe)
        cout<<"account created succesfully";
        Sleep(4000);
        fclose(check);
    }    
}

void del_account()
{
    system("CLS");

    //make a string that is a file name with your username in D Drive
    char uname[60];
    char passw[60];
    cout<<"please enter your user name :";
    cin.getline(uname,50);
    int len = strlen(uname);
    char * unamecheck=(char *)malloc(60);
    strcpy(unamecheck,uname);
    unamecheck=strcat(unamecheck,".bin");
    char * unamecheck2=(char *)malloc(60);
    unamecheck2[0]='D';
    unamecheck2[1]=':';
    unamecheck2[2]='\\';
    int i=0;
    while (unamecheck[i])
    {
        unamecheck2[i+3]=unamecheck[i];
        i++;
    }
    unamecheck2[i+3]=0;

    FILE * check = fopen(unamecheck2,"r");//check avalablity of an account
    if (check)
    {
        cout<<"please enter your password :";
        cin.getline(passw,60);
        fread(uname,60,1,check);
        fread(uname,60,1,check);
        if (!strcmp(uname,passw))
        {
            fclose(check);
            remove(unamecheck2);
            cout<<"done";
            Sleep(4000);
        }
        else
        {
            cout<<"wrong password!";
            fclose(check);
            Sleep(4000);
        }
    }
    else
    {
        cout<<"this username has not an account";
        fclose(check);
        Sleep(4000);
    }    
}
