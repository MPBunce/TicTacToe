#include <iostream>
using namespace std;

//Functions
void printBoard( char board[100][100] ){

    int x = 3;
    
    for(int i; i < x; ++i){
        cout << board[i];
    }

}
//Main

int main(){

    char gameBoard[3][3] = {
        {'1', '2', '3',},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    printf("\nhello\n\n");

    printBoard( gameBoard );

    return(0);


}

