#include <iostream>
#include <random>
#include <string>
#include "../database.h"
#include "../control_classes.h"
#include "../logger.h"

int main()
{
    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distrQuantities(1, 20); // Define the range

    std::string names[] = {
        "Shirt A", 
        "Shirt B", 
        "Shorts", 
        "Socks A", 
        "Socks B", 
        "Shoes A", 
        "Shoes B", 
        "Hat A", 
        "Hat B", 
        "Gloves"
    };

    Logger logger;
    logger.setLogFilePath("../logs/generator.log");
    Database db(std::make_shared<Logger>(logger), "../conf/conf.json");
    db.connect();

    // Generate and print 10 random numbers
    for (int i = 0; i < 10; ++i) {
        db.updateStock(stock({product_batch(product(names[i], i+1), distrQuantities(gen))}));
    }
    
    db.disconnect();

    return 0;
}