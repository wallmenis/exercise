/*
#include "database.h"
#include <iostream>


Database::Database() {
    
}

Database::~Database() {
    disconnect();
  
}

bool Database::connect(const std::string& dsn) {

}

void Database::disconnect() {
   
}

bool Database::execute(const std::string& query) {
    
}
bool Database::insertProduct(const std::string& name, int aisle, int qty) {
    return execute(
        "INSERT INTO products VALUES ('" +
        name + "', " +
        std::to_string(aisle) + ", " +
        std::to_string(qty) + ")"
    );
}

bool Database::insertOrder(int orderId, const std::string& status) {
    return execute(
        "INSERT INTO orders VALUES (" +
        std::to_string(orderId) + ", '" +
        status + "')"
    );
}

bool Database::insertToat(int toatId, const std::string& name, int aisle) {
    return execute(
        "INSERT INTO toats VALUES (" +
        std::to_string(toatId) + ", '" +
        name + "', " +
        std::to_string(aisle) + ")"
    );
}
    */