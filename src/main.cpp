#include "control_classes.h"
#include "database.h"
#include "tui.h"
#include <iostream>
#include <vector>
#include <random>
#include <occi.h>
//using namespace oracle::occi;
//using namespace std;


int main()
{
    std::cout << "PROGRAM STARTED\n";

    std::string output;

    output = TUI::displayAndSelectPage({"Welcome to the Warehouse Management System!\nThis is a simple TUI application that demonstrates basic database operations and control classes for managing products, orders, and stock.\n\nPress 'n' to continue to the next page.", "On the next pages, you will see examples of how to create products, manage orders, and maintain stock levels using C++ classes and a database connection.\n\nPress 'n' to continue.", "Finally, you will see how to connect to an Oracle database using OCCI and perform basic operations.\n\nPress 'q' to quit."});

    std::cout << "TUI OUTPUT:\n" << output << "\n";

    try {
        Database db;

        std::cout << "CONNECTING...\n";

        db.connect();

        std::cout << "CONNECTED SUCCESSFULLY!\n";

        db.disconnect();

        std::cout << "CLEAN EXIT\n";
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR\n";
    }

    std::cout << "PROGRAM END\n";
    return 0;

}