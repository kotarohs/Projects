#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

sql::Connection* get_db_connection() {
    sql::Driver* driver = get_driver_instance();
    sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "root", "123456789");
    con->setSchema("hostel_booking_system");
    return con;
}

#endif // DB_CONNECTION_H
