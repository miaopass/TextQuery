#ifndef QUERYBASE_H
#define QUERYBASE_H

#include "TextQuery.h"
#include<string>

class Query;

class QueryBase
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~QueryBase() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
private:
};


#endif // QUERYBASE_H
