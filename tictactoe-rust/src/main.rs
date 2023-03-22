use std::io;

fn main() {



    let mut board: [[char; 3]; 3] = [
        [' ', ' ', ' '],
        [' ', ' ', ' '],
        [' ', ' ', ' ']
    ];

    let player = 'X';
    let computer = 'O';


    loop {

        println!("WELCOME TO HARD MODE TIC TAC TOE");
        display_board(&board);
        let mut user_move = get_user_move(&board);  
        board[user_move.0 as usize][user_move.1 as usize] = 'X';
        display_board(&board);

    }


}

fn display_board(board: &[[char; 3]; 3]) {

    for row in board {
        println!("{:?}", row);
    }

}

fn get_user_move(board: &[[char; 3]; 3]) -> (i32, i32){
    let mut row: i32;
    let mut col: i32;

    loop {
        println!("Enter row number (1-3) of your move: ");
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read input");
        row = input.trim().parse().expect("Invalid input");

        println!("Enter column number (1-3) of your move: ");
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read input");
        col = input.trim().parse().expect("Invalid input");

        row -= 1;
        col -= 1;

        if row < 0 || row > 2 || col < 0 || col > 2 {
            println!("Invalid input. Please enter numbers between 1 and 3.");
        } else if board[row as usize][col as usize] != ' ' {
            println!("That space is already taken. Please choose another one.");
        } else {
            break;
        }
    }

    return (row, col);
}

fn is_winner(board: &[[char; 3]; 3], player: char) -> bool {

    //row
    for row in 0..3{
        if  board[row][0] == player && board[row][1] == player && board[row][2] == player {
            return true;
        }
    }

    //col
    for col in 0..3{
        if  board[0][col] == player && board[1][col] == player && board[2][col] == player {
            return true;
        }
    }

    if board[0][0] == player && board[1][1] == player && board[2][2] == player {
        return true
    }

    if board[0][2] == player && board[1][1] == player && board[2][0] == player {
        return true;
    }

    return false;
}

fn is_tie(board: &[[char; 3]; 3]) -> bool{

    for i in 0..3{
        for j in 0..3{
            if board[i][j] == ' '{
                return false
            }
        }
    }

    return true;
}