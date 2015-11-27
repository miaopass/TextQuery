#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<fstream>

class QueryResult
{
public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,std::shared_ptr<std::set<line_no>> p,std::shared_ptr<std::vector<std::string>> f)
                : sought(s),lines(p),file(f) { }
    void print(std::ostream&) const;
    std::set<line_no>::iterator begin() { return lines->begin(); }
    std::set<line_no>::iterator end() { return lines->end(); }
    const std::shared_ptr<std::vector<std::string>> get_file() const { return file ;}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

class TextQuery
{
    public:
        using line_no =std::vector<std::string>::size_type;
        TextQuery(std::ifstream&);
        QueryResult query(const std::string &sought) const;
    private:
        std::shared_ptr<std::vector<std::string>> file;
        std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
};

#endif // TEXTQUERY_H
