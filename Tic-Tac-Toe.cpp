#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Function prototypes
void printBoard(char[][3], int);
bool move_validator(char[][3], int, char);
char winner(char[][3], int);
void computer_move(char[][3], int);
void one_player(char[][3], int);
void two_player(char[][3], int);
void fetch_history(const string &);
void save_data(const string &, string);
void game_history();

// Main function
int main()
{
    // Defining an array for the board and a variable to control the repetition of the program
    int choice;

    // Constant integer for board size
    const int size = 3;

    do
    {
        // Defining an array for the board and setting it to default
        char board[size][size] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

        // Display the menu
        cout << " TIC-TAC-TOE" << endl;
        cout << "==== Menu ====" << endl;
        cout << "1. 1 Player game" << endl;
        cout << "2. 2 Player game" << endl;
        cout << "3. Game history" << endl;
        cout << "4. Exit Program" << endl
             << endl;

        // Get user input
        cout << "Please select an option from the menu: ";
        cin >> choice;

        // Clear the input buffer
        cin.ignore(10000, '\n');

        // Check if the input is valid
        if (cin.fail())
        {
            cin.clear();            // Clear the fail state
            cin.ignore(1000, '\n'); // Ignore the invalid input up to the newline character
        }

        // Process the user's choice
        if (choice == 1)
        {
            // Clear the output screen
            system("cls");

            cout << "====1 PLAYER GAME====" << endl;

            // Call the function to play the 1-player game
            one_player(board, size);
        }

        else if (choice == 2)
        {
            // Clear the screen
            system("cls");

            cout << "====2 PLAYER GAME====" << endl;

            // Call the function to play the 2-player game
            two_player(board, size);
        }

        else if (choice == 3)
        {
            // Clear the screen
            system("cls");

            cout << "===GAME HISTORY===" << endl;

            // Call the function for game history
            game_history();
        }

        else if (choice == 4)
        {
            // Exiting program
            system("cls");

            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        else
        {
            // Clear the screen
            system("cls");

            // Error message for invalid choice
            cout << "Invalid choice. Please enter a number (1 - 4)." << endl;
        }

    } while (true);

    return 0;
}

// Function to print the Tic-Tac-Toe board
void printBoard(char arr[][3], int size)
{
    // For loop runs for each row
    for (int i = 0; i < size; i++)
    {
        // Print empty lines to create spacing
        cout << setw(15) << "\t|\t" << "\t|\t" << endl
             << endl;

        // Print the row content with separators
        cout << setw(10) << arr[i][0] << "\t|\t" << arr[i][1] << "\t|\t" << arr[i][2] << endl
             << endl;

        // Print empty lines to create spacing
        cout << setw(15) << "\t|\t" << "\t|\t" << endl
             << endl;

        // Print horizontal line separator, but only if it's not the last row
        if (i == size - 1)
        {
            break;
        }
        cout << "   -------------------------------------------" << endl;
    }
}

// Function to validate the user's move and update the board
bool move_validator(char arr[][3], int size, char symbol)
{
    // Variable to store the move
    char move;

    // Variable to track if the move is done successfully
    bool done = false;

    // Pointer to navigate through the array
    char *ptr = &arr[0][0];

    // Getting input from the user
    cin >> move;

    // Clear screen
    system("cls");

    // Check if the input is longer than one character
    if (cin.fail() || cin.peek() != '\n')
    {
        cout << "Invalid input. Please enter a number (1-9)." << endl;

        cin.clear();             // Clear the error flag
        cin.ignore(10000, '\n'); // Discard the input buffer

        return done;
    }
    else
    {
        // Clear the newline character from the buffer
        cin.ignore();

        // Check if the move is within the valid range (1-9)
        if (move >= '1' && move <= '9')
        {
            // Iterate through each element of the 2D array
            for (int i = 0; i < size * size; i++)
            {
                // If the move matches the current position on the board
                if (move == *ptr)
                {
                    // Update the board
                    *ptr = symbol;

                    done = true;
                    return done;
                }

                // Increment pointer to the next element
                ptr++;
            }

            // If no match is found
            if (!done)
            {
                // Print a message to select an empty position
                cout << "Please select an empty position." << endl
                     << endl;
                return done;
            }
        }
        else
        {
            // If the move is not within the valid range, print an error message
            cout << "Invalid input. Please enter a valid option (1-9)." << endl
                 << endl;
        }
    }
    return done;
}

// Function to check if someone won the game or not
char winner(char arr[][3], int size)
{
    // Variable which will be returned is set to 'N' by default (No winner yet)
    char r_winner = 'N';

    // Checking if there is any winner from rows or columns
    for (int i = 0; i < size; i++)
    {
        // Check rows
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
        {
            // Update return variable by the winning player's mark
            r_winner = arr[i][0];
        }

        // Check columns
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i])
        {
            // Update return variable by the winning player's mark
            r_winner = arr[0][i];
        }
    }

    // Checking principal diagonal
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
    {
        // Update return variable by the winning player's mark
        r_winner = arr[0][0];
    }

    // Checking anti-diagonal
    if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])
    {
        // Update return variable by the winning player's mark
        r_winner = arr[0][2];
    }

    // Return the winning player's mark or 'N' if no winner yet
    return r_winner;
}

