use std::io;

fn main() {



    let mut board: [[char; 3]; 3] = [
        [' ', ' ', ' '],
        [' ', ' ', ' '],
        [' ', ' ', ' ']
    ];

    let player = 'X';
    let computer = 'O';
    let mut turn: bool = false;

    loop {
        // Print current board
        display_board(&board);
        
        // Check if game is over
        if is_winner(&board, 'X') {
            println!("Congrats player, you win!\n");
            break;
        } else if is_winner(&board, 'O') {
            println!("Congrats computer, you win!\n");
            break;
        } else if is_tie(&board) {
            println!("Darn a tie!\n");
            break;
        }
        
        // Player turn
        if turn {

            // Get player move
            let user_move = get_user_move(&board);  

            // Update board
            board[user_move.0 as usize][user_move.1 as usize] = player;
            
            // Switch to computer turn
            turn = false;

        } else {

            // Get player move
            let computer_move = get_computer_move(&board);  

            // Update board
            board[computer_move.0 as usize][computer_move.1 as usize] = computer;
            
            // Switch to computer turn
            turn = true;

        }

        println!("\n");

    }

    // Game over
    display_board(&board);

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

fn get_computer_move( board: &[[char; 3]; 3] ) -> (i32, i32){
    let mut row: i32 = -1;
    let mut col: i32 = -1;

    let mut best_score: i32 = -1000;
    let mut score: i32;

    let mut temp_board: [[char; 3]; 3] = board.clone();



    for i in 0..3{
        for j in 0..3{
            if board[i][j] == ' '{

                //Make a move if cell is empty
                temp_board[i][j] = 'O';
                score = min_max(&temp_board, 0, false, 'O' );
                
                if score > best_score {
                    row = i as i32;
                    col = j as i32;
                    best_score = score;
                }

            }
        }
    }



    return (row, col);
}

fn min_max(board: &[[char; 3]; 3], depth: i32, is_maxing: bool, symbol: char ) -> i32 {


    let mut best_score: i32 = -1000;
    let mut score: i32 = 0;
    let mut temp_board: [[char; 3]; 3] = board.clone();

    if is_winner(board, 'O') {
        return 10 - depth;
    } else if is_winner(board, 'X'){
        return depth - 10;
    } else if is_tie(board){
        return 0;
    }


    if is_maxing {

        for i in 0..3{
            for j in 0..3{
                if board[i][j] == ' '{

                    temp_board[i][j] = symbol;
                    score = min_max(&temp_board, depth + 1, false, 'X' );
                    best_score = std::cmp::max(score, best_score);

                }
            }
        }

        return best_score;

    } else {
        best_score = 1000;

        for i in 0..3{
            for j in 0..3{
                if board[i][j] == ' '{

                    temp_board[i][j] = symbol;
                    min_max(&temp_board, depth +1 , true, 'O' );
                    best_score = std::cmp::min(score, best_score);
    
                }
            }
        }

        return best_score;

    }

}
