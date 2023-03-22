#include <iostream>
#include <vector>
#include <cctype>
#include <stdlib.h> 
#include <limits>
using namespace std;

//Functions
void printBoard(vector<vector<char>> board) {

    cout << "\n";
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << " " << board[i][j] << " ";
            if (j != board[i].size() - 1) {
                cout << "|";
            }
        }
        cout << endl;
        if (i != board.size() - 1) {
            for (int j = 0; j < board[i].size(); j++) {
                cout << "---";
                if (j != board[i].size() - 1) {
                    cout << "+";
                }
            }
            cout << endl;
        }
    }
    cout << "\n";
}

bool isWinner(const vector<vector<char>>& board, char player){
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player) {
            return true;
        }
    }
    
    // Check columns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == player && board[1][col] == player && board[2][col] == player) {
            return true;
        }
    }
    
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    
    // No win conditions met
    return false;
}

bool isTie(const vector<vector<char>>& board){
    // Check if any spaces are still empty
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == ' ') {
                return false;
            }
        }
    }
    
    // No empty spaces left, so it's a tie
    return true;
}

pair<int, int> getUserMove(const vector<vector<char>>& board) {
    int row, col;
    while (true) {
        cout << "Enter row number (1-3) of your move: ";
        cin >> row ;
        cout << "\n";
        cout << "Enter column number(1-3) of your move: ";
        cin >> col;
        row--;
        col--;
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid input. Please enter numbers between 1 and 3." << endl;
        } else if (board[row][col] != ' ') {
            cout << "That space is already taken. Please choose another one." << endl;
        } else {
            break;
        }
    }
    return make_pair(row, col);
}

// Minimax algorithm
int minMax(const vector<vector<char>>& board, int depth, bool isMaximizing, char symbol) {
    // Base cases
    if (isWinner(board, 'O')) {
        return 10 - depth;
    } else if (isWinner(board, 'X')) {
        return depth - 10;
    } else if (isTie(board)) {
        return 0;
    }
    
    // Recursive cases
    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    vector<vector<char>> newBoard = board;
                    newBoard[i][j] = symbol;
                    int score = minMax(newBoard, depth + 1, false, symbol);
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    vector<vector<char>> newBoard = board;
                    newBoard[i][j] = (symbol == 'O' ? 'X' : 'O');
                    int score = minMax(newBoard, depth + 1, true, symbol);
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

pair<int, int> getComputerMoveMinimax(const vector<vector<char>>& board, char symbol) {
    // Initialize best move
    pair<int, int> bestMove = make_pair(-1, -1);
    int bestScore = -1000;
    
    // Iterate over all empty cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // Make a move on the empty cell
                vector<vector<char>> newBoard = board;
                newBoard[i][j] = symbol;
                
                // Determine the score for the move using Minimax algorithm
                int score = minMax(newBoard, 0, false, symbol);
                
                // If the score is better than the current best score, update best move and score
                if (score > bestScore) {
                    bestMove = make_pair(i, j);
                    bestScore = score;
                }
            }
        }
    }
    
    // Return the best move
    return bestMove;
}

//Main
int main(){

    //Game Variables
    vector<vector<char>> board {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char playerSymbol = 'X';
    char computerSymbol = 'O';
    bool playerTurn = false;

    while (true) {
        // Print current board
        printBoard(board);
        
        // Check if game is over
        if (isWinner(board, playerSymbol)) {
            cout << "You win!" << endl;
            break;
        } else if (isWinner(board, computerSymbol)) {
            cout << "You lose!" << endl;
            break;
        } else if (isTie(board)) {
            cout << "It's a tie!" << endl;
            break;
        }
        
        // Player turn
        if (playerTurn) {

            // Get player move
            pair<int, int> move = getUserMove(board);
            int row = move.first;
            int col = move.second;
            
            // Update board
            board[row][col] = playerSymbol;
            
            // Switch to computer turn
            playerTurn = false;

        } 

        // Computer turn
        else {

            // Get computer move
            pair<int, int> move = getComputerMoveMinimax(board, computerSymbol);
            int row = move.first;
            int col = move.second;
            
            // Update board
            board[row][col] = computerSymbol;
            
            // Switch to player turn
            playerTurn = true;

        }

    }

    // Game over
    printBoard(board);

}