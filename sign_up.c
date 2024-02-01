#include <stdio.h>
#include <conio.h>
#include "pacman.h"
#include <string.h>
#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define CLEAR_SCREEN "\033[2J\033[H"

struct sign_up_player
{
    char name[100];
    char family[100];
    int id;
    int level;
    char password[100];
    char status_of_game[20];
} temp;
// check if the file existed or not
int check_file_exist(char name_file[])
{
    FILE *file;
    file = fopen(name_file, "r");
    if (file)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// update file <information_of_players.txt> with new player
void update_file(struct sign_up_player player)
{
    FILE *file;
    file = fopen("D:\\pacman\\information_of_players.txt", "a+");
    fprintf(file, "%s %s %d %s %d %s\n", temp.name, temp.family, temp.id, temp.password, temp.level, temp.status_of_game);
    fclose(file);
}

void display_sign_up(int selected_of_button)
{
    printf(CLEAR_SCREEN);
    printf(YELLOW "                  Sign Up\n");
    printf("-----------------------------------------------" RESET "\n");
    for (int i = 0; i < 2; i++)
    {
        if (i == selected_of_button)
        {
            printf(GREEN "> " RESET);
        }
        printf("%d. ", i + 1);
        switch (i)
        {
        case 0:
            printf("Go to the registration form\n");
            break;
        case 1:
            printf("Go back to the main menu\n");
            break;
        }
    }
}

void display_Yes_NO_SignUp(int selected_of_button2)
{
    printf(CLEAR_SCREEN);
    printf("\nAre you sure about your registration information?\n");
    for (int i = 0; i < 2; i++)
    {
        if (i == selected_of_button2)
        {
            printf(GREEN "> " RESET);
        }
        printf("%d. ", i + 1);
        switch (i)
        {
        case 0:
            printf("Yes\n");
            break;
        case 1:
            printf("No\n");
            break;
        }
    }
}
void sign_up()
{
    int selected_of_button = 0;
    int input;
    do
    {
        // It shows going to the registration form or going to the menu
        display_sign_up(selected_of_button);
        input = getch();
        switch (input)
        {
        case 72: // upward
            selected_of_button -= 1;
            if (selected_of_button < 0)
            {
                selected_of_button = 1;
            }
            break;
        case 80: // downward
            selected_of_button += 1;
            if (selected_of_button > 1)
            {
                selected_of_button = 0;
            }
            break;
        case 13: // Enter key
            switch (selected_of_button)
            {
            case 0: // Go to the registration form
                printf("\nEnter the name: ");
                scanf("%s", temp.name);
                printf("\nEnter the family:");
                scanf("%s", temp.family);
                printf("\nEnter the password: ");
                scanf("%s", temp.password);
                FILE *read_file;
                temp.level = 0;
                strcpy(temp.status_of_game, "finished");
                int selected_of_button2 = 0;
                int input1;
                do
                {
                    // It shows whether the user is sure of his registration or not
                    display_Yes_NO_SignUp(selected_of_button2);
                    input1 = getch();
                    switch (input1)
                    {
                    case 72: // upward
                        selected_of_button2 -= 1;
                        if (selected_of_button2 < 0)
                            selected_of_button2 = 1;
                        break;
                    case 80: // downward
                        selected_of_button2 += 1;
                        if (selected_of_button2 > 1)
                            selected_of_button2 = 0;
                        break;
                    case 13: // key_enter
                        if (selected_of_button2 == 0)
                        {
                            //give id to the temp
                            int c;
                            if (check_file_exist("D:\\pacman\\number_of_player.txt"))
                            {
                                read_file = fopen("D:\\pacman\\number_of_player.txt", "r");
                                fscanf(read_file, "%d", &c);
                                fclose(read_file);
                            }
                            else
                            {
                                FILE *writefile;
                                writefile = fopen("D:\\pacman\\number_of_player.txt", "w");
                                fprintf(writefile, "%d", 0);
                                fclose(writefile);
                                FILE *read_file;
                                read_file = fopen("D:\\pacman\\number_of_player.txt", "r");
                                fscanf(read_file, "%d", &c);
                                fclose(read_file);
                            }

                            c += 1;
                            temp.id = c;
                            FILE *write_file;
                            write_file = fopen("D:\\pacman\\number_of_player.txt", "w");
                            fprintf(write_file, "%d", c);
                            fclose(write_file);
                            // It updates the file and adds a user to the file
                            update_file(temp);
                            
                            fprintf(write_file, "%d", c);
                            fclose(write_file);
                            printf(GREEN "\nYour id is: " RESET);
                            printf("%d", temp.id);
                            printf(GREEN "\nYour password is: " RESET);
                            printf("%s", temp.password);
                            printf("\n\n >go back to the menu");
                            int input2;
                            do
                            {
                                input2 = getch();
                                if (input2 == 13)
                                {
                                    menu_login();
                                }
                            } while (input2 != 13);
                        }
                        else
                        {
                            sign_up();
                        }
                        break;
                    }
                } while (input1 != 13);
                break;
            case 1:
                menu_login();
                break;
            }
            break;
        }
    } while (input != 13);
}