//
// Created by Jan on 31.03.2016.
//

#include "Reader.h"

using namespace std;

string Reader::getEvent()
{
    return event;
}

string Reader::getSite()
{
    return site;
}

string Reader::getDate()
{
    return date;
}

string Reader::getResult()
{
    return result;
}

string Reader::getWhite()
{
    return white;
}

string Reader::getBlack()
{
    return black;
}

string Reader::getNextMove()
{
    if(moves.empty())
        return "";
    else
    {
        string ret = moves.front();
        moves.pop();
        return ret;
    }
}

Reader::Reader(string name)
{

    string s;
    string allmoves = "";
    match_results<string::const_iterator> tags;

    tags_pattern = new regex("\\[(\\w+) \"([\\s\\S]*)\"\\]");
    moves_pattern = new regex("((?:[KQRNB]?[a-h]?[1-8]?x?[a-h][1-8](?:=[QRNB])?[+#]?)|(?:O-O)|(?:O-O-O))(?![^{]*})");

    ifstream file;

    try
    {
        file.open(name,ios::in);
    }
    catch (ifstream::failure e) {
        cerr << "Exception opening/reading/closing file\n";
    }


    if(!file){
        cout<<"NIE"<<endl;
    }




    while(getline(file, s))
    {

        if(regex_match(s, tags, *tags_pattern))
        {
            if(tags[1].str() == "Event")
                event = tags[2].str();
            else if(tags[1].str() == "Site")
                site = tags[2].str();
            else if(tags[1].str() == "Date")
                date = tags[2].str();
            else if(tags[1].str() == "tags")
                this->result = tags[2].str();
            else if(tags[1].str() == "White")
                white = tags[2].str();
            else if(tags[1].str() == "Black")
                black = tags[2].str();
        }
        else
        {
            allmoves += s;
            allmoves += " ";
        }
    }



    sregex_iterator next(allmoves.begin(), allmoves.end(), *moves_pattern);
    sregex_iterator end;

    while(next != end)
    {
        smatch match = *next;
        moves.push(match.str());
        next++;
    }
}

Reader::~Reader()
{
    file.close();
    delete tags_pattern;
    delete moves_pattern;
    while(!moves.empty())
        moves.pop();
}

Reader::Reader()
{

}





