//
// Created by Jan on 24.03.2016.
//

#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

void Player::PleaseCompleteTheSnapshot(Tile **snap)
{
    for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
    {
        snap[it->getRow()-1][it->getColumn()-1].type = it->getType();
        snap[it->getRow()-1][it->getColumn()-1].colour = this->colour;
    }
}

Player::Player(Colour colour)
{
    this->colour = colour;

    switch(this->colour)
    {
        case White: {
            //pawns
            Piece p1(Pawn, 1, 2);
            myPieces.push_back(p1);
            Piece p2(Pawn, 2, 2);
            myPieces.push_back(p2);
            Piece p3(Pawn, 3, 2);
            myPieces.push_back(p3);
            Piece p4(Pawn, 4, 2);
            myPieces.push_back(p4);
            Piece p5(Pawn, 5, 2);
            myPieces.push_back(p5);
            Piece p6(Pawn, 6, 2);
            myPieces.push_back(p6);
            Piece p7(Pawn, 7, 2);
            myPieces.push_back(p7);
            Piece p8(Pawn, 8, 2);
            myPieces.push_back(p8);
            //rooks
            Piece r1(Rook, 1, 1);
            myPieces.push_back(r1);
            Piece r2(Rook, 8, 1);
            myPieces.push_back(r2);
            //knights
            Piece n1(Knight, 2, 1);
            myPieces.push_back(n1);
            Piece n2(Knight, 7, 1);
            myPieces.push_back(n2);
            //bishops
            Piece b1(Bishop, 3, 1);
            myPieces.push_back(b1);
            Piece b2(Bishop, 6, 1);
            myPieces.push_back(b2);
            //queen
            Piece q(Queen, 4, 1);
            myPieces.push_back(q);
            //king
            Piece k(King, 5, 1);
            myPieces.push_back(k);
            break;
        }

        case Black: {
            //pawns
            Piece p1(Pawn, 1, 7);
            myPieces.push_back(p1);
            Piece p2(Pawn, 2, 7);
            myPieces.push_back(p2);
            Piece p3(Pawn, 3, 7);
            myPieces.push_back(p3);
            Piece p4(Pawn, 4, 7);
            myPieces.push_back(p4);
            Piece p5(Pawn, 5, 7);
            myPieces.push_back(p5);
            Piece p6(Pawn, 6, 7);
            myPieces.push_back(p6);
            Piece p7(Pawn, 7, 7);
            myPieces.push_back(p7);
            Piece p8(Pawn, 8, 7);
            myPieces.push_back(p8);
            //rooks
            Piece r1(Rook, 1, 8);
            myPieces.push_back(r1);
            Piece r2(Rook, 8, 8);
            myPieces.push_back(r2);
            //knights
            Piece n1(Knight, 2, 8);
            myPieces.push_back(n1);
            Piece n2(Knight, 7, 8);
            myPieces.push_back(n2);
            //bishops
            Piece b1(Bishop, 3, 8);
            myPieces.push_back(b1);
            Piece b2(Bishop, 6, 8);
            myPieces.push_back(b2);
            //queen
            Piece q(Queen, 4, 8);
            myPieces.push_back(q);
            //king
            Piece k(King, 5, 8);
            myPieces.push_back(k);
            break;
        }
        default:
            cout<<"Gracz nie ma koloru"<<endl;
    }
}