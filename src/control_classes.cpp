#include "control_classes.h"
#include <iostream>

// PRODUCT
product::product() 
{   
    name="";
    id=0;
}

product::product(std::string name, int id)
{
    this->name = name;
    this->id = id;
}

product::~product() {}

std::string product::getName()
{
    return name;
}
int product::getId()
{
    return id;
}
//////////////////////////////////////////////
// PRODUCT BATCH GENERATION

product_batch::product_batch() : quantity(0) {}

product_batch::product_batch(product p, int qty)
    : product_type(p), quantity(qty) {}

product_batch::~product_batch() {}

product product_batch::getProductType() {
    return product_type;
}

int product_batch::getQuantity() {
    return quantity;
}

product_batch product_batch::generateRandomBatch(product p) {
    std::uniform_int_distribution<> dis(1, 100);
    int random_qty = dis(gen);
    return product_batch(p, random_qty); 
}
////////////////////////////////////////////////////////

// ORDER
order::order() : status(processing) {}
order::~order() {}

void order::addProduct(product p) {
    products.push_back(p);
}

std::vector<product> order::getProducts() 
{
    return products;
}

order::order_status order::getStatus() {
    return status;
}

void order::setStatus(order_status new_status)
{
    status = new_status;
}


// TOAT
toat::toat() {}
toat::~toat() {}

void toat::addProduct(product p)
{
    contents.push_back(p);
}

void toat::print() {
    std::cout << "Toat contents:\n";
    for (auto p : contents) {
        std::cout << p.getName() << " (ID" << p.getId() << ")\n";
    }
}

// STOCK
stock::stock() {}
stock::~stock() {}
stock::stock(std::vector<product_batch> batches) {
    for (auto b : batches) {
        inventory[b.getProductType().getId()] = b;
    }
}
stock::stock(std::vector<product> products) {
    std::unordered_map<int, int> map;
    for (auto p : products){    // it is already initialized to 0, so we can just increment it (https://www.reddit.com/r/AskProgramming/comments/xhg6sw/do_value_for_keys_are_zero_by_default_in/)
        map[p.getId()]++;
    }
    for (auto p : products) {
        inventory[p.getId()] = product_batch(p, map[p.getId()]);
    }
}

void stock::addProduct(product p) {
    if (inventory.find(p.getId()) != inventory.end()) {
        inventory[p.getId()] = product_batch(p, inventory[p.getId()].getQuantity() + 1);
    } else {
        inventory[p.getId()] = product_batch(p, 1);
    }
}

bool stock::removeProduct(product p) {
    if (inventory.find(p.getId()) != inventory.end() && inventory[p.getId()].getQuantity() > 0) {
        inventory[p.getId()] = product_batch(p, inventory[p.getId()].getQuantity() - 1);
        return true;
    }
    return false;
}

std::vector<product> stock::getProducts() {
    std::vector<product> products;
    for (auto pair : inventory) {
        for (int i = 0; i < pair.second.getQuantity(); i++) {
            products.push_back(pair.second.getProductType());
        }
    }
    return products;
}

std::string stock::getStockInsertStatement() {
    std::string statement = "INSERT INTO stock (product_name, product_id, quantity) VALUES\n";
    bool first = true;
    for (auto pair : inventory) {
        if (!first) {
            statement += ",\n";
        }
        statement += "('" + pair.second.getProductType().getName() + "', " + std::to_string(pair.second.getProductType().getId()) + ", " + std::to_string(pair.second.getQuantity()) + ")";
        first = false;
    }
    statement += ";";
    return statement;
}
