//import libraries and other files
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <cstring>
#include <wchar.h>
#include "game.cpp"
#include "authentication.cpp"
#include "main_menu.cpp"
#include "entery.cpp"

using namespace std;
int main()
{
    int which; //main menu option selector
    char Fname[60]; //file name will save at this variable
    text();
    while (1)
    {
        int level=authentication(Fname); //includes : sign in , sign up and delete account
        while (1) //loop for main menu which includes : new game , resume last game , log out
        {
            which=main_menu(level);
            if (which==3) //condition for logout option
            {
                break; 
            }

            level = game(Fname,which); //game function return the level of user for show in main menu
        }
    }
}