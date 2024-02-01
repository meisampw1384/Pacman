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

struct map_player player_map;

void update_file_information(int id, struct information_of_player player)
{
    int number_of_player;

    FILE *read_file_number_of_player;
    read_file_number_of_player = fopen("D:\\pacman\\number_of_player.txt", "r");
    fscanf(read_file_number_of_player, "%d", &number_of_player);
    fclose(read_file_number_of_player);

    struct information_of_all_players temp[number_of_player];

    FILE *read_file_information;
    read_file_information = fopen("D:\\pacman\\information_of_players.txt", "r");
    for (int i = 0; i < number_of_player; i++)
    {
        fscanf(read_file_information, "%s %s %d %s %d %s\n", temp[i].name,temp[i].family, &temp[i].id, temp[i].password, &temp[i].level, temp[i].status_of_game);
    }
    fclose(read_file_information);

    for (int i = 0; i < number_of_player; i++)
    {
        if (id == temp[i].id)
        {
            strcpy(temp[i].status_of_game, player.status_of_game);
            temp[i].level = player.level;
            strcpy(temp[i].status_of_game, player.status_of_game);
            break;
        }
    }

    FILE *write_file_information;
    write_file_information = fopen("D:\\pacman\\information_of_players.txt", "w");
    for (int i = 0; i < number_of_player; i++)
    {
        fprintf(write_file_information, "%s %s %d %s %d %s\n", temp[i].name,temp[i].family, temp[i].id, temp[i].password, temp[i].level, temp[i].status_of_game);
    }
    fclose(write_file_information);
}

void dispaly_pacman_menu(int selected_of_button5, struct information_of_player player)
{
    printf(CLEAR_SCREEN);
    printf(YELLOW "                 welcome to the pacman %s\n", player.name);
    printf("-----------------------------------------------------------------" RESET);
    printf("\nWhich level do you choose?\n");
    for (int i = 0; i < 3; i++)
    {
        if (i == selected_of_button5)
        {
            printf(GREEN ">" RESET);
        }
        printf("%d. ", i + 1);
        switch (i)
        {
        case 0:
            printf("Easy\n");
            break;
        case 1:
            printf("Medium\n");
            break;
        case 2:
            printf("Hard\n");
            break;
        }
    }
    printf(RED "\nPress on <esc> for Exit\n" RESET);
}

void display_Yes_NO(int selected_of_button3, struct information_of_player player)
{
    printf(CLEAR_SCREEN);
    printf(YELLOW "                 welcome to the pacman %s\n", player.name);
    printf("----------------------------------------------------------------" RESET);
    printf("\nDo you want to continue your previous game?\n");
    for (int i = 0; i < 2; i++)
    {
        if (i == selected_of_button3)
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

void readfile_map(char name_file[])
{
    int row;
    int column;
    FILE *file;
    file = fopen(name_file, "r");
    fscanf(file, "%d %d\n", &row, &column);
    player_map.row = row;
    player_map.column = column;
    player_map.map = (char **)malloc((row) * sizeof(char *));
    for (int i = 0; i < row; i++)
    {
        player_map.map[i] = (char *)malloc((column) * sizeof(char));
    }
    for (int j = 0; j < row; j++)
    {
        fscanf(file, "%s\n", player_map.map[j]);
    }

    fclose(file);
}

void game_menu(struct information_of_player player)
{
    if (strcmp(player.status_of_game, "finished") != 0)
    {
        int selected_of_button3 = 0;
        int input3;
        do
        {
            //It tells the player whether he wants to continue his last game or not
            display_Yes_NO(selected_of_button3, player);
            input3 = getch();
            switch (input3)
            {
            case 72://upward
                selected_of_button3 -= 1;
                if (selected_of_button3 < 0)
                    selected_of_button3 = 1;
                break;
            case 80://downward
                selected_of_button3 += 1;
                if (selected_of_button3 > 1)
                    selected_of_button3 = 0;
                break;
            case 13://enter key
                if (selected_of_button3 == 0)//Continuation of the previous game
                {
                    char str_id[20];
                    sprintf(str_id, "%d", player.id);
                    readfile_map(str_id);//Read the previous game map
                    game_logic(player, player_map);
                }
                else
                {
                    int selected_of_button4;
                    int input4;
                    do
                    {
                        //It shows what level of the game the user wants to try?
                        dispaly_pacman_menu(selected_of_button4, player);
                        input4 = getch();
                        switch (input4)
                        {
                        case 72://upward
                            selected_of_button4 -= 1;
                            if (selected_of_button4 < 0)
                            {
                                selected_of_button4 = 2;
                            }
                            break;
                        case 80://downward
                            selected_of_button4 += 1;
                            if (selected_of_button4 > 2)
                            {
                                selected_of_button4 = 0;
                            }
                            break;
                        case 27://esc key
                            update_file_information(player.id, player);
                            exit(0);
                            break;
                        case 13://enter key
                            if (selected_of_button4 == 0)//go to the mapA or easy
                            {
                                readfile_map("D:\\pacman\\mapA.txt");
                                game_logic(player, player_map);
                            }
                            else if (selected_of_button4 == 1)//go to the mapB or medium
                            {
                                readfile_map("D:\\pacman\\mapB.txt");
                                game_logic(player, player_map);
                            }
                            else if (selected_of_button4 == 2)//go to the mapC or hard
                            {
                                readfile_map("D:\\pacman\\mapC.txt");
                                game_logic(player, player_map);
                            }
                        }
                    } while (input4 != 13);
                }
            }
        } while (input3 != 13);
    }
    else
    {
        int selected_of_button5 = 0;
        int input5;
        do
        {
            dispaly_pacman_menu(selected_of_button5, player);
            input5 = getch();
            switch (input5)
            {
            case 72:
                selected_of_button5 -= 1;
                if (selected_of_button5 < 0)
                {
                    selected_of_button5 = 2;
                }
                break;
            case 80:
                selected_of_button5 += 1;
                if (selected_of_button5 > 2)
                {
                    selected_of_button5 = 0;
                }
                break;
            case 27:
                update_file_information(player.id, player);
                exit(0);
                break;
            case 13:
                if (selected_of_button5 == 0)
                {
                    readfile_map("D:\\pacman\\mapA.txt");
                    game_logic(player, player_map);
                }
                else if (selected_of_button5 == 1)
                {
                    readfile_map("D:\\pacman\\mapB.txt");
                    game_logic(player, player_map);
                }
                else if (selected_of_button5 == 2)
                {
                    readfile_map("D:\\pacman\\mapC.txt");
                    game_logic(player, player_map);
                }
            }
        } while (input5 != 13);
    }
}