#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pacman.h"

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define CLEAR_SCREEN "\033[2J\033[H"

int number_of_player;

void num_of_player()
{
    FILE *file;
    file = fopen("D:\\pacman\\number_of_player.txt", "r");
    fscanf(file, "%d", &number_of_player);
    fclose(file);
}

struct information_of_player player;
struct information_of_all_players *temp_players;

//get all players in the file and save it in the temp_players
void read_all_players(struct information_of_all_players _temp_players[])
{
    FILE *file;
    file = fopen("D:\\pacman\\information_of_players.txt", "r");
    for (int i = 0; i < number_of_player; i++)
    {
        fscanf(file, "%s %s %d %s %d %s\n", _temp_players[i].name, _temp_players[i].family, &_temp_players[i].id, _temp_players[i].password, &_temp_players[i].level, _temp_players[i].status_of_game);
    }
    fclose(file);
}

//checks whether such a user exists in the file or not
int confirmation(char *password, int id, struct information_of_all_players *_temp_players)
{
    for (int i = 0; i < number_of_player; i++)
    {
        if (_temp_players[i].id == id && strcmp(_temp_players[i].password, password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void display_login(int selected_of_button)
{
    printf(CLEAR_SCREEN);
    printf(YELLOW "                  Login\n");
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
            printf("Go to the login form\n");
            break;
        case 1:
            printf("Go back to the menu_login\n");
            break;
        }
    }
}

void login()
{

    num_of_player();//It takes the number of players and save it in the number_of_player.txt
    temp_players = (struct information_of_all_players *)malloc(sizeof(struct information_of_all_players) * number_of_player);
    read_all_players(temp_players);//save all player in temp_player
    int selected_of_button = 0;
    int input;
    do
    {
        //Indicates whether the user wants to go to the menu or to the login form
        display_login(selected_of_button);
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
            case 0://go to the login form
                int id;
                printf("\nEnter the id: ");
                scanf("%d", &id);
                char password[100];
                printf("\nEnter the password: ");
                scanf("%s", password);
                int index = confirmation(password, id, temp_players);
                if (index != -1)
                {
                    player.id = id;
                    strcpy(player.password, password);
                    player.level = temp_players[index].level;
                    strcpy(player.name, temp_players[index].name);
                    strcpy(player.status_of_game, temp_players[index].status_of_game);
                    game_menu(player);
                }
                else
                {
                    printf(RED "\nThe player is not found!\n" RESET);
                    sleep(3);
                    login();
                }
                break;
            case 1://go to the main menu
                menu_login();
                break;
            }
            break;
        }
    } while (input != 13);
}