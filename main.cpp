#include <iostream>
#include "Game.h"

using namespace std;

Game* game;

int main()
{
    game = new Game("C:\\Users\\Jan\\Desktop\\semestr4\\grafika\\anderssen_dufresne_1852.pgn");
    game->Print();
    //game->printGameInfo();
    cout<<endl;

    //while(!game->Move());

    game->Move();
    game->Print();

    game->Move();
    game->Print();

    game->Move();
    game->Print();

    game->Move();
    game->Print();


    delete game;

    return 0;
}