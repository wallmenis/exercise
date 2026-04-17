#ifndef CONTROL_CLASSES_H
#define CONTROL_CLASSES_H

#include <vector>
#include <string>

class product
{
private:
    std::string name;
public:
    product();
    ~product();
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

};



#endif // CONTROL_CLASSES_H