// Function for the computer to make a random move on the Tic-Tac-Toe board
void computer_move(char arr[][3], int size)
{
    // Variable to track if the move is done successfully and to store the random move
    bool done = false;
    int move;

    // Seed for the random number generator based on the current time
    int x = time(0);
    srand(x);

    // Keep generating a random move until a valid move is found
    do
    {
        // Generate a random number between 1 and 9
        move = (rand() % 9) + 1;

        // Find the row and column of the move
        int row = (move - 1) / size;
        int col = (move - 1) % size;

        // Check if the selected position is not already marked
        if (arr[row][col] != 'X' && arr[row][col] != 'O')
        {
            // Print computer move
            cout << "Computer move: " << move << endl
                 << endl;

            // Update board
            arr[row][col] = 'O';

            done = true;
        }

    } while (!done); // Continue the loop until a valid move is made
}

// Function for the 1-player game
void one_player(char arr[][3], int size)
{
    // Variables for the player names and game result
    string p1, string_result;

    // Variable to store the winning character
    char result;

    // Prompting player 1 to enter his name
    cout << "Enter your name p1:";
    getline(cin, p1);

    // Clear the screen
    system("cls");

    // Initiate a counter to track the number of moves
    int i = 0;

    // Game loop
    do
    {
        bool validmove;

        // Player 1's turn
        do
        {
            // Printing the board
            printBoard(arr, size);

            // Ask player 1 for their move
            cout << p1 << "(X) please make your move: ";

            // Call move validator function to get the input and check if the move is valid
            validmove = move_validator(arr, size, 'X');

        } while (!validmove);

        // Increment move counter
        i++;

        // Check if player 1 won the game by calling winner function
        result = winner(arr, size);

        if (result == 'X')
        {
            // Print final board
            printBoard(arr, size);

            cout << "Congratulations! " << p1 << " has won." << endl;

            // Save the result to a file by calling the save_data function
            string_result = p1 + " won against the computer.";
            save_data("PvC.txt", string_result);

            break;
        }

        // Check for a draw
        if (i == 9)
        {
            // Print final board
            printBoard(arr, size);

            cout << "It's a draw! No one won." << endl;

            // Save the result to a file by calling the save_data function
            string_result = p1 + " and the computer had a Draw.";
            save_data("PvC.txt", string_result);

            break;
        }

        // Getting computer's move by calling the function
        computer_move(arr, 3);

        // Increment move counter
        i++;

        // Check if the computer won the game by calling winner function
        result = winner(arr, size);

        if (result == 'O')
        {
            // Print final board
            printBoard(arr, size);

            cout << "The computer has won. (-_-)" << endl;

            // Save the result to a file by calling the save_data function
            string_result = "The computer won against " + p1 + ".";
            save_data("PvC.txt", string_result);

            break;
        }

    } while (i < 10);

    // Prompt the user to go back to the main menu
    char exit;
    cout << "Please enter any key to go back to the main menu:";
    cin >> exit;

    // Clear the screen
    system("cls");
}

