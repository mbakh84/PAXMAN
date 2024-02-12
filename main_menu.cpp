#include <iostream>

using namespace std;

int main_menu(int level)
{
    int checker=1;
    char input;
    while (1)
    {
        system("CLS");
        cout<<"LEVEL  :  "<<level<<"\n\n\n";
        if (checker == 1)
        {
            cout<<">>resume last game\n";
            cout<<"  new game\n";
            cout<<"  log out\n";

            input=getch();
            //system("CLS");
            if (input==13)
            {
                break;
            }
            else if (input=='w' or input=='W')
            {
                checker=3;
            }
            else if (input=='s' or input=='S')
            {
                checker=2;
            }
            
        }
        else if(checker == 2)
        {
            cout<<"  resume last game\n";
            cout<<">>new game\n";
            cout<<"  log out\n";

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
            cout<<"  resume last game\n";
            cout<<"  new game\n";
            cout<<">>log out\n";

            input=getch();
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
                checker=1;
            }
        }
    }
    return checker;
}
