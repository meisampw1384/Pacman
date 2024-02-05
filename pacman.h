struct information_of_player
{
    char name[100];
    char family[100];
    char id;
    int level;
    char password[100];
    char status_of_game[20];

};



struct map_player
{
    char **map;
    int row;
    int column;
};


//Show the main menu that includes sign up and login
void menu_login();
//Performs the registration process
void sign_up();
//Performs the login process
void login();
//display game menu
void game_menu(struct information_of_player player);

void update_file_information(int id, struct information_of_player);
//Makes the logic of the game
void game_logic(struct information_of_player player, struct map_player map);