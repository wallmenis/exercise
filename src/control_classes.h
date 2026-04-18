#ifndef CONTROL_CLASSES_H
#define CONTROL_CLASSES_H

#include <vector>
#include <string>
#include <unordered_map>

class product
{
private:
    std::string name;
    int id;

public:
    product();
    product(std::string name, int id);
    ~product();

    std::string getName();
    int getId();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class order {
public:
    enum order_status
    {
        processing,
        completed,
        cancelled
    };

    order();
    ~order();

    void addProduct(product p);
    std::vector<product> getProducts();

    order_status getStatus();
    void setStatus(order_status new_status);

private:
    std::vector<product> products;
    order_status status;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class toat
{
private:
    std::vector<product> contents;

public:
    toat();
    ~toat();

    void addProduct(product p);
    void print();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class product_batch     // this is a helper class for stock management, not used in main.cpp
{
private:
    product product_type;
    int quantity;
public:
    product_batch();
    product_batch(product p, int qty);
    ~product_batch();
    product getProductType();
    int getQuantity();

    static product_batch generateRandomBatch(product p);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class stock
{
private:
    std::unordered_map<int, product_batch> inventory;

public:
    stock();
    stock(std::vector<product_batch> batches);
    stock(std::vector<product> products);
    ~stock();

    void addProduct(product p);
    bool removeProduct(product p);

    std::vector<product> getProducts();
};

#endif