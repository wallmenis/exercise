#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <nlohmann/json.hpp>
#include "control_classes.h"
#include <occi.h>

class Database {
private:
    //oracle::occi::Environment* env;
    //oracle::occi::Connection* dbc;

public:
    Database();
    ~Database();

    bool connect();
    void disconnect();

    bool updateStock(stock s);
    stock getStock();

    bool updateToat(toat t);
    toat getToat();

    bool updateOutOfStockProducts(std::vector<product> products);
    std::vector<product> getOutOfStockProducts();
};

#endif