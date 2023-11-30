/*
 * Creators: Fasih Hasan, Syed Ukkashah, Muhammad Ali
 * Desc: A game called connect 4. First player to create a sequence of 4 characters in a row in a 6 by 7 grid will win
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define BUFFER_SIZE 10
#define f_name "wins.txt"

#define P1 'R'
#define P2 'B'
#define X '.'

// default settings
const int rows = 6, cols = 7;


// create a game grid
char **create_game_grid();

// change color of character
void color_char(char player);

// print the game grid
void print_grid(char **grid);

// update the frame by clearing the screen and printing the grid
void update_frame(char **grid);

// user input for the column number
int user_input(int player); 

// validate a move in the specified column
bool validate_move(char **grid, int col);

// get the first empty row in a column
int get_first_empty(char **grid, int col);

// set the grid at the specified column and row with the player's character
void set_grid(char **grid, int col, int player);

// check the win status of the game after a move
bool game_win_status(char **grid, int col, int player);

// check if the game is a draw
bool game_draw_status(char **grid);

// displays relevant game end screen to player
void game_end_display(char **grid, int player, bool type);

// extracts player wins from the wins file
int *save_win(int player);

// shows the wins for each player
void display_wins(int player);


int main()
{
	int player, col;
	bool valid = true, win = false;
	char player_char, **grid = create_game_grid();

	// default color scheme
	system("Color 0E");

	// game loop
	while (!win) {

		// check at the start if draw
		// this was done to avoid out of bound errors mid game
		
		if (game_draw_status(grid)) {
			// display end screen for DRAW
			game_end_display(grid, player, false);

			return 0; // end
		}

		// for each player
		for (player = 0; player < 2; player++) {
			// loop until valid input
			do {
				update_frame(grid);
				if (!valid) printf("-- Enter appropriate column number --\n\n");
				col = user_input(player);
				valid = validate_move(grid, col);
			} while (!valid);

			// set to grid
			set_grid(grid, col, player);

			// check if win or draw
			win = game_win_status(grid, col, player);

			if (win) {
				break;
			}
		}
	}
	
	// display screen for WIN of player
	game_end_display(grid, player, true);

	// reset color to default
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	return 0; // end
} // end main()


char **create_game_grid()
{
	// creates double pointer for number of rows
	char **grid = (char **)malloc(sizeof(char *) * rows);

	// creates single pointers and sets them in all rows
	for (int i = 0; i < rows; i++) grid[i] = (char *)malloc(sizeof(char) * cols);

	// initializing as default
	for (int i = 0; i < rows; i++) memset(grid[i], X, cols);

	return grid;
} // end create_game_grid()


void color_char(char player)
{
	switch (player) {
        case P1:
        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf("%c", player); // Red color for P1
            break;
        case P2:
        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            printf("%c", player); // Blue color for P2
            break;
        case X:
        	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("%c", player); // White color for X
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
} // end color_char()


void print_grid(char **grid)
{
	
	printf("%-4c", ' ');
	for (int i = 0; i < cols; i++) {
		printf("%-4d", i+1);
	}
	printf("\n");
	printf("%-2c|", ' ');
	for (int i = 2; i <= cols*4; i++) printf("%c", '-');
	printf("|");

	printf("\n");
	for (int i = 0; i < rows; i++) {
		printf("%d | ", i+1);
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1) {
				color_char(grid[i][j]);
				printf(" |");
				break;
			}
			color_char(grid[i][j]);
			printf("%-3c", ' ');
		}
		if (i == rows - 1) continue;
		printf("\n");
		printf("%3c", '|');
		for (int i = 2; i < cols*4; i++) printf("%c", ' ');
		printf(" |\n");
	}
	printf("\n");
	printf("%-2c|", ' ');
	for (int i = 2; i <= cols*4; i++) printf("%c", '-');
	printf("|\n\n");
} // end print_grid(Player **)


void update_frame(char **grid)
{
	// clear screen and print grid
	system("cls");
	print_grid(grid);
} // end update_frame()


int user_input(int player)
{
	char col;
	printf("Enter column number for Player %d: ", player+1);
	scanf(" %c", &col);

	return col-'1';
} // user_input(int)


bool validate_move(char **grid, int col)
{
    // range check and overflow check
    return (col < cols && col >= 0) ? grid[0][col] == X : false;
} // end validate_move()


int get_first_empty(char **grid, int col)
{
	int i = rows-1;
	for (i; i >= 0; i--)
		// loop from bottom until first non player character found
		if (grid[i][col] != X) continue;
		else break;
	return i;
} // end get_first_empty()


void set_grid(char **grid, int col, int player)
{
	// get row where empty slot
	int row = get_first_empty(grid, col);
	grid[row][col] = (player) ? P1 : P2;
} // end set_grid()


bool game_win_status(char **grid, int col, int player)
{
	// getting row of current player character
	char player_char = (player) ? P1 : P2;
	int row = get_first_empty(grid, col)+1;

	// down
	if (row + 3 < rows) {
		if (grid[row+1][col] == player_char && grid[row+2][col] == player_char && grid[row+3][col] == player_char)
				return true;
	}

	// right
	if (col + 3 < cols) {
		if (grid[row][col+1] == player_char && grid[row][col+2] == player_char && grid[row][col+3] == player_char)
				return true;
	}

	// left
	if (col - 3 >= 0) {
		if (grid[row][col-1] == player_char && grid[row][col-2] == player_char && grid[row][col-3] == player_char)
				return true;
	}

	// up right
	if (col + 3 < cols && row - 3 >= 0) {
		if (grid[row-1][col+1] == player_char && grid[row-2][col+2] == player_char && grid[row-3][col+3] == player_char)
				return true;
	}


	// up left
	if (col - 3 >= 0 && row - 3 >= 0) {
		if (grid[row-1][col-1] == player_char && grid[row-2][col-2] == player_char && grid[row-3][col-3] == player_char)
				return true;
	}

	// down right
	if (col + 3 < cols && row + 3 < rows) {
		if (grid[row+1][col+1] == player_char && grid[row+2][col+2] == player_char && grid[row+3][col+3] == player_char)
				return true;
	}

	// down left
	if (col - 3 >= 0 && row + 3 < rows) {
		if (grid[row+1][col-1] == player_char && grid[row+2][col-2] == player_char && grid[row+3][col-3] == player_char)
				return true;
	}

	return false;
} // end game_win_status()


bool game_draw_status(char **grid)
{
	// if top row is not full return false
	for (int i = 0; i < cols; i++) if (grid[0][i] == X) return false;
	return true;
} // end game_draw_status()


void game_end_display(char **grid, int player, bool type)
{
	update_frame(grid);
	(type) ? printf("%c WINS", (player) ? P1 : P2) : printf("DRAW");
	display_wins(player);
}


int *save_win(int player)
{
	char line[BUFFER_SIZE];
	int *wins = (int *)calloc(2, sizeof(int));

	//reading wins from file
	FILE *f_ptr = fopen(f_name, "r+");

	// if file exists
	if (f_ptr != NULL) {
		for (int i = 0;!feof(f_ptr); i++) {
			// reading win from file
			fgets(line, BUFFER_SIZE, f_ptr);

			// trimming string
			line[strcspn(line, "\n")] = 0;

			// adding into win of the player
			// ignoring if -1 (DRAW)
			wins[i] = atoi(line) + (player != -1 && i == player);
		}

		fclose(f_ptr);
	} else wins[player] = 1; // setting to 1 if no file exists


	// ending if DRAW
	if (player == -1) return wins;


	// writing new wins in file
	f_ptr = fopen(f_name, "w");

	// if file can be opened
	if (f_ptr != NULL) {
		// writing the wins in to the file
		fprintf(f_ptr, "%d\n%d", wins[0], wins[1]);
		fclose(f_ptr);
	}

	return wins;
} // end save_win()


void display_wins(int player)
{
	// get wins from the file
	int *wins = save_win(player);
	printf("\nTotal %c wins: %d\nTotal %c wins: %d", P1, wins[1], P2, wins[0]);

	// to not immediately close the program at the end
	Sleep(10000);
} // end display_wins()
