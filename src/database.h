#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <nlohmann/json.hpp>
#include "control_classes.h"
#include <occi.h>
#include "logger.h"
using namespace oracle::occi;


class Database {
private:
    Environment* env;
    Connection* dbc;
    std::string username;
    std::string password;
    std::string db_connection_string;
    bool isConnected;
    std::shared_ptr<Logger> logger;

public:
    Database(std::shared_ptr<Logger> logger, std::string configFilePath);
    ~Database();

    bool connect();
    bool disconnect();

    bool getIfTableIsEmpty(std::string table);
    int getLatestIDFromTable(std::string table);

    bool updateStock(stock s);
    stock getStock(int start, int count);

    bool updateToat(toat t);

    product_batch getProductBatchById(int id, const std::string& table);
    bool updateProductBatch(product_batch p, const std::string& table);
    bool removeProductBatchById(int id, const std::string& table);

    toat getToatById(int id);
    bool removeByToatId(int id);

};

#endif