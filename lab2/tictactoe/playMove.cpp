//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h"
#include "gameState.h"

using namespace std;

using namespace std;


void playMove(gameState& game_state) {
    //accessing clickedRow and clickedColumn and putting into shorter Variable names
    int clckR = game_state.get_clickedRow();
    int clckC = game_state.get_clickedColumn();
    
    //we can only continue to edit board if move is valid (space empty, game not over)
    if(game_state.get_gameBoard(clckR,clckC) == Empty && game_state.get_winCode() == 0 
                        && game_state.get_gameOver() == false){
        game_state.set_moveValid(true);
    }else{
        game_state.set_moveValid(false);
    }
    
    //if move is valid, we can begin to work on our board
    if(game_state.get_moveValid() == true){
        
        //lets figure out who's turn it is, then store that in player, we'll change 
        //the turn variable at the end
        int player = 0;
        switch(game_state.get_turn()){ //this will typecase the bool to a int, not a problem
            case true : player = X; 
                        break;
            case false : player = O;
                        break;
        }
        
        //now we are going to change the gameBoard to the player value
        game_state.set_gameBoard(clckR, clckC, player);
        
        //player has taken their turn, now switch turns
        switch(game_state.get_turn()){ //this will typecase the bool to a int, not a problem
            case true : game_state.set_turn(false); //if its x, switch to o
                        break;
            case false : game_state.set_turn(true); //if its o, switch to x
                        break;
        }
        
        
    }
    
    //now that our player has gone, we should check for a winner
    //first we check if winner has already been found, to save some time
    if(game_state.get_gameOver() == false){
        //now we're going to check the win codes one by one, there's a more efficient way of doing this but anyway...
        //have to make sure that the entries dont == each other just because theyre empty, hence != Empty at each win statement
        if(game_state.get_gameBoard(0,0) != Empty && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(0,1) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(0,2)){ 
            //row 0
            game_state.set_winCode(1);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(1,0) != Empty && game_state.get_gameBoard(1,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(1,0) == game_state.get_gameBoard(1,2)){ 
            //row 1
            game_state.set_winCode(2);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(2,0) != Empty && game_state.get_gameBoard(2,0) == game_state.get_gameBoard(2,1) && game_state.get_gameBoard(2,0) == game_state.get_gameBoard(2,2)){
            //row 2
            game_state.set_winCode(3);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(0,0) != Empty && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,0) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(2,0)){ 
            //col 0
            game_state.set_winCode(4);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(0,1) != Empty && game_state.get_gameBoard(0,1) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,1) == game_state.get_gameBoard(2,1)){ 
            //col 1
            game_state.set_winCode(5);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(0,2) != Empty && game_state.get_gameBoard(0,2) == game_state.get_gameBoard(1,2) && game_state.get_gameBoard(0,2) == game_state.get_gameBoard(2,2)){ 
            //col 2
            game_state.set_winCode(6);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(1,1) != Empty && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(2,2)){ 
            //left to right diag
            game_state.set_winCode(7);
            game_state.set_gameOver(true);
        }else if(game_state.get_gameBoard(2,0) != Empty && game_state.get_gameBoard(2,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(2,0) == game_state.get_gameBoard(0,2)){ 
            //right to left diag
            game_state.set_winCode(8);
            game_state.set_gameOver(true);
        }
    }
    
    if(game_state.get_gameOver() == false){
        //if no win code runs, lets check if theres been a draw, (the board is full)
        //well assume theres a draw (gameover true) unless we find an empty spot
        game_state.set_gameOver(true);
        //cycle through sports on the board
        for (int i=0 ; i < 3 ; i++){
            for (int j=0 ; j< 3 ; j++){
                if (game_state.get_gameBoard(i, j) == Empty){
                    game_state.set_gameOver(false);
                }
            }
        }
    }
    

}


