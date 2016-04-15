//
// Created by Jan on 24.03.2016.
//

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

void Player::FindPieceToMove(PieceType type, int startColumn, int startRow, int targetColumn, int targetRow,
                              Tile **boardSnapshot)
{
    bool CorrectPiece = false;
    for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
    {
        if(type == it->getType()
           && ((startColumn == 0 && startRow == 0)
               || (startColumn == it->getColumn() && startRow == 0)
               || (startColumn == 0 && startRow == it->getRow())
               || (startColumn == it->getColumn() && startRow == it->getRow())))
            switch (type)
            {
                case Pawn:
                    CorrectPiece = (startColumn == 0 && CanPawnMove(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot))
                       || (startColumn == it->getColumn() && CanPawnTake(it->getRow(), targetRow));
                    break;
                case Knight:
                    CorrectPiece = CanKnightMove(it->getColumn(), it->getRow(), targetColumn, targetRow);
                    break;
                case Bishop:
                    CorrectPiece = CanMoveDiagonally(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot);
                    break;
                case Rook:
                    CorrectPiece = (CanMoveHorizontally(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot)
                        || CanMoveVertically(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot));
                    break;
                case Queen:
                    CorrectPiece = (CanMoveHorizontally(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot)
                        || CanMoveVertically(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot)
                        || CanMoveDiagonally(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot));
                    break;
                case King:
                    CorrectPiece = true;
                    break;
                default:
                    break;
            }
        if(CorrectPiece)
        {
            it->setColumn(targetColumn);
            it->setRow(targetRow);
            break;
        }
    }
}

void Player::FindPieceToTake(int targetColumn, int targetRow)
{
    bool enPassant = true;

    for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
    {
        if(it->getColumn() == targetColumn && it->getRow() == targetRow)
        {
            enPassant = false;
            myPieces.erase(it);
            break;
        }
    }

    if(enPassant)
    {
        for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
        {
            if(it->getColumn() == targetColumn && (it->getRow() == targetRow + 1 || it->getRow() == targetRow - 1))
            {
                myPieces.erase(it);
                break;
            }
        }
    }
}

void Player::KingsideCastling()
{
    for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
    {
        if(it->getType() == King)
            it->setColumn(7);
        if(it->getType() == Rook && it->getColumn() == 8 && ((colour == White && it->getRow() == 1) || (colour == Black && it->getRow() == 8)))
            it->setColumn(6);
    }
}

void Player::QueensideCastling()
{
    for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
    {
        if(it->getType() == King)
            it->setColumn(3);
        if(it->getType() == Rook && it->getColumn() == 1 && ((colour == White && it->getRow() == 1) || (colour == Black && it->getRow() == 8)))
            it->setColumn(4);
    }
}

void Player::MovePawnAndPromote(PieceType type, int startColumn, int startRow, int targetColumn, int targetRow,
                                Tile** boardSnapshot, PieceType promotion)
{
    bool CorrectPiece = false;
    for(vector<Piece>::iterator it = myPieces.begin(); it != myPieces.end(); ++it)
    {
        if(type == it->getType()
           && ((startColumn == 0 && startRow == 0)
               || (startColumn == it->getColumn() && startRow == 0)
               || (startColumn == 0 && startRow == it->getRow())
               || (startColumn == it->getColumn() && startRow == it->getRow())))
            {
                CorrectPiece = (startColumn == 0 && CanPawnMove(it->getColumn(), it->getRow(), targetColumn, targetRow, boardSnapshot))
                               || (startColumn == it->getColumn() && CanPawnTake(it->getRow(), targetRow));
            }
        if(CorrectPiece)
        {
            it->setColumn(targetColumn);
            it->setRow(targetRow);
            it->setType(promotion);
            break;
        }
    }
}

bool Player::CanMoveDiagonally(int startColumn, int startRow, int targetColumn, int targetRow, Tile **boardSnapshot)
{
    int horizontalDifference = AbsoluteInt(targetColumn - startColumn);
    int verticalDifference = AbsoluteInt(targetRow - startRow);

    if(horizontalDifference != verticalDifference)
        return false;

    int Difference = horizontalDifference;

    int currentColumn = startColumn + (targetColumn - startColumn) / Difference;
    int currentRow = startRow + (targetRow - startRow) / Difference;
    Difference--;

    while(currentColumn != targetColumn /*&& currentRow !=targetRow*/)
    {
        if(boardSnapshot[currentRow - 1][currentColumn - 1].type != None)
            return false;
        currentColumn += (targetColumn - currentColumn) / Difference;
        currentRow += (targetRow - currentRow) / Difference;
        Difference--;
    }

    return true;
}

