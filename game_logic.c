#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pacman.h"
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

// It saves the player's map in a file named player ID
void writefile_map_for_player(struct map_player map, const char name_file[])
{
    FILE *write_file_map;
    write_file_map = fopen(name_file, "w");

    int row = map.row;
    int column = map.column;
    fprintf(write_file_map, "%d %d\n", row, column);
    for (int i = 0; i < row; i++)
    {
        fprintf(write_file_map, "%s\n", map.map[i]);
    }
    fclose(write_file_map);
}
//swap the array elements
void move_array_elements(struct map_player map, int row1, int column1, int row2, int column2)
{
    char temp = map.map[row1][column1];
    map.map[row1][column1] = map.map[row2][column2];
    map.map[row2][column2] = temp;
}
//If the player wins, it will show the player the information about winning the game
void display_win_the_game(struct information_of_player player)
{
    system("cls");
    printf(GREEN "You win the game.\nYour level increased by three!\n" RESET);
    player.level += 3;
    printf(YELLOW "Your current level: %d", player.level);
    strcpy(player.status_of_game, "finished");
    update_file_information(player.id, player);
    sleep(5);
    game_menu(player);
}
//if the player lose, it will show the player the information about losing the game
void display_lose_the_game(struct information_of_player player)
{
    system("cls");
    printf(RED "You lose the game.\nYour level decreased by one!\n" RESET);
    player.level--;
    printf(YELLOW "Your current level: %d", player.level);
    strcpy(player.status_of_game, "finished");
    update_file_information(player.id, player);
    sleep(5);
    game_menu(player);
}
//diplsay player he wants save the game or not
void display_Yes_NO_SaveTheGame(int selected_of_button2)
{
    system("cls");
    printf("\nDo you want to save the game?\n");
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
//show the map for player 
void display_the_map(struct map_player map, struct information_of_player player, int pill)
{
    system("cls");
    char **updated_map;
    updated_map = (char **)malloc(sizeof(char *) * map.row * 4);
    for (int i = 0; i < map.row * 4; i++)
    {
        updated_map[i] = (char *)malloc(sizeof(char) * map.column * 5);
    }

    printf(BLUE "name: %s %s   number of pills earned: %d   level: %d\n\n" RESET, player.name,player.family, pill, player.level);
    for (int i = 0; i < map.row; i++)
    {
        for (int j = 0; j < map.column; j++)
        {
            if (map.map[i][j] == '-' || map.map[i][j] == '|')
            {
                for (int k = 0; k < 4; k++)
                {
                    for (int z = 0; z < 5; z++)
                    {
                        updated_map[i * 4 + k][j * 5 + z] = '.';
                    }
                }
            }
            else if (map.map[i][j] == 'P')
            {
                updated_map[i * 4 + 0][j * 5 + 0] = ' ';
                updated_map[i * 4 + 0][j * 5 + 1] = ' ';
                updated_map[i * 4 + 0][j * 5 + 2] = ' ';
                updated_map[i * 4 + 0][j * 5 + 3] = ' ';
                updated_map[i * 4 + 0][j * 5 + 4] = ' ';
                updated_map[i * 4 + 1][j * 5 + 0] = ' ';
                updated_map[i * 4 + 1][j * 5 + 1] = '.';
                updated_map[i * 4 + 1][j * 5 + 2] = '-';
                updated_map[i * 4 + 1][j * 5 + 3] = '.';
                updated_map[i * 4 + 1][j * 5 + 4] = ' ';
                updated_map[i * 4 + 2][j * 5 + 0] = ' ';
                updated_map[i * 4 + 2][j * 5 + 1] = '\'';
                updated_map[i * 4 + 2][j * 5 + 2] = '-';
                updated_map[i * 4 + 2][j * 5 + 3] = '\'';
                updated_map[i * 4 + 2][j * 5 + 4] = ' ';
                updated_map[i * 4 + 3][j * 5 + 0] = ' ';
                updated_map[i * 4 + 3][j * 5 + 1] = ' ';
                updated_map[i * 4 + 3][j * 5 + 2] = ' ';
                updated_map[i * 4 + 3][j * 5 + 3] = ' ';
                updated_map[i * 4 + 3][j * 5 + 4] = ' ';
            }
            else if (map.map[i][j] == 'F')
            {
                updated_map[i * 4 + 0][j * 5 + 0] = ' ';
                updated_map[i * 4 + 0][j * 5 + 1] = '.';
                updated_map[i * 4 + 0][j * 5 + 2] = '-';
                updated_map[i * 4 + 0][j * 5 + 3] = '.';
                updated_map[i * 4 + 0][j * 5 + 4] = ' ';
                updated_map[i * 4 + 1][j * 5 + 0] = '|';
                updated_map[i * 4 + 1][j * 5 + 1] = ' ';
                updated_map[i * 4 + 1][j * 5 + 2] = 'O';
                updated_map[i * 4 + 1][j * 5 + 3] = 'O';
                updated_map[i * 4 + 1][j * 5 + 4] = '|';
                updated_map[i * 4 + 2][j * 5 + 0] = '|';
                updated_map[i * 4 + 2][j * 5 + 1] = ' ';
                updated_map[i * 4 + 2][j * 5 + 2] = ' ';
                updated_map[i * 4 + 2][j * 5 + 3] = ' ';
                updated_map[i * 4 + 2][j * 5 + 4] = '|';
                updated_map[i * 4 + 3][j * 5 + 0] = '^';
                updated_map[i * 4 + 3][j * 5 + 1] = '^';
                updated_map[i * 4 + 3][j * 5 + 2] = '^';
                updated_map[i * 4 + 3][j * 5 + 3] = '^';
                updated_map[i * 4 + 3][j * 5 + 4] = '^';
            }
            else if (map.map[i][j] == '@')
            {
                updated_map[i * 4 + 0][j * 5 + 0] = ' ';
                updated_map[i * 4 + 0][j * 5 + 1] = '.';
                updated_map[i * 4 + 0][j * 5 + 2] = '-';
                updated_map[i * 4 + 0][j * 5 + 3] = '-';
                updated_map[i * 4 + 0][j * 5 + 4] = '.';
                updated_map[i * 4 + 1][j * 5 + 0] = '/';
                updated_map[i * 4 + 1][j * 5 + 1] = ' ';
                updated_map[i * 4 + 1][j * 5 + 2] = ' ';
                updated_map[i * 4 + 1][j * 5 + 3] = 'O';
                updated_map[i * 4 + 1][j * 5 + 4] = '/';
                updated_map[i * 4 + 2][j * 5 + 0] = '\\';
                updated_map[i * 4 + 2][j * 5 + 1] = ' ';
                updated_map[i * 4 + 2][j * 5 + 2] = ' ';
                updated_map[i * 4 + 2][j * 5 + 3] = ' ';
                updated_map[i * 4 + 2][j * 5 + 4] = '\\';
                updated_map[i * 4 + 3][j * 5 + 0] = ' ';
                updated_map[i * 4 + 3][j * 5 + 1] = '\'';
                updated_map[i * 4 + 3][j * 5 + 2] = '-';
                updated_map[i * 4 + 3][j * 5 + 3] = '-';
                updated_map[i * 4 + 3][j * 5 + 4] = '\'';
                ;
            }
            else if (map.map[i][j] == '.')
            {
                for (int u = 0; u < 4; u++)
                {
                    for (int c = 0; c < 5; c++)
                    {
                        updated_map[i * 4 + u][j * 5 + c] = ' ';
                    }
                }
            }
        }
    }

    for (int i = 0; i < (map.row) * 4; i++)
    {
        for (int j = 0; j < map.column * 5; j++)
        {
            printf(YELLOW "%c", updated_map[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < map.row * 4; i++)
    {
        free(updated_map[i]);
    }
    free(updated_map);
    
    printf(RED "\n\nPress on <esc> for Exit" RESET);
}
// move ghost random
struct map_player move_ghost(struct map_player map, struct information_of_player player, int pill)
{
    struct map_player updated_map;
    updated_map.row = map.row;
    updated_map.column = map.column;
    updated_map.map = (char **)malloc(sizeof(char *) * updated_map.row);
    for (int i = 0; i < updated_map.row; i++)
    {
        updated_map.map[i] = (char *)malloc(sizeof(char) * updated_map.column);
    }
    for (int i = 0; i < map.row; i++)
    {
        strcpy(updated_map.map[i], map.map[i]);
    }

    for (int i = 0; i < map.row; i++)
    {
        for (int j = 0; j < map.column; j++)
        {
            if (map.map[i][j] == 'F')
            {
                int random_number = rand() % 4;

                if (random_number == 0 && map.map[i][j - 1] != '-' && map.map[i][j - 1] != '|' && map.map[i][j - 1] != 'P' && map.map[i][j - 1] != 'F') // move ghost left
                {
                    if (map.map[i][j - 1] != '@')
                        move_array_elements(updated_map, i, j, i, j - 1);
                    else
                    {
                        move_array_elements(updated_map, i, j, i, j - 1);
                        updated_map.map[i][j] = '.';
                        display_the_map(updated_map, player, pill);
                        sleep(1);
                        display_lose_the_game(player);
                    }
                }
                else if (random_number == 1 && map.map[i][j + 1] != '-' && map.map[i][j + 1] != '|' && map.map[i][j + 1] != 'P' && map.map[i][j + 1] != 'F') // move ghost right
                {
                    if (map.map[i][j + 1] != '@')
                        move_array_elements(updated_map, i, j, i, j + 1);
                    else
                    {
                        move_array_elements(updated_map, i, j, i + 1, j + 1);
                        updated_map.map[i][j] = '.';
                        display_the_map(updated_map, player, pill);
                        sleep(1);
                        display_lose_the_game(player);
                    }
                }
                else if (random_number == 2 && map.map[i - 1][j] != '-' && map.map[i - 1][j] != '|' && map.map[i - 1][j] != 'P' && map.map[i - 1][j] != 'F') // move ghost up
                {
                    if (map.map[i - 1][j] != '@')
                        move_array_elements(updated_map, i, j, i - 1, j);
                    else
                    {
                        move_array_elements(updated_map, i, j, i - 1, j);
                        updated_map.map[i][j] = '.';
                        display_the_map(updated_map, player, pill);
                        sleep(1);
                        display_lose_the_game(player);
                    }
                }
                else if (random_number == 3 && map.map[i + 1][j] != '-' && map.map[i + 1][j] != '|' && map.map[i + 1][j] != 'P' && map.map[i + 1][j] != 'F') // move ghost down
                {
                    if (map.map[i + 1][j] != '@')
                        move_array_elements(updated_map, i, j, i + 1, j);
                    else
                    {
                        move_array_elements(updated_map, i, j, i + 1, j);
                        updated_map.map[i][j] = '.';
                        display_the_map(updated_map, player, pill);
                        sleep(1);
                        display_lose_the_game(player);
                    }
                }
            }
        }
    }
    return updated_map;
}

void game_logic(struct information_of_player player, struct map_player map)
{
    srand(time(NULL));
    int pill = 0;
    int number_of_pills_get = 0;

    // count of pills
    for (int i = 0; i < map.row; i++)
    {
        for (int j = 0; j < map.column; j++)
        {
            if (map.map[i][j] == 'P')
            {
                pill++;
            }
        }
    }
    // show the map
    display_the_map(map, player, number_of_pills_get);
    int row = map.row;
    int column = map.column;
    int row_pacman;
    int column_pacman;

    // Save Pacman coordinates in row_pacman and column pacman
    for (int i = 0; i < row; i++)
    {
        int flag = 0;
        for (int j = 0; j < column; j++)
        {
            if (map.map[i][j] == '@')
            {
                row_pacman = i;
                column_pacman = j;
                flag = 1;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }

    while (1)
    {
        if (kbhit()) // If a button is pressed from the keyboard,return non zero
        {
            int input6;
            input6 = getch();
            switch (input6)
            {
            case 72: // upward
                if (map.map[row_pacman - 1][column_pacman] != '|' && map.map[row_pacman - 1][column_pacman] != '-' && map.map[row_pacman - 1][column_pacman] != 'F' && map.map[row_pacman - 1][column_pacman] != 'P')
                {
                    move_array_elements(map, row_pacman - 1, column_pacman, row_pacman, column_pacman);
                    display_the_map(map, player, number_of_pills_get);
                    row_pacman--;
                }
                else if (map.map[row_pacman - 1][column_pacman] == 'P')
                {
                    move_array_elements(map, row_pacman - 1, column_pacman, row_pacman, column_pacman);
                    map.map[row_pacman][column_pacman] = '.';
                    pill--;
                    number_of_pills_get++;
                    display_the_map(map, player, number_of_pills_get);
                    if (pill == 0)
                    {

                        sleep(1);
                        display_win_the_game(player);
                    }
                    row_pacman--;
                }
                else if (map.map[row_pacman - 1][column_pacman] == 'F')
                {
                    map.map[row_pacman][column_pacman] = '.';
                    display_the_map(map, player, number_of_pills_get);
                    sleep(1);
                    display_lose_the_game(player);
                }
                break;
            case 80: // downward
                if (map.map[row_pacman + 1][column_pacman] != '|' && map.map[row_pacman + 1][column_pacman] != '-' && map.map[row_pacman + 1][column_pacman] != 'F' && map.map[row_pacman + 1][column_pacman] != 'P')
                {
                    move_array_elements(map, row_pacman + 1, column_pacman, row_pacman, column_pacman);
                    display_the_map(map, player, number_of_pills_get);
                    row_pacman++;
                }
                else if (map.map[row_pacman + 1][column_pacman] == 'P')
                {
                    move_array_elements(map, row_pacman + 1, column_pacman, row_pacman, column_pacman);
                    map.map[row_pacman][column_pacman] = '.';
                    pill--;
                    number_of_pills_get++;
                    display_the_map(map, player, number_of_pills_get);
                    if (pill == 0)
                    {
                        sleep(1);
                        display_win_the_game(player);
                    }
                    row_pacman++;
                }
                else if (map.map[row_pacman + 1][column_pacman] == 'F')
                {
                    map.map[row_pacman][column_pacman] = '.';
                    display_the_map(map, player, number_of_pills_get);
                    sleep(1);
                    display_lose_the_game(player);
                }
                break;
            case 75: // left
                if (map.map[row_pacman][column_pacman - 1] != '|' && map.map[row_pacman][column_pacman - 1] != '-' && map.map[row_pacman][column_pacman - 1] != 'F' && map.map[row_pacman][column_pacman - 1] != 'P')
                {
                    move_array_elements(map, row_pacman, column_pacman - 1, row_pacman, column_pacman);
                    display_the_map(map, player, number_of_pills_get);
                    column_pacman--;
                }
                else if (map.map[row_pacman][column_pacman - 1] == 'P')
                {
                    move_array_elements(map, row_pacman, column_pacman - 1, row_pacman, column_pacman);
                    map.map[row_pacman][column_pacman] = '.';
                    pill--;
                    number_of_pills_get++;
                    display_the_map(map, player, number_of_pills_get);
                    if (pill == 0)
                    {
                        sleep(1);
                        display_win_the_game(player);
                    }
                    column_pacman--;
                }
                else if (map.map[row_pacman][column_pacman - 1] == 'F')
                {
                    map.map[row_pacman][column_pacman] = '.';
                    display_the_map(map, player, number_of_pills_get);
                    sleep(1);
                    display_lose_the_game(player);
                }
                break;
            case 77: // right
                if (map.map[row_pacman][column_pacman + 1] != '|' && map.map[row_pacman][column_pacman + 1] != '-' && map.map[row_pacman][column_pacman + 1] != 'F' && map.map[row_pacman][column_pacman + 1] != 'P')
                {
                    move_array_elements(map, row_pacman, column_pacman + 1, row_pacman, column_pacman);
                    display_the_map(map, player, number_of_pills_get);
                    column_pacman++;
                }
                else if (map.map[row_pacman][column_pacman + 1] == 'P')
                {
                    move_array_elements(map, row_pacman, column_pacman + 1, row_pacman, column_pacman);
                    map.map[row_pacman][column_pacman] = '.';
                    pill--;
                    number_of_pills_get++;
                    display_the_map(map, player, number_of_pills_get);
                    if (pill == 0)
                    {
                        sleep(1);
                        display_win_the_game(player);
                    }
                    column_pacman++;
                }
                else if (map.map[row_pacman][column_pacman + 1] == 'F')
                {
                    map.map[row_pacman][column_pacman] = '.';
                    display_the_map(map, player, number_of_pills_get);
                    sleep(1);
                    display_lose_the_game(player);
                }
                break;
            case 27: // esc key
                int input7;
                int selected_of_button7 = 0;
                do
                {
                    // Indicates whether the player wants to save the game or not
                    display_Yes_NO_SaveTheGame(selected_of_button7);
                    input7 = getch();
                    switch (input7)
                    {
                    case 72: // upward
                        selected_of_button7 -= 1;
                        if (selected_of_button7 < 0)
                            selected_of_button7 = 1;
                        break;
                    case 80: // downward
                        selected_of_button7 += 1;
                        if (selected_of_button7 > 1)
                            selected_of_button7 = 0;
                        break;
                    case 13:                          // enter
                        if (selected_of_button7 == 0) // save the game
                        {
                            char namefile[20];
                            sprintf(namefile, "%d", player.id);
                            writefile_map_for_player(map, namefile);
                            strcpy(player.status_of_game, "not finished");
                            game_menu(player);
                        }
                        else // not save the game
                        {
                            strcpy(player.status_of_game, "finished");
                            game_menu(player);
                        }
                    }
                } while (input7 != 13);
            }
        }
        else
        {
            map = move_ghost(map, player, pill);
            display_the_map(map, player, number_of_pills_get);
            Sleep(500);
        }
    }
}
