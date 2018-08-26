#include <iostream>
#include "Database.hpp"
#include "books.hpp"
#include "employees.hpp"
#include "suppliers.hpp"
#include "customers.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Database &db = Database::getInstance();
        
    cout << "Welcome to our Book Store! \n" <<
    "What would you like to do?" << endl;
    
    while (1) {
        db.printMenu();
        int choise;
        cin >> choise;
        switch (choise) {
            case 1:
                books::inventory();
                break;
            case 2:
                books::orders();
                break;
            case 3:
                customers::customerList();
                break;
            case 4:
                suppliers::SupplierList();
                break;
            case 5:
                books::ordersByDate();
                break;
            case 6:
                books::DiscuntedBooks();
                break;
            case 7:
                books::bookSearching();
                break;
            case 8:
                suppliers::searchingSupplierByBookName();
                break;
            case 9:
                books::booksSince();
                break;
            case 10:
                customers::howManyBooksForCustomer();
                break;
            case 11:
                customers::CustomerWhoPurchasedTheMost();
                break;
            case 12:
                suppliers::topSupllier();
                break;
            case 13:
                books::OrdersAmount();
                break;
            case 14:
                books::PhurchacesAmount();
                break;
            case 15:
                customers::discountForCustomer();
                break;
            case 16:
                books::incomes();
                break;
            case 17:
                customers::newCustomers();
                break;
            case 18:
                suppliers::totalOrders();
                break;
            case 19:
                employees::totalSales();
                break;
            case 20:
                books::top10Books();
                break;
            case 99:
                cout << "Have a Great Day!" << endl;
                exit(1);
            default:
                cout << "Invalid choise, try again" << endl;
                break;
        }
    }
    
}
