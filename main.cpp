#include "bits/stdc++.h"
#include "manager.h"
using namespace std;
int main() {
    srand(time(0));
    int answer;
    cout<<"choose the kind of game  (1)human vs human (2)human vs computer: ";
    cin>>answer;

    if(answer==1){
        string name1,name2;
        cout<<"enter name of player 1: ";
        cin>>name1;

        cout<<"enter name of player 2: ";
        cin>>name2;

        Player* player1=new HumanPlayer(name1,'v');
        Player* player2=new HumanPlayer(name2,'>');
        Manager* manager=new Manager(player1,player2);
        manager->play();
    }
    else{
        string name1;
        cout<<"enter name of player 1: ";
        cin>>name1;
        Player* player1=new HumanPlayer(name1,'v');
        Player* player2=new computerPlayer("computer",'>');
        Manager* manager=new Manager(player1,player2);
        manager->play();
    }
    return 0;

}
