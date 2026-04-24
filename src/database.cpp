#include "database.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace oracle::occi;

Database::Database() {
    nlohmann::json j;
    std::string configuration;
    std::stringstream configStream;
    std::ifstream readStream("conf.json");

    if (!readStream.is_open()) {
        std::cerr << "ERROR: Could not open conf.json\n";
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
        return false;
    }
}


product_batch Database::getProductBatchById(int id, const string& table) {
    if (!isConnected) {
        std::cerr << "ERROR: Not connected to database\n";
        return product_batch();
    }
    try {
        Statement* stmt = dbc->createStatement("SELECT name, quantity FROM " + table + " WHERE id = :id");
        stmt->setInt(1, id);
        ResultSet* rs = stmt->executeQuery();

        if (rs->next()) {
            std::string name = rs->getString(1);
            int quantity = rs->getInt(2);
            dbc->terminateStatement(stmt);
            return product_batch(name, id, quantity);
        } else {
            dbc->terminateStatement(stmt);
            std::cerr << "ERROR: No product found with id " << id << " in table " << table << "\n";
            return product_batch();
        }
    }
    catch (SQLException &e) {
        std::cerr << "ORACLE ERROR: " << e.getMessage() << std::endl;
        return product_batch();
    }
}

bool Database::updateProductBatch(product_batch p, const string& table)
{
    if (!isConnected) {
        std::cerr << "ERROR: Not connected to database\n";
        return false;
    }
    try {
        std::string query = "UPDATE " + table + " SET name = :name, quantity = :quantity WHERE id = :id";
        if (getProductBatchById(p, table).getProductType().getId() == 0)
        {
            query = "INSERT INTO " + table + " (name, quantity, id) VALUES (:name, :quantity, :id)";
        }
        
        Statement* stmt = dbc->createStatement(query);
        stmt->setString(1, p.getProductType().getName());
        stmt->setInt(2, p.getQuantity());
        stmt->setInt(3, p.getProductType().getId());
        stmt->executeUpdate();
        dbc->terminateStatement(stmt);
        return true;
    }
    catch (SQLException &e) {
        std::cerr << "ORACLE ERROR: " << e.getMessage() << std::endl;
        return false;
    }
}

toat Database::getToatById(int id)
{
    if (!isConnected) {
        std::cerr << "ERROR: Not connected to database\n";
        return toat();
    }
    try {
        std::string query = "SELECT id, name, quantity FROM out_of_stock WHERE toat_id = :id";
        Statement* stmt = dbc->createStatement(query);
        stmt->setInt(1, id);
        ResultSet* rs = stmt->executeQuery();

        int loops = 0;
        while (rs->next()) {
            int toat_id = rs->getInt(1);
            std::string name = rs->getString(2);
            int quantity = rs->getInt(3);
            dbc->terminateStatement(stmt);
            return toat(name, id, quantity);
            loops++;
        }
        dbc->terminateStatement(stmt);
        if (loops == 0) {
            std::cerr << "ERROR: No toat found with id " << id << "\n";
        }
        return toat();
        
    }
    catch (SQLException &e) {
        std::cerr << "ORACLE ERROR: " << e.getMessage() << std::endl;
        return toat();
    }
}