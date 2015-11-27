#include "TextQuery.h"
#include<iostream>
#include<sstream>
using std::ifstream;
using std::cin;
using std::cout;
using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
using std::set;

TextQuery::TextQuery(ifstream& is) : file(new vector<string>)
{
    string text;
    while(getline(is,text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if(!lines)
            {
                lines.reset(new set<line_no>);
            }
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string& sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought,nodata,file);
    else
        return QueryResult(sought,loc->second,file);
}

void QueryResult::print(std::ostream &os) const
{
    os<<sought<< " occurs "<<lines->size() << "time s"<<std::endl;
    for(auto num : *lines)
        os<<" (line " << num + 1<< ") " << *(file->begin() + num) <<std::endl;
}
