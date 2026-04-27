#include "database.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

using namespace oracle::occi;

Database::Database(std::shared_ptr<Logger> logger, std::string configFilePath) {
    nlohmann::json j;
    std::string configuration;
    std::stringstream configStream;
    std::ifstream readStream(configFilePath);
    this->logger = logger;

    if (!readStream.is_open()) {
        logger->log("ERROR: Could not open conf.json");
        return;
    }

    configStream << readStream.rdbuf();
    configuration = configStream.str();
    
    j = nlohmann::json::parse(configuration);

    readStream.close(); 

    auto usernamef = j.find("username");
    auto passwordf = j.find("password");
    auto db_connection_stringf = j.find("db_connection_string");

    username = (usernamef != j.end()) ? usernamef->get<std::string>() : "";
    password = (passwordf != j.end()) ? passwordf->get<std::string>() : "";
    db_connection_string = (db_connection_stringf != j.end()) ? db_connection_stringf->get<std::string>() : "";


    isConnected = false;

    env = Environment::createEnvironment(Environment::DEFAULT);
}

Database::~Database() {
    if (isConnected) {
        disconnect();
    }
    Environment::terminateEnvironment(env);
}



bool Database::connect() {
    try {
        dbc = env->createConnection(username, password, db_connection_string);
        isConnected = true;
        return true;
    }
    catch (SQLException &e) {
        std::cerr << "ORACLE ERROR: " << e.getMessage() << std::endl;
        logger->log("Database connection failed: " + std::string(e.getMessage()));
        return false;
    }
}

bool Database::disconnect() {
    try {
        env->terminateConnection(dbc);
        isConnected = false;
        return true;
    }
    catch (SQLException &e) {
        std::cerr << "ORACLE ERROR: " << e.getMessage() << std::endl;
        logger->log("Database disconnection failed: " + std::string(e.getMessage()));
        return false;
    }
}

int Database::getLatestIDFromTable(std::string table)
{
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return 0;
    }
    try
    {
        std::string query = "SELECT id FROM " + table + " ORDER BY id DESC FETCH FIRST 1 ROW ONLY";
        logger->log("Executing query: " + query);
        Statement* stmt = dbc->createStatement(query);
        ResultSet* rs = stmt->executeQuery();
        int id;
        if (rs->next()) {
            id = rs->getInt(1);
            dbc->terminateStatement(stmt);
            return id;
        } else {
            dbc->terminateStatement(stmt);
            logger->log("ERROR: No toat found with id " + std::to_string(id) + " in table " + table);
            return 0;
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        logger->log(e.what());
        return 0;
    }
}

bool Database::updateStock(stock s)
{
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return false;
    }
    try {
        for (auto p : s.getProductBatches()) {
            std::string query = "UPDATE stock SET name = :1, quantity = :2 WHERE id = :3";
            if(getProductBatchById(p.second.getProductType().getId(), "stock").getQuantity() == 0) {
                query = "INSERT INTO stock ( name, quantity, id) VALUES ( :1, :2, :3)";
            }
            logger->log("Executing query: " + query);
            Statement* stmt = dbc->createStatement(query);
            stmt->setString(1, p.second.getProductType().getName());
            stmt->setInt(2, p.second.getQuantity());
            stmt->setInt(3, p.second.getProductType().getId());
            stmt->executeUpdate();
            dbc->terminateStatement(stmt);
        }
        return true;
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return false;
    }
}

stock Database::getStock(int start, int count){
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return stock();
    }
    try {
        std::string query = "SELECT name, id, quantity FROM stock OFFSET :1 ROWS FETCH NEXT :2 ROWS ONLY";
        bool fetchAll = false;
        if (start < 0 || count == 0) {
            logger->log("ERROR: Invalid start or count parameters for getStock");
            return stock();
        }
        if (count < 0)
        {
            query = "SELECT name, id, quantity FROM stock OFFSET :1 ROWS";
            fetchAll = true;
        }
        
        Statement* stmt = dbc->createStatement(query);
        stmt->setInt(1, start);
        if (!fetchAll) {
            stmt->setInt(2, count);
        }
        logger->log("Executing query: " + query);
        ResultSet* rs = stmt->executeQuery();

        stock s;
        while (rs->next()) {
            std::string name = rs->getString(1);
            int id = rs->getInt(2);
            int quantity = rs->getInt(3);
            s.addProductBatch(product_batch(product(name, id), quantity));
        }
        dbc->terminateStatement(stmt);
        return s;
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return stock();
    }
}

