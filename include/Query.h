#ifndef QUERY_H
#define QUERY_H

#include "QueryBase.h"
#include<memory>
#include<string>

Query operator~ (const Query&);
Query operator& (const Query&,const Query&);
Query operator| (const Query&,const Query&);

class Query
{
    friend Query operator~ (const Query&);
    friend Query operator& (const Query&,const Query&);
    friend Query operator| (const Query&,const Query&);
public:
    Query(std::string sought);
    virtual ~Query() = default;
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    std::string rep() const { return q-> rep(); }
private:
    Query(std::shared_ptr<QueryBase> query) : q(query) { }
    std::shared_ptr<QueryBase> q;
};


#endif // QUERY_H
