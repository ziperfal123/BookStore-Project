#ifndef customers_hpp
#define customers_hpp

#include <stdio.h>
#include <iostream>
#include "Database.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string.h>

#define CON Database &db = Database::getInstance(); Connection *con = db.getConnection();

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class customers {
    
public:
    static int count ();
    static void customerList();
    static void howManyBooksForCustomer();
    static void CustomerWhoPurchasedTheMost();
    static void newCustomers();
    static void discountForCustomer();
};

#endif
