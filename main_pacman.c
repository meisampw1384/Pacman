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

void display(int selected_of_button)
{
    system("cls");
    printf(YELLOW "            Welcome to Pacman\n");
    printf("-----------------------------------------------" RESET "\n");
    for (int i = 0; i < 4; i++)
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
            printf("delete player\n");
            break;
        case 3:
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
        display(selected_button); // display sign up and login and exit
        input = getch();

        switch (input)
        {
        case 72: // upward arrow
            selected_button -= 1;
            if (selected_button < 0)
            {
                selected_button = 3;
            }
            break;
        case 80: // downward arrow
            selected_button += 1;
            if (selected_button > 3)
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
            case 1: // sign up
                sign_up();
                break;
            case 2: // delete player
                delete_player();
                break;
            case 3: // exit
                exit(0);
                break;
            }
            break;
        }
    } while (input != 13);
}

int main()
{
    char validation_of_CurrentPlayer[20];
    FILE *current_player;
    current_player = fopen("current_player.txt", "r");
    fscanf(current_player, "%s ", validation_of_CurrentPlayer);
    // Checks whether a player has already logged in
    if (strcmp(validation_of_CurrentPlayer, "valid") == 0)
    {
        struct information_of_player player;
        int number_of_player;
        // get number of players
        FILE *number_of_players;
        number_of_players = fopen("number_of_player.txt", "r");
        fscanf(number_of_players, "%d", &number_of_player);
        fclose(number_of_players);
        // get information of all players and save it in struct
        struct information_of_player temp_players[number_of_player];
        FILE *get_information_of_players;
        get_information_of_players = fopen("information_of_players.txt", "r");
        for (int i = 0; i < number_of_player; i++)
        {
            fscanf(get_information_of_players, "%s %s %d %s %d %s\n", temp_players[i].name, temp_players[i].family, &temp_players[i].id, temp_players[i].password, &temp_players[i].level, temp_players[i].status_of_game);
        }
        fclose(get_information_of_players);
        // get id of current player
        int id_CurrentPlayer;
        fscanf(current_player, "%d", &id_CurrentPlayer);
        fclose(current_player);
        // Checks out of the registered players, which matches the current player
        for (int i = 0; i < number_of_player; i++)
        {
            if (temp_players[i].id == id_CurrentPlayer)
            {
                player.id = temp_players[i].id;
                strcpy(player.password, temp_players[i].password);
                strcpy(player.name, temp_players[i].name);
                strcpy(player.family, temp_players[i].family);
                player.level = temp_players[i].level;
                strcpy(player.status_of_game, temp_players[i].status_of_game);
                break;
            }
        }
        game_menu(player);
    }
    else
    {
        fclose(current_player);
        menu_login();
    }
    return 0;
}
