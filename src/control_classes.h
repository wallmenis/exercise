#ifndef CONTROL_CLASSES_H
#define CONTROL_CLASSES_H

#include <vector>
#include <string>

class product
{
private:
    std::string name;
    int aisle;

public:
    product();
    product(std::string name, int aisle);
    ~product();

    std::string getName() const;
    int getAisle() const;
};

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

    void add_product(const product& p);
    const std::vector<product>& get_products() const;

    order_status get_status();
    void set_status(order_status new_status);

private:
    std::vector<product> products;
    order_status status;
};

class toat
{
private:
    std::vector<product> contents;

public:
    toat();
    ~toat();

    void add_product(const product& p);
    void print() const;
};

#endif