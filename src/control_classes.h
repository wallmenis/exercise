#ifndef CONTROL_CLASSES_H
#define CONTROL_CLASSES_H

#include <vector>
#include <string>
#include <unordered_map>
#include <random>

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

class product_batch     // this is a helper class for stock management, not used in main.cpp
{
private:
    product product_type;
    int quantity;
    static inline std::random_device rd;
    static inline std::mt19937 gen = std::mt19937(rd());
    
public:
    product_batch();
    product_batch(product p, int qty);
    ~product_batch();
    product getProductType();
    int getQuantity();
    void setQuantity(int qty);

    static product_batch generateRandomBatch(product p);
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
    int order_id;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class toat
{
private:
    int id;
    int order_id;
    std::vector<product_batch> contents;

public:
    toat();
    ~toat();

    void addProductBatch(product_batch p);
    void addProduct(product p);
    std::vector<product_batch> getContents();
    int getId();
    void setId(int new_id);
    int getOrderId();
    void setOrderId(int new_order_id);
    std::string print();
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
    void addProductBatch(product_batch b);
    bool removeProduct(product p);

    std::vector<product> getProducts();
    std::vector<product_batch> getProductBatches();
    
    std::string getStockBatchesInString();
};

#endif