// Function for the 2-player game
void two_player(char arr[][3], int size)
{
    // Variables for the player names and game result
    string p1, p2, string_result;

    // Variable to store the winning character
    char result;

    // Prompting player 1 to enter their name
    cout << "Enter your name p1:";
    getline(cin, p1);

    // Prompting player 2 to enter their name
    cout << "Enter your name p2:";
    getline(cin, p2);

    // Clear screen
    system("cls");

    // Initiate a counter to track the number of moves
    int i = 0;

    // Game loop
    do
    {
        bool validmove;

        // Player 1's turn
        do
        {
            // Print the board
            printBoard(arr, size);

            // Ask player 1 for their move
            cout << p1 << "(X) please make your move: ";

            // Call move validator function to get the input and check if the move is valid
            validmove = move_validator(arr, size, 'X');

        } while (!validmove);

        // Increment move counter
        i++;

        // Check if player 1 won the game by calling winner function
        result = winner(arr, size);

        if (result == 'X')
        {
            // Display final board
            printBoard(arr, size);

            cout << "Congratulations! " << p1 << " has won." << endl;

            // Save the result to a file by calling the save_data function
            string_result = p1 + " won against " + p2 + ".";
            save_data("PvP.txt", string_result);

            break;
        }

        // Check for a draw
        if (i == 9)
        {
            // Display final board
            printBoard(arr, size);

            cout << "It's a draw! No one won." << endl;

            // Save the result to a file by calling the save_data function
            string_result = p1 + " and " + p2 + " had a Draw.";
            save_data("PvP.txt", string_result);

            break;
        }

        // Player 2's turn
        do
        {
            // Print the board
            printBoard(arr, size);

            // Ask player 2 for their move
            cout << p2 << "(O) please make your move: ";

            // Call move validator function to get the input and check if the move is valid
            validmove = move_validator(arr, size, 'O');

        } while (!validmove);

        // Increment move counter
        i++;

        // Check if player 2 won the game by calling winner function
        result = winner(arr, size);

        if (result == 'O')
        {
            // Display final board
            printBoard(arr, size);

            cout << "Congratulations! " << p2 << " has won." << endl;

            // Save the result to a file by calling the save_data function
            string_result = p2 + " won against " + p1 + ".";
            save_data("PvP.txt", string_result);

            break;
        }
    } while (i < 10);

    // Prompt the user to go back to the main menu
    char exit;
    cout << "Please enter any key to go back to the main menu:";
    cin >> exit;

    // Clear the screen
    system("cls");
}

// Function to print the game history
void fetch_history(const string &filename)
{
    // Declaring a string to store each line
    string line;

    // Open the file
    ifstream file(filename);

    // Read and print each line
    while (getline(file, line))
    {
        cout << line << endl;
    }

    // Close the file
    file.close();
}

// Function to save the game result to a file
void save_data(const string &filename, string result)
{
    // Declaring variables to store the last line, new line and game number
    string line, new_line;
    int game_number = 0;

    // Open the file for reading
    ifstream fileread(filename);

    // Read each line in the file
    while (getline(fileread, line))
    {
        int i = 5;
        int j = 1;

        // Extract game number from the line
        while (line.substr(i, 1) != " ")
        {
            game_number = stoi(line.substr(5, j));
            i++;
            j++;
        }
    }

    // Increment game number
    game_number++;

    // Close the file
    fileread.close();

    // Open the file for writing in append mode
    ofstream filewrite(filename, ios::app);

    // Create a new line with the game result
    new_line = "Game " + to_string(game_number) + " : " + result;

    // Write the new line to the file
    filewrite << new_line << endl;

    // Close the file
    filewrite.close();
}

// Function to display game history menu
void game_history()
{
    do
    {
        // Variable to get input for the menu
        int option;

        // Display the game history menu
        cout << "1. 1-Player history" << endl;
        cout << "2. 2-Player history" << endl;
        cout << "3. Back" << endl;

        // Prompt user for input
        cout << "Please select an option from menu: ";
        cin >> option;

        // Validate user input
        if (cin.fail())
        {
            cin.clear();           // Clear the fail state
            cin.ignore(100, '\n'); // Ignore the invalid input up to the newline character

            // Clear the screen
            system("cls");
        }

        // Process the user input
        if (option == 1)
        {
            // Clear the screen
            system("cls");

            cout << "1-Player Game Results: " << endl
                 << endl;

            // Call the function to get the 1-player history
            fetch_history("PvC.txt");

            cout << endl
                 << endl
                 << endl;
        }
        else if (option == 2)
        {
            // Clear the screen
            system("cls");

            cout << "2-Player Game Results: " << endl
                 << endl;

            // Call the function to get the 2-player history
            fetch_history("PvP.txt");

            cout << endl
                 << endl
                 << endl;
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            // Clear the screen
            system("cls");

            // Display error message for invalid input
            cout << "Invalid option. Please enter a number between 1-3." << endl;
        }
    } while (true);
}
