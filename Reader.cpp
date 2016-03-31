//
// Created by Jan on 31.03.2016.
//

#include "Reader.h"

Reader::Reader(string name)
{
    file.open(name);
}

Reader::~Reader()
{
    file.close();
}

Reader::Reader()
{

}





