#include <iostream>
#include <random>
#include <string>

int main()
{
    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distrNames(1, 10); // Define the range
    std::uniform_int_distribution<> distrIsles(1, 20); // Define the range

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


    std::cout << "Product, Isle" << std::endl;

    // Generate and print 10 random numbers
    for (int i = 0; i < 10; ++i) {
        std::cout << names[distrNames(gen) - 1] << ",";
        std::cout << distrIsles(gen);
        std::cout << std::endl;
    }
    

    return 0;
}