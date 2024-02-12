#include <iostream>

using namespace std;

int main()
{
    FILE* file = fopen("map.txt", "r");
    

    char line[500];

    fgets(line, sizeof(line), file);
    char stri[3];
    char strj[3];
    int i;
    int leni;
    int j;
    int count=0;
    while (line[count]!=' ')
    {
        stri[count]=line[count];
        count++;
    }
    i=atoi(stri);
    count++;
    leni=count;
    while (line[count]!='\n')
    {
        strj[count-leni]=line[count];
        count++;
    }
    j=atoi(strj);
    cout<<i<<"  "<<j<<'\n';
    //pground->hight=j;
    //pground->length=i;

    char ** raw_map=(char **)malloc(sizeof(char *)*i);
    for (int c = 0; c < i; c++)
    {
        raw_map[c]=(char *)malloc(j+1);
        fgets(raw_map[c], j+2, file);
        raw_map[c][j]=0;
    }
    fclose(file);
    FILE * x=fopen("map.bin","w");
    fwrite(&j,sizeof(int),1,x);
    fwrite(&i,sizeof(int),1,x);
    for (int h = 0; h < i; h++)
    {
        for (int y = 0; y < j; y++)
        {
            fwrite(&raw_map[h][y],1,1,x);
        }
    }
    fclose(x);
}