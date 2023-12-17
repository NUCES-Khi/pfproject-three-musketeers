# Connect4: A game
## Fasih Hassan Khan 23K-0018
## Ukkashah Ahmed 23K-0055
## Muhammad Ali 23K-0052

# Video demo for the game
https://github.com/NUCES-Khi/pfproject-three-musketeers/assets/47947561/dd806924-799c-4907-a5b6-86564f0af11c

# Overview:
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


We kindly request your feedback and approval of this project proposal. Your guidance will be invaluable as we work on creating the "Four in a Row" game in C.

Sincerely,\
Fasih Hasan Khan (23K-0018)\
Syed Ukkashah Ahmed Shah (23K-0055)\
Muhammad Ali (23K-0052)\
Email for contact:\
k230052@nu.edu.pk

## Future Work to do
Update filing and make ouput more better looking\
Add a save and load game option
Check and test the win coditions
