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

class toat
{
private:
    std::vector<product> contents;
public:
    toat();
    ~toat();
    
};



#endif // CONTROL_CLASSES_H