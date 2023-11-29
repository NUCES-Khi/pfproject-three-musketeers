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

// print the game grid
void print_grid(char **grid);

// user input for the column number
int user_input(int player); 

// validate a move in the specified column
bool validate_move(char **grid, int col);

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

