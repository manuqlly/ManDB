#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query {
public:
    Query(const std::string& queryString);
    void parse();
    void execute();

private:
    std::string queryString;
};

#endif // QUERY_H