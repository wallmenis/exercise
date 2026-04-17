#include "control_classes.h"
#include <iostream>

// PRODUCT
product::product() : name(""), aisle(0) {}

product::product(std::string name, int aisle)
    : name(name), aisle(aisle) {}

product::~product() {}

std::string product::getName() const { return name; }
int product::getAisle() const { return aisle; }


// ORDER
order::order() : status(processing) {}
order::~order() {}

void order::add_product(const product& p) {
    products.push_back(p);
}

const std::vector<product>& order::get_products() const {
    return products;
}

order::order_status order::get_status() {
    return status;
}

void order::set_status(order_status new_status) {
    status = new_status;
}


// TOAT
toat::toat() {}
toat::~toat() {}

void toat::add_product(const product& p) {
    contents.push_back(p);
}

void toat::print() const {
    std::cout << "Toat contents:\n";
    for (const auto& p : contents) {
        std::cout << p.getName() << " (Aisle " << p.getAisle() << ")\n";
    }
}