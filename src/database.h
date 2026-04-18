#ifndef DATABASE_H
#define DATABASE_H

#include <string>

//#include <occi.h>

class Database {
private:
    //oracle::occi::Environment* env;
    //oracle::occi::Connection* dbc;

public:
    Database();
    ~Database();

    bool connect(const std::string& dsn);
    void disconnect();

    bool execute(const std::string& query);

    // 🔥 NEW HIGH LEVEL FUNCTIONS
    bool insertProduct(const std::string& name, int aisle, int qty);
    bool insertOrder(int orderId, const std::string& status);
    bool insertToat(int toatId, const std::string& name, int aisle);
};

#endif