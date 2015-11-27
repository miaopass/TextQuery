#include "Query.h"
#include "Derive.h"
Query::Query(std::string sought) : q(new WordQuery(sought))
{

}
