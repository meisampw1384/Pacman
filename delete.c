#include "pacman.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
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

void delete_player()
{
    system("cls");
    // get number of player
    int number_of_player;
    FILE *number_of_players;
    number_of_players = fopen("number_of_player.txt", "r");
    fscanf(number_of_players, "%d", &number_of_player);
    fclose(number_of_players);
    struct information_of_player temp_players[number_of_player];
    // get information of delete student
    int Delete_id;
    char Delete_name[100];
    char Delete_family[100];
    char Delete_password[100];
    printf(RED "     Delete player    \n");
    printf("---------------------------------\n" RESET);
    printf("\nEnter the name of the player you want to remove:");
    scanf("%s", Delete_name);
    printf("\nEnter the family of the player you want to remove:");
    scanf("%s", Delete_family);
    printf("\nEnter the id of the player you want to remove:");
    scanf("%d", &Delete_id);
    printf("\nEnter the password of the player you want to remove:");
    scanf("%s", Delete_password);
    // get information of all players in information_of_player.txt
    FILE *information_of_players;
    information_of_players = fopen("information_of_players.txt", "r");
    for (int i = 0; i < number_of_player; i++)
    {
        fscanf(information_of_players, "%s %s %d %s %d %s\n", temp_players[i].name, temp_players[i].family, &temp_players[i].id, temp_players[i].password, &temp_players[i].level, temp_players[i].status_of_game);
    }
    fclose(information_of_players);
    for (int i = 0; i < number_of_player; i++)
    {
        if (strcmp(temp_players[i].name, Delete_name) == 0 && strcmp(temp_players[i].family, Delete_family) == 0 && temp_players[i].id == Delete_id && strcmp(temp_players[i].password, Delete_password) == 0)
        {
            for (int j = i; j < number_of_player; j++)
            {
                temp_players[j] = temp_players[j + 1];
            }
            // update_number_of_file
            number_of_player--;
            FILE *update_number_of_player;
            update_number_of_player = fopen("number_of_player.txt", "w");
            fprintf(update_number_of_player, "%d", number_of_player);
            fclose(update_number_of_player);
            // update information of players
            FILE *update_information_of_players;
            update_information_of_players = fopen("information_of_players.txt", "w");
            for (int i = 0; i < number_of_player; i++)
            {
                fprintf(update_information_of_players, "%s %s %d %s %d %s\n", temp_players[i].name, temp_players[i].family, temp_players[i].id, temp_players[i].password, temp_players[i].level, temp_players[i].status_of_game);
            }
            fclose(update_information_of_players);
            printf(RED "\nPlayer removal operation completed successfully" RESET);
            Sleep(3000);
            menu_login();
        }
    }
    printf(RED "\nPlayer not found!" RESET);
    Sleep(3000);
    menu_login();
}