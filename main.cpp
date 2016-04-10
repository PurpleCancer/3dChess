#include <iostream>
#include "Game.h"

using namespace std;

Game* game;

int main()
{
    game = new Game("C:\\Users\\Jan\\Desktop\\semestr4\\grafika\\fischer_petrosian_1959.pgn");
    game->Print();
    //game->printGameInfo();
    cout<<endl;

    while(game->Move());

    /*int i = 1;
    while(true)
    {
        cout<<i++<<". ";
        if(!game->Move())break;
        game->Print();
        if(!game->Move())break;
        game->Print();
    }*/

    game->Print();

    delete game;

    return 0;
}