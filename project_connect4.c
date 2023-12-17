/*
 * Creators: Fasih Hasan, Syed Ukkashah, Muhammad Ali
 * Desc: A game called connect 4. First player to create a sequence of 4 characters in a row in a 6 by 7 grid will win
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "connect4.h"

#define      BUFFER_SIZE 10
#define SAVE_BUFFER_SIZE 50

#define f_name  "wins.txt"
#define f_save "saves.csv"

#define P1 'R'
#define P2 'B'
#define  X '.'

#define     blue  1
#define      red  4
#define    white 15
#define l_yellow 14

// default settings
const int rows = 6, cols = 7;

// input flag to handle input commands
bool input_flag = false;

int main()
{
	int player, col;
	bool valid = true, win = false;
	char player_char, **grid = create_game_grid();
        start_menu();
	// game loop
	while (!win) {
		// check at the start if draw
		// this was done to avoid out of bound errors mid game
		if (game_draw_status(grid)) {
			// display end screen for DRAW
			game_draw_display(grid, player);
			return 0; // end
		}

		// for each player
		for (player = 0; player < 2; player++) {
			// loop until valid input
			do {
				update_frame(grid);
				if (!valid && !input_flag) printf("-- Enter appropriate column number or command --\n\n");
				input_flag = false;
				col = user_input(grid, &player);
				valid = validate_move(grid, col);
			} while (!valid);

			// set to grid
			set_grid(grid, col, player);

			// check if win or draw
			win = game_win_status(grid, player);

			if (win)
				break;
		}
	}
	
	// display screen for WIN of player
	game_end_display(grid, player);

	// reset color to default
	set_color(white);

	return 0; // end
} // end main()

void start_menu() {
    system("cls");

    // Print "WELCOME" with different colors for each character
    set_color(10); // Green for 'W'
    printf("       W");
    set_color(9); // Blue for 'E'
    printf("E");
    set_color(14); // Yellow for 'L'
    printf("L");
    set_color(11); // Pink for 'C'
    printf("C");
    set_color(13); // Purple for 'O'
    printf("O");
    set_color(12); // Red for 'M'
    printf("M");
    set_color(15); // Reset color to light yellow for the rest of the characters
    printf("E ");

    // Print "TO CONNECT 4!" in red
    set_color(12); // Red for 'T'
    printf("T");
    set_color(15); // Reset color to light yellow for the rest of the characters
    printf("O ");

    set_color(4); // Red for 'C'
    printf("CONNECT ");

    set_color(12); // Red for '4'
    printf("4");

    set_color(15); // Reset text color to light yellow
    printf("!\n\n");

    // Set text color to red for "AFU STUDIOS"
    set_color(4);
    printf("%24s", "AFU STUDIOS\n\n");

    // Reset text color to light yellow
    set_color(15);

    // Print controls with different colors
    printf("%-12s%s\n", "", "CONTROLS:\n");
    set_color(10); // Green for 'r'
    printf("%-12s%s\n", "", "r - reset");
    set_color(13); // Purple for 's'
    printf("%-12s%s\n", "", "s - save");
    set_color(14); // Yellow for 'l'
    printf("%-12s%s\n", "", "l - load");
    set_color(4); // Red for 'e'
    printf("%-12s%s\n", "", "e - exit");

    // Reset text color to light yellow
    set_color(15);
     // Set text color to gold
    set_color(14);
    printf("\n\n");
    printf("%27s\n", "CONNECT 4 RULES\n\n");
    set_color(14);  // Reset text color

    // Print rules with color formatting
    printf("1. The game is played on a vertically standing grid with 6 rows and 7 columns.\n");

    // set_color(4);  // Red color for 'red'
    printf("2. Player red (");
    set_color(4);  // Reset text color
    printf("R");
    set_color(14);  // Red color for 'red'
    printf(") and Player blue (");
    set_color(1);  // Blue color for 'blue'
    printf("B");
    set_color(14);  // Red color for 'red'
    printf(") take turns to drop their colored discs from the top into any of the\n");
    printf("   seven columns.\n");
    printf("3. The disc will then occupy the lowest available space within the chosen column.\n");
    printf("4. The game continues until one of the players achieves four of their discs\n");
    printf("   consecutively in a row, either horizontally, vertically, or diagonally.\n");
    printf("5. The player who connects four discs in a row first wins the game!\n");

    set_color(15);  // Reset text color
     printf("\n    Press any key to continue");

    // Blinking effect
    int blink = 1;
    while (!_kbhit()) {
        // Toggle visibility by moving the cursor to the beginning of the line
        printf("\r");
        if (blink) {
            printf("    Press any key to continue");
        } else {
            printf("                              ");  // Print spaces to clear the line
        }
        blink = !blink;

        // Wait for a short time to control the blinking speed
        Sleep(500);
    }

    // Clear the line after a key is pressed
    printf("\r                              ");
}

char **create_game_grid()
{
	// creates double pointer for number of rows
	char **grid = (char **)malloc(sizeof(char *) * rows);

	// creates a data block for the double pointer
	char *block = (char *)malloc(sizeof(char) * rows*cols);

	// set the pointer locations for the grid
	for (int i = 0; i < rows; i++) grid[i] = &block[i*cols];

	// initialize the grid
	initialize_grid(grid);

	return grid;
} // end create_game_grid()


void initialize_grid(char **grid)
{
	// initializing the grid with X
	for (int i = 0; i < rows; i++) memset(grid[i], X, cols);
} // end initialize_grid()


void set_color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
} // end set_color()


void color_player(char player)
{
	switch (player) {
        case P1:
        	set_color(red);
            printf("%c", player); // Red color for P1
            break;
        case P2:
        	set_color(blue);
            printf("%c", player); // Blue color for P2
            break;
        case X:
        	set_color(white);
            printf("%c", player); // White color for X
    }
    set_color(l_yellow);
} // end color_player()


void print_grid(char **grid)
{
	// default color scheme
	set_color(l_yellow);

	printf("%-4c", ' ');
	for (int i = 0; i < cols; i++) {
		printf("%-4d", i+1);
	}
	printf("\n");
	printf("%-2c\\", ' ');
	for (int i = 2; i <= cols*4; i++) (i & 1) ? printf("%c", '=') : printf("%c", '-');
	printf("/");

	printf("\n");
	for (int i = 0; i < rows; i++) {
		printf("%c | ", i+'a');
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1) {
				color_player(grid[i][j]);
				printf(" |");
				break;
			}
			color_player(grid[i][j]);
			printf("%-3c", ' ');
		}
		if (i == rows - 1) continue;
		printf("\n");
		printf("%3c", '|');
		for (int i = 2; i < cols*4; i++) printf("%c", ' ');
		printf(" |\n");
	}
	printf("\n");
	printf("%-2c/", ' ');
	for (int i = 2; i <= cols*4; i++) (i & 1) ? printf("%c", '=') : printf("%c", '-');
	printf("\\\n\n");
} // end print_grid(Player **)


void update_frame(char **grid)
{
	// clear screen and print grid
	system("cls");
	print_grid(grid);
} // end update_frame()


int user_input(char **grid, int *player)
{
	char input[BUFFER_SIZE];
	printf("Enter column number for Player %d: ", *player+1);

	// using fgets as a safer input than scanf or gets
	fgets(input, BUFFER_SIZE, stdin);

	// removing trailing new line
	input[strcspn(input, "\n")] = 0;

	// exit if user inputs 'e' or 'E'
	if (!strcmp("e", input) || !strcmp("E", input)) {
		printf("%24s", "---- Exiting ----");
		set_color(white);
		Sleep(300);
		exit(EXIT_SUCCESS);
	} 
	// saving wins and showing wins if input is 's' or 'S'
	else if (!strcmp("s", input) || !strcmp("S", input)) {
		printf("%24s", "---- Saving ----");
		Sleep(500);
		save_game(grid, *player);
		input_flag = true;
		return -1;
	}
	// loading game if input is 'l' or 'L'
	else if (!strcmp("l", input) || !strcmp("L", input)) {
		printf("%24s", "---- Loading ----");
		Sleep(200);
		*player = load_game(grid, *player);
		input_flag = true;
		return -1;
	} 
	// restarting game if input is 'r' or 'R'
	else if (!strcmp("r", input) || !strcmp("R", input)) {
		printf("%24s", "---- Resetting ----");
		Sleep(500);
		initialize_grid(grid);
		*player = 0;
		input_flag = true;
		return -1;
	}

	return atoi(input)-1;
} // user_input(int)


bool validate_move(char **grid, int col)
{
    // range check and overflow check
    return (col < cols && col >= 0) ? grid[0][col] == X : false;
} // end validate_move()


int get_first_empty(char **grid, int col)
{
	int i = rows-1;
	for (i; i >= 0 && grid[i][col] != X; i--);
		// loop from bottom until first non player character found
	return i;
} // end get_first_empty()


void set_grid(char **grid, int col, int player)
{
	// get row where empty slot
	int row = get_first_empty(grid, col);
	grid[row][col] = (player) ? P1 : P2;
} // end set_grid()


bool game_win_status(char **grid, int player)
{
	// getting row of current player character
	char player_char = (player) ? P1 : P2;

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			// down
			if (row + 3 < rows) {
				if (grid[row][col] == player_char && grid[row+1][col] == player_char && grid[row+2][col] == player_char && grid[row+3][col] == player_char)
					return true;
			}

			// right
			if (col + 3 < cols) {
				if (grid[row][col] == player_char && grid[row][col+1] == player_char && grid[row][col+2] == player_char && grid[row][col+3] == player_char)
					return true;
			}

			// left
			if (col - 3 >= 0) {
				if (grid[row][col] == player_char && grid[row][col-1] == player_char && grid[row][col-2] == player_char && grid[row][col-3] == player_char)
					return true;
			}

			// up right
			if (col + 3 < cols && row - 3 >= 0) {
				if (grid[row][col] == player_char && grid[row-1][col+1] == player_char && grid[row-2][col+2] == player_char && grid[row-3][col+3] == player_char)
					return true;
			}


			// up left
			if (col - 3 >= 0 && row - 3 >= 0) {
				if (grid[row][col] == player_char && grid[row-1][col-1] == player_char && grid[row-2][col-2] == player_char && grid[row-3][col-3] == player_char)
					return true;
			}

			// down right
			if (col + 3 < cols && row + 3 < rows) {
				if (grid[row][col] == player_char && grid[row+1][col+1] == player_char && grid[row+2][col+2] == player_char && grid[row+3][col+3] == player_char)
					return true;
			}

			// down left
			if (col - 3 >= 0 && row + 3 < rows) {
				if (grid[row][col] == player_char && grid[row+1][col-1] == player_char && grid[row+2][col-2] == player_char && grid[row+3][col-3] == player_char)
					return true;
			}
		}
	}

	return false;
} // end game_win_status()


bool game_draw_status(char **grid)
{
	// if top row is not full return false
	for (int i = 0; i < cols; i++) if (grid[0][i] == X) return false;
	return true;
} // end game_draw_status()


void game_draw_display(char **grid, int player)
{
	update_frame(grid);
	printf("DRAW");
	display_wins(-1);
} // game_draw_display()


void game_end_display(char **grid, int player)
{
	update_frame(grid);
	set_color((player) ? 4 : 1);
	printf("%13c", ' ');
	printf("%s ", (player) ? "RED" : "BLUE");
	set_color(l_yellow);
	printf("WINS!\n");
	display_wins(player);
} // game_end_display()


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

	for (int i = 1; i >= 0; i--) {
		printf("\n%6cTotal  ", ' ');
		set_color(i ? red : blue);
		printf("%4s ", i ? "RED" : "BLUE");
		set_color(l_yellow);
		printf(" wins: %2d", wins[i]);
	}

	// to not immediately close the program at the end
	Sleep(5000);
} // end display_wins()


int load_game(char **grid, int player) {
	FILE *fp = fopen(f_save, "r");

	if (fp == NULL) {
		printf("%24s", "---- No Saves ----");
		Sleep(300);
		return player;
	}

	char save_str[SAVE_BUFFER_SIZE];

	// retrieve saved game data from file
	fgets(save_str, SAVE_BUFFER_SIZE, fp);

	// copy each row into grid
	for (int i = 0; i < rows; i++)
		strncpy(grid[i], &save_str[i*cols], cols);

	// return the player turn
	return save_str[strlen(save_str)-1]-'0';
} // load_game()


void save_game(char **grid, int player)
{
	FILE *fp = fopen(f_save, "w");
	char save_str[SAVE_BUFFER_SIZE];
	memset(save_str, 0, SAVE_BUFFER_SIZE);

	// using strncat to concat to limit the upper bound
	for (int i = 0; i < rows; i++) strncat(save_str, grid[i], cols);

	// convert char int to string
	char player_str[3];
	sprintf(player_str, ",%d", player);

	// append player to string
	strcat(save_str, player_str);

	// save array data to file
	fputs(save_str, fp);

	fclose(fp);
} // end save_game()
