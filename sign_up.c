#include <stdio.h>
#include <conio.h>
#include "pacman.h"
#include <windows.h>
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

struct information_of_player temp;

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
void update_file(struct information_of_player player)
{
    FILE *file;
    file = fopen("information_of_players.txt", "a+");
    fprintf(file, "%s %s %d %s %d %s\n", temp.name, temp.family, temp.id, temp.password, temp.level, temp.status_of_game);
    fclose(file);
}

void display_sign_up(int selected_of_button)
{
    system("cls");
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
    system("cls");
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
                    case 13:                          // key_enter
                        if (selected_of_button2 == 0) // Yes for sign up
                        {
                            // give id to the temp
                            int c;
                            if (check_file_exist("last_id.txt"))
                            {
                                read_file = fopen("last_id.txt", "r");
                                fscanf(read_file, "%d", &c);
                                fclose(read_file);
                            }
                            else // the file does not exist
                            {
                                FILE *writefile;
                                writefile = fopen("last_id.txt", "w");
                                fprintf(writefile, "%d", 0);
                                fclose(writefile);
                                FILE *read_file;
                                read_file = fopen("last_id.txt", "r");
                                fscanf(read_file, "%d", &c);
                                fclose(read_file);
                            }

                            c += 1;
                            temp.id = c;
                            // update file last of id
                            FILE *update_file_last;
                            update_file_last = fopen("last_id.txt", "w");
                            fprintf(update_file_last, "%d", c);
                            fclose(update_file_last);
                            // update file of number of player
                            int x;
                            FILE *file_number_of_player;
                            file_number_of_player = fopen("number_of_player.txt", "r");
                            fscanf(file_number_of_player, "%d", &x);
                            fclose(file_number_of_player);
                            x++;
                            FILE *write_file_number_of_player;
                            write_file_number_of_player = fopen("number_of_player.txt", "w");
                            fprintf(write_file_number_of_player, "%d", x);
                            fclose(write_file_number_of_player);

                            // It updates the file and adds a user to the file
                            update_file(temp);
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
                        else // No for sign up
                        {
                            sign_up();
                        }
                        break;
                    }
                } while (input1 != 13);
                break;
            case 1: // go back to the menu
                menu_login();
                break;
            }
            break;
        }
    } while (input != 13);
}
