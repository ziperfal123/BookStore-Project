#ifndef suppliers_hpp
#define suppliers_hpp

#include <iostream>
#include "Database.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdio.h>
#include <string.h>

#define CON Database &db = Database::getInstance(); Connection *con = db.getConnection();

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class suppliers {
    
public:
    static int count ();
    static void SupplierList();
    static void searchingSupplierByBookName();
    static void topSupllier();
    static void totalOrders();
    
};
#endif /* suplier_hpp */
