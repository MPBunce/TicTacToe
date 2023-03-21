#include <iostream>
#include <vector>
#include <cctype>
#include <stdlib.h> 
#include <limits>
using namespace std;

//Functions
void printBoard( vector<vector<char>> theMatrix ){

    cout << "\n**************************\n\n";

    cout << "       |         |      \n";
    cout << "   " << theMatrix[0][0] << "   |    " << theMatrix[0][1] << "    |    " << theMatrix[0][2] << "\n";    
    cout << "       |         |      " << "\n";
    cout << "--------------------------" << "\n";
    cout << "       |         |      \n";
    cout << "   " << theMatrix[1][0] << "   |    " << theMatrix[1][1] << "    |    " << theMatrix[1][2] << "\n";    
    cout << "       |         |      " << "\n";
    cout << "--------------------------" << "\n";
    cout << "       |         |      " << "\n";
    cout << "   " << theMatrix[2][0] << "   |    " << theMatrix[2][1] << "    |    " << theMatrix[2][2] << "\n";    
    cout << "       |         |      " << "\n";

    cout << "\n**************************\n";

}

vector<vector<char>> getUserInput( vector<vector<char>> theMatrix, char inputChar ){
    
    bool correctInput = true;
    int userChoice = 0;


    while(correctInput){

        cout << "\nEnter where you want to place: \n";
        cin >> userChoice;

        userChoice = toupper(userChoice);

        switch (userChoice){
            case 1:
                theMatrix[0][0] = inputChar;
                correctInput = false;
                return theMatrix;
            case 2:
                theMatrix[0][1] = inputChar;
                correctInput = false;
                return theMatrix;
            case 3:
                theMatrix[0][2] = inputChar;
                correctInput = false;
                return theMatrix;
            case 4:
                theMatrix[1][0] = inputChar;
                correctInput = false;
                return theMatrix;
            case 5:
                theMatrix[1][1] = inputChar;
                correctInput = false;
                return theMatrix;
            case 6:
                theMatrix[1][2] = inputChar;
                correctInput = false;
                return theMatrix;
            case 7:
                theMatrix[2][0] = inputChar;
                correctInput = false;
                return theMatrix;
            case 8:
                theMatrix[2][1] = inputChar;
                correctInput = false;
                return theMatrix;
            case 9:
                theMatrix[2][2] = inputChar;
                correctInput = false;
                return theMatrix;
            default:
                cout << "Error Please try again!\n";    
        }

    }

    return theMatrix;

}

vector<vector<char>> computerRandom(vector<vector<char>> theMatrix, char inputChar){
    
    vector<char> avaliablePositions;
    int randomPosition = 0;

    for(int i = 0; i < theMatrix.size(); ++i){
        for(int j = 0; j < theMatrix.size(); ++j){
            if(theMatrix[i][j] != 'X' && theMatrix[i][j] != 'O'){
                avaliablePositions.push_back(theMatrix[i][j]);
            }
        }
    }

    // for(int i = 0; i < avaliablePositions.size(); ++i){
    //     cout << avaliablePositions[i] << "Random Check"<< (rand() % avaliablePositions.size())<< "\n";
    // }

    randomPosition = (rand() % avaliablePositions.size());
    
    // cout << "\nPossible Random Position  :  " << randomPosition << "\n";

    for(int i = 0; i < theMatrix.size(); ++i){
        for(int j = 0; j < theMatrix.size(); ++j){
            if(theMatrix[i][j] == avaliablePositions[randomPosition]){
                theMatrix[i][j] = inputChar;
            }
        }
    }


    return theMatrix;

}

int isWinner( vector<vector<char>> theMatrix, char inputChar ){

    //return 0 for nothjing
    //return 1 for X win
    //return 2 for O win
    //return 3 for tie!
    vector<char> avaliablePositions;

    //No Tie did someone win?
    for(int i = 0; i < theMatrix.size(); ++i){
        if(theMatrix[i][0] == theMatrix[i][1] && theMatrix[i][1] == theMatrix[i][2]){
            if(inputChar == 'X'){
                return 1;
            }else{
                return 2;
            }

        }
    }

    for(int i = 0; i < theMatrix.size(); ++i){
        if(theMatrix[0][i] == theMatrix[1][i] && theMatrix[1][i] == theMatrix[2][i]){
            if(inputChar == 'X'){
                return 1;
            }else{
                return 2;
            }

        }
    }

    if( theMatrix[0][0] == inputChar && theMatrix[1][1] == inputChar && theMatrix[2][2] == inputChar ){

        if(inputChar == 'X'){
            return 1;
        }else{
            return 2;
        }

    }else if( theMatrix[0][2]  == inputChar && theMatrix[1][1]  == inputChar && theMatrix[2][0] == inputChar ){

        if(inputChar == 'X'){
            return 1;
        }else{
            return 2;
        }

    }else{

        return 0;

    }

    //Check Tie
    for(int i = 0; i < theMatrix.size(); ++i){
        for(int j = 0; j < theMatrix.size(); ++j){
            if(theMatrix[i][j] != 'X' && theMatrix[i][j] != 'O'){
                avaliablePositions.push_back(theMatrix[i][j]);
            }
        }
    }

    if(avaliablePositions.size() < 1){
        return 3;
    }

}


