#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <nlohmann/json.hpp>
#include "control_classes.h"
#include <occi.h>
using namespace oracle::occi;


class Database {
private:
    Environment* env;
    Connection* dbc;
    std::string username;
    std::string password;
    std::string db_connection_string;
    bool isConnected;

public:
    Database();
    ~Database();

    bool connect();
    bool disconnect();

    bool updateStock(stock s);
    stock getStock();

    bool updateToat(toat t);
    toat getToat();

    product_batch getProductBatchById(int id, const string& table);

    bool updateProductBatch(product_batch p, const string& table);

    toat getToatById(int id);
    bool updateToatContents(toat t);

};

#endif