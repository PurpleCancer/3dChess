//
// Created by Jan on 24.03.2016.
//

#include "Game.h"

using namespace std;

void Game::Print()
{
    board->Print();
}

Pole Game::Move()
{
    Pole p;
    string move = reader->getNextMove();
    if(move.empty()) {
        //no more moves
        p.Row = -1;
        p.Column = 1;
    }
    else
    {
        p = board->Move(move);
    }
    return p;
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

Tile** Game::getBoardSnapshot() {
    return this->board->getBoardSnapshot();
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