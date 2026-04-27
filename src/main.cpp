#include "control_classes.h"
#include "database.h"
#include "tui.h"
#include <iostream>
#include <vector>
#include "logger.h"
#include <sstream>
//using namespace oracle::occi;
//using namespace std;


int main(int argc, char* argv[])
{
    Logger logger;
    logger.setLogFilePath("../logs/app.log");
    logger.log("PROGRAM STARTED");
    std::stringstream toOrder;
    for (int i = 0; i < argc; ++i) {
        logger.log("Argument " + std::to_string(i) + ": " + argv[i]);
        toOrder << argv[i] << " ";
    }

    try {
        Database db(std::make_shared<Logger>(logger), "../conf/conf.json");

        std::cout << "CONNECTING...\n";
        logger.log("Attempting to connect to database...");

        db.connect();

        std::cout << "CONNECTED SUCCESSFULLY!\n";
        logger.log("Database connection established.");

        stock s = db.getStock(0, -1);
        std::cout << "STOCK RETRIEVED:\n";
        std::string output = "";
        if (argc < 2) {
            output = TUI::displayAndSelectPage(TUI::pageize(s.getStockBatchesInString(), 10));
            logger.log("TUI INPUT: " + output);
        }
        toOrder << output;
        logger.log("Stock retrieved from database.");

        std::vector<int> productIDs;
        std::string token;

        order o;
        o.setOrderId(1);
        logger.log("Order created with ID: " + std::to_string(o.getOrderId()));
        while (std::getline(toOrder, token, ' ')) {
            if (!token.empty()) {
                try {
                    int id = std::stoi(token);
                    productIDs.push_back(id);
                } catch (const std::invalid_argument& e) {
                    logger.log("Invalid product ID: " + token);
                }
            }
        }
        for (auto id : productIDs) {
            logger.log("Product ID to order: " + std::to_string(id));
            o.addProduct(s.getProductBatches()[id].getProductType());
        }
        
        
        
        toat t = o.makeOrder(s);

        if (t.getContents().empty()) {
            logger.log("Failed to create toat from order.");
            std::cerr << "Failed to create toat from order.\n";
            return 1;
        }

        t.setId(1);
        logger.log("Created toat from stock batches.");
        logger.log("Toat details: " + t.print());

        db.updateToat(t);
        logger.log("Updated toat in database.");

        //TUI::displayAndSelectPage(TUI::pageize(t.print(), 10));

        //db.removeByToatId(t.getId());
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