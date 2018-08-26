#ifndef books_hpp
#define books_hpp

#include <iostream>
#include "Database.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdio.h>
#include <string.h>

#define CON Database &db = Database::getInstance(); Connection *con = db.getConnection();

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class books {
    
public:
    
    static int count ();
    static void inventory ();
    static void orders();
    static void ordersByDate();
    static void DiscuntedBooks();
    static void bookSearching();
    static void booksSince();
    static void OrdersAmount();
    static void PhurchacesAmount();
    static void top10Books();
    static void incomes();
};


#endif /* books_hpp */