bool Player::CanMoveHorizontally(int startColumn, int startRow, int targetColumn, int targetRow, Tile **boardSnapshot)
{
    if(startRow != targetRow)
        return false;

    int Difference = AbsoluteInt(targetColumn - startColumn);
    int currentColumn = startColumn + (targetColumn - startColumn) / Difference;
    Difference--;

    while(currentColumn != targetColumn)
    {
        if(boardSnapshot[startRow - 1][currentColumn - 1].type != None)
            return false;
        currentColumn += (targetColumn - currentColumn) / Difference;
        Difference--;
    }

    return true;
}

bool Player::CanMoveVertically(int startColumn, int startRow, int targetColumn, int targetRow, Tile **boardSnapshot)
{
    if(startColumn != targetColumn)
        return false;

    int Difference = AbsoluteInt(targetRow - startRow);
    int currentRow = startRow + (targetRow - startRow) / Difference;
    Difference--;

    while(currentRow != targetRow)
    {
        if(boardSnapshot[currentRow - 1][startColumn - 1].type != None)
            return false;
        currentRow += (targetRow - currentRow) / Difference;
        Difference--;
    }

    return true;
}

bool Player::CanKnightMove(int startColumn, int startRow, int targetColumn, int targetRow)
{
    int horizontalDifference = AbsoluteInt(targetColumn - startColumn);
    int verticalDifference = AbsoluteInt(targetRow - startRow);
    return (horizontalDifference == 1 && verticalDifference == 2) || (horizontalDifference == 2 && verticalDifference == 1);
}

bool Player::CanPawnMove(int startColumn, int startRow, int targetColumn, int targetRow, Tile **boardSnapshot)
{
    int forward = (colour == White) ? 1 : -1;     //'forward' for a player

    return (targetColumn == startColumn && targetRow == startRow + forward)
       || (targetColumn == startColumn && targetRow == startRow + 2*forward && boardSnapshot[startRow + forward - 1][startColumn - 1].type == None);
}

bool Player::CanPawnTake(int startRow, int targetRow)
{
    int forward = (colour == White) ? 1 : -1;     //'forward' for a player
    return targetRow == startRow + forward;
}

Player::Player(Colour colour)
{
    this->colour = colour;
    int firstRow = 0;
    int secondRow = 0;

    switch(this->colour)
    {
        case White:
            firstRow = 1;
            secondRow = 2;
            break;
        case Black:
            firstRow = 8;
            secondRow = 7;
            break;
        default:
            cout<<"Gracz nie ma koloru"<<endl;
            break;
    }
    //inserting the pieces
    //pawns
    Piece p1(Pawn, 1, secondRow);
    myPieces.push_back(p1);
    Piece p2(Pawn, 2, secondRow);
    myPieces.push_back(p2);
    Piece p3(Pawn, 3, secondRow);
    myPieces.push_back(p3);
    Piece p4(Pawn, 4, secondRow);
    myPieces.push_back(p4);
    Piece p5(Pawn, 5, secondRow);
    myPieces.push_back(p5);
    Piece p6(Pawn, 6, secondRow);
    myPieces.push_back(p6);
    Piece p7(Pawn, 7, secondRow);
    myPieces.push_back(p7);
    Piece p8(Pawn, 8, secondRow);
    myPieces.push_back(p8);
    //rooks
    Piece r1(Rook, 1, firstRow);
    myPieces.push_back(r1);
    Piece r2(Rook, 8, firstRow);
    myPieces.push_back(r2);
    //knights
    Piece n1(Knight, 2, firstRow);
    myPieces.push_back(n1);
    Piece n2(Knight, 7, firstRow);
    myPieces.push_back(n2);
    //bishops
    Piece b1(Bishop, 3, firstRow);
    myPieces.push_back(b1);
    Piece b2(Bishop, 6, firstRow);
    myPieces.push_back(b2);
    //queen
    Piece q(Queen, 4, firstRow);
    myPieces.push_back(q);
    //king
    Piece k(King, 5, firstRow);
    myPieces.push_back(k);
}

int Player::AbsoluteInt(int x)
{
    return x >= 0 ? x : -x;
}

Player::Player()
{

}

Player::~Player()
{
    myPieces.clear();
}



