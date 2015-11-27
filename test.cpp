#include"TextQuery.h"
#include"Query.h"
#include"Derive.h"
int main()
{
    std::ifstream is("text.txt");
    TextQuery tq(is);
    int i = 1;
    while(i--)
    {
        Query q1("I");
        Query q2("her");
        Query q3("and");
        (q1&q2).eval(tq).print(std::cout);
        (q1&q2|q3).eval(tq).print(std::cout);
        (~q2&q3).eval(tq).print(std::cout);
    }
    std::cin>>i;
    return 0;
}
