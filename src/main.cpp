#include "control_classes.h"
#include "database.h"
#include "tui.h"
#include <iostream>
#include <vector>
#include <random>
#include <occi.h>
#include "logger.h"
//using namespace oracle::occi;
//using namespace std;


int main()
{
    
    Logger logger;
    logger.setLogFilePath("../logs/app.log");
    logger.log("PROGRAM STARTED");

    //std::string output;

    //output = TUI::displayAndSelectPage({"Welcome to the Warehouse Management System!\nThis is a simple TUI application that demonstrates basic database operations and control classes for managing products, orders, and stock.\n\nPress 'n' to continue to the next page.", "On the next pages, you will see examples of how to create products, manage orders, and maintain stock levels using C++ classes and a database connection.\n\nPress 'n' to continue.", "Finally, you will see how to connect to an Oracle database using OCCI and perform basic operations.\n\nPress 'q' to quit."});

    //std::cout << "TUI OUTPUT:\n" << output << "\n";
    //logger.log("TUI OUTPUT: " + output);

    try {
        Database db(std::make_shared<Logger>(logger), "../conf/conf.json");

        std::cout << "CONNECTING...\n";
        logger.log("Attempting to connect to database...");

        db.connect();

        std::cout << "CONNECTED SUCCESSFULLY!\n";
        logger.log("Database connection established.");

        stock s = db.getStock(0, -1);
        std::cout << "STOCK RETRIEVED:\n";
        TUI::displayAndSelectPage(TUI::pageize(s.getStockBatchesInString(), 10));
        logger.log("Stock retrieved from database.");
        s.getProductBatches();
        toat t;
        for (auto p : s.getProductBatches()) {
            t.addProductBatch(p);
        }
        t.setId(1);
        logger.log("Created toat from stock batches.");

        db.updateToat(t);
        logger.log("Updated toat in database.");

        TUI::displayAndSelectPage(TUI::pageize(t.print(), 10));

        db.removeByToatId(t.getId());
        logger.log("Removed toat from database.");

        db.disconnect();

        std::cout << "CLEAN EXIT\n";
        logger.log("Database connection closed. Exiting program.");
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR\n";
        logger.log("An unknown error occurred.");
    }

    logger.log("PROGRAM END");
    logger.log("Exiting program.");
    return 0;

}