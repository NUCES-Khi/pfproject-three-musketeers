//displays start menu
void start_menu();

// create a game grid
char **create_game_grid();

// initializes the grid
void initialize_grid(char **grid);

// changes console color to the code value
void set_color(int color);

// change color of character
void color_player(char player);

// print the game grid
void print_grid(char **grid);

// update the frame by clearing the screen and printing the grid
void update_frame(char **grid);

// user input for the column number or if user wants to save or exit
int user_input(char **grid, int *player); 

// validate a move in the specified column
bool validate_move(char **grid, int col);

// get the first empty row in a column
int get_first_empty(char **grid, int col);

// set the grid at the specified column and row with the player's character
void set_grid(char **grid, int col, int player);

// check the win status of the game after a move
bool game_win_status(char **grid, int player);

// check if the game is a draw
bool game_draw_status(char **grid);

// displays game draw screen to player
void game_draw_display(char **grid, int player);

// displays game end screen to player
void game_end_display(char **grid, int player);

// extracts player wins from the wins file
int *save_win(int player);

// saves the game progress and turn
void save_game(char **grid, int player);

// loads the game from the file
int load_game(char **grid, int player);

// shows the wins for each player
void display_wins(int player);
