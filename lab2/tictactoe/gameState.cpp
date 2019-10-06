//
//  gameState.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.



#include "tictactoe.h"
#include "gameState.h"

using namespace std;

//Accessor for clickedRow variable
int gameState::get_clickedRow(){
    return (clickedRow);
}

//Accessor for clicked column
int gameState::get_clickedColumn(){
    return (clickedColumn);
}

//set clickedRow to value iff value is in board bounds
void gameState::set_clickedRow(int value){
    if(value > boardSize-1 || value < 0){
        return;
    }
    clickedRow = value;
    return;
}

//set clickedColumn to value iff value is in board bounds
void gameState::set_clickedColumn(int value){
    if(value > boardSize-1 || value < 0){
        return;
    }
    clickedColumn = value;
   return;
}

//accessor for moveValid
bool gameState::get_moveValid(){
    return moveValid;
}

//mutator for moveValid
void gameState::set_moveValid(bool value){
    moveValid=value;
    return;
}

//accessor for gameOver
bool gameState::get_gameOver(){
    return gameOver;
}

//mutator of gameOver
void gameState::set_gameOver(bool value){
    gameOver=value;
    return;
}

//accessor of winCode
int gameState::get_winCode(){
    return winCode;
}

//winCode mutator, set to value iff value is within valid winCodes 0-8
void gameState::set_winCode(int value){
    if(value <= 8 && value >=0){
        winCode=value;
    }
    return;
}

//accessor of get_turn
bool gameState::get_turn(){
    return turn;
}

//mutator of getTurn
void gameState::set_turn(bool value){
    turn = value;
    return;
}

//gameBoard entry accessor
int gameState::get_gameBoard(int row, int col){
    return gameBoard[row][col];
}

//gameBoard mutator, conditions: iff col & row are 0 <= x <= (boardSize-1) 
//& value is X, O or Empty
void gameState::set_gameBoard(int row, int col, int value){
    if(col <= boardSize-1 && col >= 0){
        if(row <= boardSize-1 && row >= 0){
            if(value == Empty || value == X || value == O){
                gameBoard[row][col] = value;
            }
        }
    }
    return;
}


