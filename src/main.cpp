#include "control_classes.h"
#include "database.h"
#include <iostream>
#include <vector>
#include <random>
#include <occi.h>
using namespace oracle::occi;
//using namespace std;


int main()
{
    std::cout << "PROGRAM STARTED\n";

    std::string test;

    std::cin >> test;

    std::cout << "TEST: " << test << "\n";
    

    try {
        std::cout << "CREATING ENV...\n";

        Environment *env = Environment::createEnvironment(Environment::DEFAULT);

        std::cout << "CONNECTING...\n";

        Connection *conn = env->createConnection(
            "TAGARA_IOANNA1_SCHEMA_J4HA5",
            "GE59HPMrE02RSJ1886A$6TX9WVIXAH",
            "db.freesql.com:1521/23ai_34ui2"
        );

        std::cout << "CONNECTED SUCCESSFULLY!\n";


        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);

        std::cout << "CLEAN EXIT\n";
    }
    catch (SQLException &e) {
        std::cerr << "ORACLE ERROR: " << e.getMessage() << std::endl;
    }
    catch (...) {
        std::cerr << "UNKNOWN ERROR\n";
    }

    std::cout << "PROGRAM END\n";
    return 0;


/*

    //STOCK GENERATION

    std::vector<product> stock = {
        product("Shirt A", 1),
        product("Shoes B", 2),
        product("Hat A", 3)
    };

    // insert stock into database
    for (auto p : stock) {
        db.insertProduct(p.getName(), p.getId(), randQty(gen));
    }

  
    // ORDER GENERATION
  
    order o;
    o.addProduct(stock[0]);
    o.addProduct(stock[1]);

    db.insertOrder(1, "processing");

    //TOAT PROCESSING
   
    toat t;

    int toatId = 1;

    for (auto p : o.getProducts()) {
        t.addProduct(p);
        db.insertToat(toatId, p.getName(), p.getId());
    }

    o.setStatus(order::completed);

    db.execute("UPDATE orders SET status='completed' WHERE id=1");

    std::cout << "WAREHOUSE JOB COMPLETED\n";

    return 0;

    */
}