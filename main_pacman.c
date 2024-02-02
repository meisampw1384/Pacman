#include "pacman.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define CLEAR_SCREEN "\033[2J\033[H"

void display(int selected_of_button)
{
    system("cls");
    printf(YELLOW "            Welcome to Pacman\n");
    printf("-----------------------------------------------" RESET "\n");
    for (int i = 0; i < 3; i++)
    {
        if (i == selected_of_button)
        {
            printf(GREEN ">" RESET);
        }
        printf("%d. ", i + 1);
        switch (i)
        {
        case 0:
            printf("login\n");
            break;
        case 1:
            printf("sign up\n");
            break;
        case 2:
            printf("exit\n");
            break;
        }
    }
}

void menu_login()
{
    int selected_button = 0;
    int input;
    do
    {       
        display(selected_button);//display sign up and login and exit
        input = getch();

        switch (input)
        {
        case 72: // upward arrow
            selected_button -= 1;
            if (selected_button < 0)
            {
                selected_button = 2;
            }
            break;
        case 80: // downward arrow
            selected_button += 1;
            if (selected_button > 2)
            {
                selected_button = 0;
            }
            break;
        case 13: // Enter key
            switch (selected_button)
            {
            case 0: // login
                login();
                break;
            case 1:
                sign_up();
                break;
            case 2: // exit
                exit(0);
                break;
            }
            break;
        }
    } while (input != 13);
}

int main()
{
    menu_login();
}
