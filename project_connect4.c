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

// update the frame by clearing the screen and printing the grid
void update_frame(char **grid);

// print the game grid
void print_grid(char **grid);

// user input for the column number
int user_input(int player); 

// validate a move in the specified column
bool validate_move(char **grid, int col);

// get the first empty row in a column
int get_first_empty(char **grid, int col);

// set the grid at the specified column and row with the player's character
void set_grid(char **grid, int col, int player);


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
