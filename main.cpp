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

    for(int i = 0; i < 12; ++i)
    {
        game->Move();
        game->Print();
    }


    delete game;

    return 0;
}