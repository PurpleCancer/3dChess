#include <iostream>
#include "Game.h"

using namespace std;

Game* game;

int main()
{
    game = new Game("C:\\Users\\Jan\\Desktop\\semestr4\\grafika\\capablanca_p_northrop_1909.pgn");
    game->Print();
    //game->printGameInfo();
    cout<<endl;

    while(game->Move());

    /*for(int i = 0; i < 14; ++i)
    {
        game->Move();
        game->Print();
    }*/

    game->Print();

    delete game;

    return 0;
}