# Tic-Tac-Toe
# Tic-Tac-Toe Game (C++)

This is a simple implementation of the classic Tic-Tac-Toe game in C++. It allows both single-player and two-player gameplay, tracks game history, and saves the results for future reference. The game contains functionality which keeps the terminal clean and easy to read.

## Features

- **Single Player Mode (Player vs Computer):** Play Tic-Tac-Toe against a computer opponent.
- **Two Player Mode:** Play Tic-Tac-Toe with a friend (Player vs Player).
- **Game History:** Keep track of previous games and their results, such as wins, losses, and draws.
- **Simple Interface:** Console-based interface with clear instructions and prompts.
- **Random Computer Moves:** The computer makes moves randomly from the available empty positions.

## Prerequisites

- C++ Compiler (e.g., GCC or Visual Studio)
- C++ Standard Library

## How to Run the Game

1. **Clone the repository:**

    ```bash
    git clone https://github.com/your-username/tic-tac-toe.git
    ```

2. **Navigate to the project directory:**

    ```bash
    cd tic-tac-toe
    ```

3. **Compile the code:**
   
    If you are using GCC, run the following command in your terminal:

    ```bash
    g++ -o tictactoe main.cpp
    ```

4. **Run the game:**

    After compilation, run the executable with:

    ```bash
    ./tictactoe
    ```

    The game will launch, and you can choose between the options in the menu.

## Game Instructions

When you start the game, you will be presented with the following options in the menu:

1. **1 Player game:** Play against the computer.
2. **2 Player game:** Play against another person.
3. **Game history:** View the history of past games.
4. **Exit:** Exit the game.

If you choose "1 Player game", you will be prompted to enter your name. Then, you will take turns with the computer to play the game. The computer makes random moves and you will need to make your moves by typing a number between 1-9 that corresponds to an empty space on the board.

If you choose "2 Player game", you will need to enter both players' names. The game alternates between Player 1 (X) and Player 2 (O), and the game continues until there's a winner or the board is full.

You can also view the history of past games by selecting the "Game history" option, which will show the outcomes of previous matches (1 Player or 2 Player) saved in a file.

## Game History Files

- **PvC.txt**: Stores history of games played between the player and the computer (Single Player mode).
- **PvP.txt**: Stores history of games played between two players (Two Player mode).

Each line in the history files will be labeled with the game number and the result.

