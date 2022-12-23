//
// Created by abdel on 21/12/2022.
//
#include "bits/stdc++.h"
using namespace std;
#ifndef INC_6_MANAGER_H
#define INC_6_MANAGER_H
#define N 5
class board;
class Player{
public:
    char symbol;
    string name;
    Player(string name,char symbol){
        this->symbol = symbol;
        this->name=name;
    }
    virtual void getMove(int &move, board &state_board, Player *other_player)=0;
};
class board{
public:
    char arr[N][N];
    Player* player1;
    Player* player2;
    board(Player *player1, Player *player2);
    void display();
    bool make_move(int move, Player *currentPlayer);
    bool check_win(Player *player);
    bool isStuck(board currentBoard,Player *player);
};
class HumanPlayer: public Player{
public:
    HumanPlayer(string name, char symbol):Player(name,symbol){
    }
    void getMove(int &move, board &state_board, Player *other_player) override{
        cout << name <<", enter number of( 1, 2 , 3) : ";
        cin>>move;
        cout<<endl;
        while(!state_board.make_move(move, this)){
            cout << "invalid move enter again : ";
            cin >> move;
        }

    };
};
class computerPlayer:public Player{
public:
    computerPlayer(string name,char symbol):Player(name,symbol){};
    void getMove(int &move, board &state_board, Player *other_player) override;
    int getGoodMove(board &currentBoard,Player *currentPlayer,Player *otherPlayer);
    bool isGoodMove(board &currentBoard,Player *currentPlayer,Player *otherPlayer);
};
class Manager{
public:
    board* game;
    Player* player1;
    Player* player2;
    Manager(Player* player1, Player* player2);
    void play();
};
#endif //INC_6_MANAGER_H
