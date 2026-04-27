#include "control_classes.h"
#include "database.h"
#include "tui.h"
#include <iostream>
#include <vector>
#include "logger.h"
#include <sstream>
//using namespace oracle::occi;
//using namespace std;


int main(int argc, char * argv[])
{
    
    Logger logger;
    logger.setLogFilePath("../logs/app.log");
    logger.log("PROGRAM STARTED");
    std::stringstream orders;

    for (int i = 0; i<argc; i++)
    {
        orders << argv[i];
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
        std::string input;
        if (argc < 2)
        {
            input = TUI::displayAndSelectPage(TUI::pageize(s.getStockBatchesInString(), 10));
        }
        logger.log("Stock retrieved from database.");

        orders << input;

        order o;

        std::string token;

        std::vector<int> productIDs;

        while(std::getline(orders, token, ' ' ))
        {
            try
            {
                productIDs.emplace_back(std::stoi(token));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                logger.log(e.what());
                return 1;
            }
            
        }
        for (auto i : productIDs)
        {
            o.addProduct(s.getProductBatches()[i].getProductType());
        }
        toat t = o.makeOrder(s);
        if(t.getContents().empty())
        {
            logger.log("Order canceled.");
            return 1;
        }
        t.setId(1);
        logger.log("Created toat from stock batches.");

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