bool Database::removeProductBatchById(int id, const std::string& table)
{
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return false;
    }
    try {
        std::string query = "DELETE FROM " + table + " WHERE id = :1";
        logger->log("Executing query: " + query);
        Statement* stmt = dbc->createStatement(query);
        stmt->setInt(1, id);
        stmt->executeUpdate();
        dbc->terminateStatement(stmt);
        return true;
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return false;
    }
}


bool Database::updateToat(toat t) {
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return false;
    }
    try {
        if (getToatById(t.getId()).getId() == 0) { // if the toat doesn't exist, we insert it. Otherwise, we just update the contents.
            std::string query = "INSERT INTO toat (id, order_id) VALUES (:1, :2)";
            Statement* stmt = dbc->createStatement(query);
            stmt->setInt(1, t.getId());
            stmt->setInt(2, t.getOrderId());
            logger->log("Executing query: " + query);
            stmt->executeUpdate();
            dbc->terminateStatement(stmt);
        }
        for (auto p : t.getContents()) {
            std::string query = "UPDATE out_of_stock SET name = :1, quantity = :2 WHERE id = :3 AND toat_id = :4";
            if(getProductBatchById(p.getProductType().getId(), "out_of_stock").getQuantity() == 0 || getToatById(t.getId()).getId() == 0) {
                query = "INSERT INTO out_of_stock ( name, quantity, id, toat_id) VALUES ( :1, :2, :3, :4)";
            }
            logger->log("Executing query: " + query);
            Statement* stmt = dbc->createStatement(query);
            stmt->setString(1, p.getProductType().getName());
            stmt->setInt(2, p.getQuantity());
            stmt->setInt(3, p.getProductType().getId());
            stmt->setInt(4, t.getId());
            stmt->executeUpdate();
            dbc->terminateStatement(stmt);
        }
        return true;
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return false;
    }
}

product_batch Database::getProductBatchById(int id, const std::string& table) {
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return product_batch();
    }
    try {
        std::string query = "SELECT name, quantity FROM " + table + " WHERE id = :1";
        Statement* stmt = dbc->createStatement(query);
        stmt->setInt(1, id);
        logger->log("Executing query: " + query);
        ResultSet* rs = stmt->executeQuery();

        if (rs->next()) {
            std::string name = rs->getString(1);
            int quantity = rs->getInt(2);
            dbc->terminateStatement(stmt);
            return product_batch(product(name, id), quantity);
        } else {
            dbc->terminateStatement(stmt);
            logger->log("ERROR: No product found with id " + std::to_string(id) + " in table " + table);
            return product_batch();
        }
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return product_batch();
    }
}

bool Database::updateProductBatch(product_batch p, const std::string& table)
{
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return false;
    }
    try {
        std::string query = "UPDATE " + table + " SET name = :1, quantity = :2 WHERE id = :3";
        Statement* stmt = dbc->createStatement(query);
        stmt->setString(1, p.getProductType().getName());
        stmt->setInt(2, p.getQuantity());
        stmt->setInt(3, p.getProductType().getId());
        logger->log("Executing query: " + query);
        stmt->executeUpdate();
        dbc->terminateStatement(stmt);
        return true;
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return false;
    }
}



toat Database::getToatById(int id)
{
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return toat();
    }
    try {
        std::string query = "SELECT id, name, quantity FROM out_of_stock WHERE toat_id = :1";
        Statement* stmt = dbc->createStatement(query);
        stmt->setInt(1, id);
        logger->log("Executing query: " + query);
        ResultSet* rs = stmt->executeQuery();

        int loops = 0;
        // We loop through the result set and add each product to the toat. We also log an error if no products were found with the given toat_id.
        toat t;
        while (rs->next()) {
            std::string name = rs->getString(2);
            int quantity = rs->getInt(3);
            for (int i = 0; i < quantity; i++) {
                t.addProduct(product(name, rs->getInt(1)));
            }
            loops++;
        }
        dbc->terminateStatement(stmt);
        if (loops == 0) {
            logger->log("ERROR: No toat found with id " + std::to_string(id));
        }
        return t;
        
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return toat();
    }
}
/*
bool Database::removeByToatId(int id){
    if (!isConnected) {
        logger->log("ERROR: Not connected to database");
        return false;
    }
    
    try {
        std::string query = "DELETE FROM out_of_stock WHERE toat_id = :1";
        logger->log("Executing query: " + query);
        Statement* stmt = dbc->createStatement(query);
        stmt->setInt(1, id);
        stmt->executeUpdate();
        dbc->terminateStatement(stmt);
        return true;
    }
    catch (SQLException &e) {
        logger->log("ORACLE ERROR: " + std::string(e.getMessage()));
        return false;
    }
    
}*/