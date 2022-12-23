//
// Created by abdel on 21/12/2022.
//
#include "manager.h"

board::board(Player *player1, Player *player2) {
    this->player1=player1;
    this->player2=player2;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            arr[i][j]='-';
        }
    }
    for(int i=1;i<=N-2;i++){
        arr[0][i]=player1->symbol;
        arr[i][0]=player2->symbol;
    }

}

void board::display() {
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<arr[i][j];
        }
        cout<<endl;
    }

}



bool board::make_move(int move, Player *currentPlayer) {
    if(move<1||move>N-2){
        return false;
    }
    if(currentPlayer->symbol==player1->symbol){
        int column=move,row;
        for(int i=0;i<N;i++) {
            if (arr[i][column] == currentPlayer->symbol) {
                row = i;
                break;
            }
        }
        if(row==N-1){
            return false;
        }
        if((row!=N-2)&&(arr[row+1][column]==player2->symbol&&arr[row+2][column]==player2->symbol)){
            return false;
        }
        if(arr[row+1][column]=='-'){
            arr[row][column]='-';
            arr[row+1][column]=currentPlayer->symbol;

        } else{
            arr[row][column]='-';
            arr[row+2][column]=currentPlayer->symbol;
        }
        return true;
    }
    else {
        int column,row=move;
        for(int i=0;i<N;i++) {
            if (arr[row][i] == currentPlayer->symbol) {
                column = i;
                break;
            }
        }
        if(column==N-1){
            return false;
        }
        if((column!=N-2)&&(arr[row][column+1]==player1->symbol&&arr[row][column+2]==player1->symbol)){
            return false;
        }
        if(arr[row][column+1]=='-'){
            arr[row][column+1]=currentPlayer->symbol;
            arr[row][column]='-';
        } else{
            arr[row][column+2]=currentPlayer->symbol;
            arr[row][column]='-';
        }
        return true;
    }
}

bool board::check_win(Player *player) {
    int count=0;
    for(int i=1;i<=N-2;i++){
        if(arr[i][N-1]==player->symbol){
            count++;

        }

        if(arr[N-1][i]==player->symbol){
            count++;
        }
    }
    if(count==N-2){
        return true;
    }
    return false;
}

bool board::isStuck(board currentBoard,Player *player) {
    for(int i=1;i<=N-2;i++){
        if(currentBoard.make_move(i,player)){
            return false;
        }
    }
    return true;
}

Manager::Manager(Player *player1, Player *player2) {
    this->player1=player1;
    this->player2=player2;
    game=new board(player1,player2);


}

void Manager::play() {
    Player* player[]={player1,player2};
    int turn=0;
    while(true){
        game->display();
        cout << player[turn]->name << "'s turn" << endl;
        int move;
        if(game->isStuck(*game,player[turn])){
            cout<<"Player "<<turn-1<<" cant play";
            turn=turn-1;
        }
        player[turn]->getMove( move, *game, player[1 - turn]);
        if (game->check_win(player[turn])) {
            game->display();
            cout << player[turn]->name << " won" << endl;
            break;
        }
        if (turn == 0) {
            turn = 1;
        } else {
            turn = 0;
        }

    }
}

void computerPlayer::getMove(int &move, board &state_board, Player *otherPlayer) {
move= getGoodMove(state_board,this,otherPlayer);
if(move==0){
    move=(rand() % (N-2)) + 1;
    while (!state_board.make_move(move, this)){
        move=(rand() % (N-2)) + 1;
    }
}
    cout << name <<" choose "<< move<<endl;
}

int computerPlayer::getGoodMove(board &currentBoard,Player* currentPlayer, Player *otherPlayer) {
    for(int i=1;i<=N-2;i++){
        board temp=currentBoard;
        if(currentBoard.make_move(i, currentPlayer)) {
            if (isGoodMove(currentBoard, currentPlayer, otherPlayer)) {
                return i;
            }
        }
        currentBoard=temp;
    }
    return 0;

}

bool computerPlayer::isGoodMove(board &currentBoard,Player*currentPlayer ,Player *otherPlayer) {
    if(currentBoard.check_win(currentPlayer)){
        return true;
    }
    if(currentBoard.check_win(otherPlayer)){
        return false;
    }
    if(getGoodMove(currentBoard,otherPlayer,currentPlayer)==0){
        return true;
    }else{
        return false;
    }
}
