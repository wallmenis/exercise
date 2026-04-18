#include "control_classes.h"
#include "database.h"
#include <iostream>
#include <vector>
#include <random>

int main()
{
    Database db;

    std::string dsn =
    
    "Driver={OracleODBC};"
    "Dbq=db.freesql.com:1521/23ai_34ui2;"
    "Uid=TAGARA_IOANNA1_SCHEMA_J4HA5;"
    "Pwd=YOUR_PASSWORD;";

    if (!db.connect(dsn)) return 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randQty(1, 10);


    //STOCK GENERATION

    std::vector<product> stock = {
        product("Shirt A", 1),
        product("Shoes B", 2),
        product("Hat A", 3)
    };

    // insert stock into database
    for (auto p : stock) {
        db.insertProduct(p.getName(), p.getAisle(), randQty(gen));
    }

  
    // ORDER GENERATION
  
    order o;
    o.add_product(stock[0]);
    o.add_product(stock[1]);

    db.insertOrder(1, "processing");

    //TOAT PROCESSING
   
    toat t;

    int toatId = 1;

    for (auto p : o.get_products()) {
        t.add_product(p);
        db.insertToat(toatId, p.getName(), p.getAisle());
    }

    o.set_status(order::completed);

    db.execute("UPDATE orders SET status='completed' WHERE id=1");

    std::cout << "WAREHOUSE JOB COMPLETED\n";

    return 0;
}