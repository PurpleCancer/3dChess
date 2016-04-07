//
// Created by Jan on 24.03.2016.
//

#include "Game.h"

using namespace std;

void Game::Print()
{
    board->Print();
}

bool Game::Move()
{
    string move = reader->getNextMove();
    if(move.empty())
        //no more moves
        return false;
    else
    {
        board->Move(move);
        return true;
    }
}

void Game::printGameInfo()
{
    if(!event.empty())
        cout<<"Event: "<<event<<endl;
    if(!site.empty())
        cout<<"Site: "<<site<<endl;
    if(!date.empty())
        cout<<"Date: "<<date<<endl;
    if(!white.empty())
        cout<<"White: "<<white<<endl;
    if(!black.empty())
        cout<<"Black: "<<black<<endl;
    if(!result.empty())
        cout<<"Result: "<<result<<endl;

}

Game::Game(string name)
{
    board = new Board();
    reader = new Reader(name);

    event = reader->getEvent();
    site = reader->getSite();
    date = reader->getDate();
    result = reader->getResult();
    white = reader->getWhite();
    black = reader->getBlack();
}

Game::Game()
{

}

Game::~Game()
{
    delete board;
    delete reader;
}