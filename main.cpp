#include <iostream>
#include "Game.h"

using namespace std;

Game* game;

int main()
{
    game = new Game("<pgn file>");
    //game->Print();
    game->printGameInfo();
    cout<<endl;

    while(!game->Move());


//    game->Move("e4");
//    game->Move("Kf3");
//    game->Move("Nge7");
//    game->Move("Nf6+");
//    game->Move("Q6xd7+");
//    game->Move("bxc8=Q#");
//    game->Move("Bb5xc6");
//    game->Move("O-O");
//    game->Move("O-O-O");

    delete game;

    return 0;
}