vector<vector<char>>findBestMove(vector<vector<char>> board, char inputChar)
{

    pair<int, int> bestMove = {-1, -1};
    char placeHolder = ' ';
    int bestScore = numeric_limits<int>::min();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] =! 'X' || board[i][j] != 'O') {
                placeHolder = board[i][j];
                board[i][j] = inputChar;
                int score = minimax(board, 'O', 0);
                board[i][j] = placeHolder;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }

    board[ bestMove.first ][ bestMove.second ] = inputChar;
    return board;
}

int minimax(std::vector<std::vector<char>>& board, char player, int depth)
{
    // Check if the game is over
    char winner = checkWinner(board);
    if (winner == COMPUTER_PLAYER) {
        return 10 - depth;
    } else if (winner == HUMAN_PLAYER) {
        return depth - 10;
    } else if (isBoardFull(board)) {
        return 0;
    }

    // Recursively call minimax on all possible moves
    int bestScore;
    if (player == COMPUTER_PLAYER) {
        bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY_CELL) {
                    board[i][j] = COMPUTER_PLAYER;
                    int score = minimax(board, HUMAN_PLAYER, depth + 1);
                    board[i][j] = EMPTY_CELL;
                    bestScore = std::max(bestScore, score);
                }
            }
        }
    } else {
        bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY_CELL) {
                    board[i][j] = HUMAN_PLAYER;
                    int score = minimax(board, COMPUTER_PLAYER, depth + 1);
                    board[i][j] = EMPTY_CELL;
                    bestScore = std::min(bestScore, score);
                }
            }
        }
    }
    return bestScore;
}

//Main
int main(){

    //Game Variables
    vector<vector<char>> gameBoard = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
    };

    char easyOrHard = ' ';
    bool gameFlag = true;
    int winner = 15;
    char inputX = 'X';
    char inputO = 'O';

    cout << "Welcome to tic tac toe!\n";
    cout << "Easy mode or hard mode (E or H)?: \n";
    cin >> easyOrHard;

    easyOrHard = toupper(easyOrHard);

    cout<< "\n";

    if(easyOrHard == 'E'){
        while(gameFlag){

            //print board
            printBoard(gameBoard);

            //get user input and apply change
            gameBoard = getUserInput( gameBoard, inputX );

            //check if there is a row
            winner = isWinner(gameBoard, inputX);

            switch (winner){
                case 1:
                    cout << "\nX wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 2:
                    cout << "\nO wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 3:
                    cout << "\nTie Game?! HOW!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                default:
                    break;
            }

            
            //computer makes change
            gameBoard = computerRandom( gameBoard, inputO );

            //check if there is a row
            winner = isWinner(gameBoard, inputO);

            switch (winner){
                case 1:
                    cout << "\nX wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 2:
                    cout << "\nO wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 3:
                    cout << "\nTie Game?! HOW!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                default:
                    break;
            }


        }


    }else if(easyOrHard == 'H'){

        cout << "\n\nHARD MODE\n\n";
        gameBoard[0][0] = 'O';

        while(gameFlag){

            //print board
            printBoard(gameBoard);

            //get user input and apply change
            gameBoard = getUserInput( gameBoard, inputX );

            //check if there is a row
            winner = isWinner(gameBoard, inputX);

            switch (winner){
                case 1:
                    cout << "\nX wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 2:
                    cout << "\nO wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 3:
                    cout << "\nTie Game?! HOW!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                default:
                    break;
            }

            
            //computer makes change
            gameBoard = computerRandom( gameBoard, inputO );

            //check if there is a row
            winner = isWinner(gameBoard, inputO);

            switch (winner){
                case 1:
                    cout << "\nX wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 2:
                    cout << "\nO wins!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                case 3:
                    cout << "\nTie Game?! HOW!";
                    printBoard(gameBoard);
                    cout << "Game over!";
                    gameFlag = false;
                    break;
                default:
                    break;
            }

        }
    }else{
        cout << "\nIncorrect input, bye!";
    }

    return(0);

}