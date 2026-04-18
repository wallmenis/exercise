#include "database.h"
#include <iostream>

Database::Database() {
    //SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    //SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    //SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
}

Database::~Database() {
    disconnect();
    //SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    //SQLFreeHandle(SQL_HANDLE_ENV, env);
}

bool Database::connect(const std::string& dsn) {
    /*SQLRETURN ret = SQLDriverConnectA(
        dbc,
        NULL,
        (SQLCHAR*)dsn.c_str(),
        SQL_NTS,
        NULL,
        0,
        NULL,
        SQL_DRIVER_COMPLETE
    );

    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Connected to DB\n";
        return true;
    }

    std::cout << "Connection failed\n";*/
    return false;
}

void Database::disconnect() {
    //SQLDisconnect(dbc);
}

bool Database::execute(const std::string& query) {
    //SQLHSTMT stmt;
    //SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
/*
    SQLRETURN ret = SQLExecDirectA(
        stmt,
        (SQLCHAR*)query.c_str(),
        SQL_NTS
    );

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    */
    return 1; //SQL_SUCCEEDED(ret);
}
bool Database::insertProduct(const std::string& name, int aisle, int qty) {
    return execute(
        "INSERT INTO products VALUES ('" +
        name + "', " +
        std::to_string(aisle) + ", " +
        std::to_string(qty) + ")"
    );
}

bool Database::insertOrder(int orderId, const std::string& status) {
    return execute(
        "INSERT INTO orders VALUES (" +
        std::to_string(orderId) + ", '" +
        status + "')"
    );
}

bool Database::insertToat(int toatId, const std::string& name, int aisle) {
    return execute(
        "INSERT INTO toats VALUES (" +
        std::to_string(toatId) + ", '" +
        name + "', " +
        std::to_string(aisle) + ")"
    );
}