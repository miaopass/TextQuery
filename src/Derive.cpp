#include "Derive.h"
#include<memory>
#include<set>
#include<algorithm>
#include<iterator>
using std::make_shared;
using std::set;

QueryResult NotQuery::eval(const TextQuery& text) const
{
    QueryResult result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>> ();
    auto beg = result.begin(),end = result.end();
    auto sz = result.get_file()->size();
    for(size_t n = 0;n != sz;++n)
    {
        if(beg == end || *beg != n)
            ret_lines->insert(n);
        else if(beg != end)
            ++beg;
    }
    return QueryResult(rep(),ret_lines,result.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const
{
    auto left = lhs.eval(text),right = rhs.eval(text);
    auto ret_lines = std::make_shared<set<line_no>> ();
    set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));
    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult OrQuery::eval(const TextQuery& text) const
{
    auto left = lhs.eval(text),right = rhs.eval(text);
    auto ret_lines = std::make_shared<set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(),right.end());
    return QueryResult(rep(),ret_lines,left.get_file());
}
