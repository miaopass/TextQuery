#ifndef DERIVE_H
#define DERIVE_H
#include "QueryBase.h"
#include "Query.h"
#include<string>

class Query;
Query operator~ (const Query&);
Query operator& (const Query&,const Query&);
Query operator| (const Query&,const Query&);

class BinaryQuery : public QueryBase
{
public:
protected:
    BinaryQuery(const Query& l,const Query& r,std::string op) : lhs(l),rhs(r),opSym(op) { }
    std::string rep() const
    {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }
    Query lhs,rhs;
    std::string opSym;
};

class WordQuery : public QueryBase
{
    friend class Query;
public:
    WordQuery(std::string s) : sought(s) {}
private:
    std::string sought;
    virtual QueryResult eval(const TextQuery& t) const override { return t.query(sought); }
    virtual std::string rep() const override { return sought; }

};

class NotQuery : public QueryBase
{
private:
    friend Query operator~ (const Query&);
    NotQuery(const Query& q) : query(q) { }
    virtual QueryResult eval(const TextQuery&) const override;
    virtual std::string rep() const override { return "~(" + query.rep(); };
    Query query;
};

class AndQuery : public BinaryQuery
{
private:
    friend Query operator& (const Query&,const Query&);
    AndQuery(const Query& lhs,const Query& rhs) : BinaryQuery(lhs,rhs,"&") { }
    virtual QueryResult eval(const TextQuery&) const override;
};

class OrQuery : public BinaryQuery
{
private:
    friend Query operator| (const Query&,const Query&);
    OrQuery(const Query& lhs,const Query& rhs) : BinaryQuery(lhs,rhs,"|") { }
    virtual QueryResult eval(const TextQuery&) const override;
};

inline
Query operator~ (const Query& s)
{
    return std::shared_ptr<QueryBase> (new NotQuery(s));
}

inline
Query operator& (const Query& lhs,const Query& rhs)
{
    return std::shared_ptr<QueryBase> (new AndQuery(lhs,rhs));
}

inline
Query operator| (const Query& lhs,const Query& rhs)
{
    return std::shared_ptr<QueryBase> (new OrQuery(lhs,rhs));
}

#endif // DERIVE_H
