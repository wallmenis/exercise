#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sql.h>
#include <sqlext.h>

class Database {
private:
    SQLHENV env;
    SQLHDBC dbc;

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