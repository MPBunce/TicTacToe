#include <iostream>
#include <vector>
#include <cctype>
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
    


    return theMatrix;

}

bool isWinner( vector<vector<char>> theMatrix ){

    return false;
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
    char inputX = 'X';
    char inputO = 'O';

    cout << "Welcome to tic tac toe!\n";
    cout << "Easy mode or hard mode (E or H)?: \n";
    cin >> easyOrHard;

    easyOrHard = toupper(easyOrHard);

    cout<< "\n" << easyOrHard << "\n";

    if(easyOrHard == 'E'){
        while(gameFlag){

            //print board
            printBoard(gameBoard);

            //get user input and apply change
            gameBoard = getUserInput( gameBoard, inputX );

            //computer makes change
            gameBoard = computerRandom( gameBoard, inputO );

            //check if there is a row
            gameFlag = isWinner(gameBoard);

        }
    }else if(easyOrHard == 'H'){
        while(gameFlag){

            printBoard(gameBoard);






            gameFlag = false;

        }
    }else{
        cout << "\nIncorrect input, bye!";
    }
    
    return(0);

}