#ifndef employees_hpp
#define employees_hpp

#include <iostream>
#include "Database.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdio.h>
#include <string.h>

#define CON Database &db = Database::getInstance(); Connection *con = db.getConnection();

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class employees {

public:
    static void totalSales();
};

#endif /* employee_hpp */
