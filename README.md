# Connect4: A game
## Fasih Hassan Khan 23K-0018
## Ukkashah Ahmed 23K-0055
## Muhammad Ali 23K-0052

# Video demo for the game
https://github.com/NUCES-Khi/pfproject-three-musketeers/assets/47947561/dd806924-799c-4907-a5b6-86564f0af11c

# Proposal Idea/Overview:
This project is about a game called Connect4. The game's rules are simple and have been demonstrated clearly in the video.

# Project Description:
### The project is divided into multiple sections
> - Game functions
> - Filing functions
> - Misc functions

## Game functions
This section will cover the primary game functions only.

1. User input
This function takes every input in string. The reason why we used this approach was to prevent possible game crashes in case the user enters nothing.
Moreover, this also allows us to take both types of inputs:
- Character inputs (for commands)
- Integer inputs (for a move)
The use of a global flag is necessary to not cause disturbances in the flow of the game. This way, the user input function is able to communicate with the main
function and control said flow.
2. Game win status
This function is for the main logic of the game. It checks for a pattern of 4 on each player's turn. The time complexity for this algorithm is O(n^2). Considering
our grid size, the algorithm's time complexity is not a problem when it comes to the performance.
The function checks for each element in the grid, patterns in multiple directions. Down, left, right, up-right, up-left, down-right and down-left. There is no up check
as it's simply not possible for the game to have that pattern.
3. Game draw status
This function only checks the top row. If it is full, it would declare the game as drawed.

All of these functions are incorporated into the main function.

## Filing functions
This section will discuss the primary filing functions

1. Save win
This function takes the player that won. In case it is -1, that means no player won and that the game has been drawn.
If the wins file exists, it reads the wins for both players. Adds the current win to the player who won and then saves it back
Otherwise it simply creates a new file and adds the win in for the player who won.
It also returns an array of wins that other functions make use of

2. Save game
This function takes the grid and writes it into a csv file. The player turn is also stored alongside in order to let that player start off from where they saved

3. Load game
This function loads the game content from the saved csv file (if it exists) and initializes the grid content.
```c
for (int i = 0; i < rows; i++)
    strncpy(grid[i], &save_str[i*cols], cols);
```
It copies the first n-elements from the save_str variable, and into the grid at the i-th row. & converts the array to a pointer (string).

## Misc functions
This section will speak of the primary misc functions.

1. set color
This function makes use of the `Windows.h` library to change the color of the console text. The syntax for this is simply copied via sources online, as there
is nothing too logical about it.
```c
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
```

3. update frame
This function clears the screen and prints the grid.

4. print grid
This function prints the grid. The procedure is solely based on trial and error. There is no logic, rhyme or rythm to it.

5. Menu
Prints the menu. It is to let the user get familiar with the game rules and the commands that come along with it.

# Datastructures used
We used a plain 2D array. Our game is grid based and 2D arrays are best in this domain
The allocation for our array was contigious as this allowed is to easily extract the content from it when saving into the file.
The method to insert into our grid is slightly unorthodox. This game is supposed to simulate the real game where each coin is
dropped into the grid; therefore, we made every new element "drop" into the grid by inserting it into the first "clear" index in
the column.

# Hurdles
The biggest hurdle was the game win status.
There were many issues with it, and it took a lot of time to resolve them. Regardless, they have all been resolved now.
Other hurdles were the filing functions. Not necessarily their functionality, but it has more to do with how they
were to be implemented to ensure better code readability

# Main Algorithm
The overall time complexity for the algorithm for now has no room for improvement. However, it is possible that there exists a faster solution out there
