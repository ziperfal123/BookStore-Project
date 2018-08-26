#include "customers.hpp"


int customers:: count (){
    CON;
    int counter = 0;
    if (con) {
        Statement *stmt = con->createStatement();
        ResultSet *rset = stmt->executeQuery("SELECT count(*) as cnt from Customers");
        rset->first();
        counter = rset->getInt("cnt");
        delete con;
        delete rset;
        delete stmt;
    }
    return counter;
}

void customers:: customerList(){
    CON;
    if (con) {
        Statement *stmt = con->createStatement();
        ResultSet *rset = stmt->executeQuery("SELECT * FROM Customers");
        cout << left << setw(18) << "\nID";
        cout << left << setw(22) << "Name";
        cout << left << setw(32) << "Revenues From Customer";
        cout << left << setw(26) << "Joining Date" << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        while (rset->next()){
            cout << left << setw(16) << rset->getString(1);
            cout << left << setw(24) << rset->getString(2);
            cout << right << setw(12) << rset->getString(3);
            cout << right << setw(26) << rset->getString(4) << endl;
        }
        cout << "\n";
        delete con;
        delete rset;
        delete stmt;
    }
    
}

void customers:: howManyBooksForCustomer(){
    CON;
    if (con) {
        
        string CustomerName, Date;
        
        PreparedStatement *pstmt1 = con->prepareStatement("CREATE TABLE IF NOT EXISTS temp3 AS SELECT * FROM Orders natural join OrdersContent;");
        pstmt1->execute();
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM temp3 natural join Customers WHERE Customer_Name=? AND Order_Date>? AND Order_Status!='Cancelled'");
        
        cout << "Please Enter Customer Name > ";
        string temp;
        getline(cin, temp);
        getline(cin, CustomerName);
        pstmt->setString(1, CustomerName);
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        getline(cin, Date);

        pstmt->setString(2, Date);
        ResultSet *rset = pstmt->executeQuery();
        
        rset->beforeFirst();
        if (rset->first()){
            cout << "\n" << CustomerName << " Purchased " << rset->rowsCount() << " Books Since " << Date << "\n" << endl;
        }
        else
            cout << "\nInvalid Input Or no orders for specific Customer\n" << endl;
        
        pstmt1 = con->prepareStatement("drop table temp3");
        pstmt1->executeQuery();
        
        delete con;
        delete pstmt1;
        delete pstmt;
        delete rset;
    }
}

void customers:: CustomerWhoPurchasedTheMost(){
    CON;
    if (con) {
        
        string Date;
        
        PreparedStatement *pstmt1 = con->prepareStatement("CREATE TABLE IF NOT EXISTS temp3 AS SELECT * FROM Orders natural join OrdersContent;");
        pstmt1->execute();
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT Customer_Name,COUNT(`Customer_Name`) AS `value_occurrence` FROM temp3 natural join Customers where Order_Status='Purchased' AND Order_Date>? GROUP BY `Customer_Name` ORDER BY `value_occurrence` DESC LIMIT 1;");
        
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        string temp;
        getline(cin, temp);
        getline(cin, Date);
        pstmt->setString(1, Date);

        ResultSet *rset = pstmt->executeQuery();
        
        if (rset->first()){
            cout << "\n" << rset->getString("Customer_Name") << " Purchased The Most Books Since " << Date << " - " <<  rset->getString("value_occurrence") << " Books \n" << endl;
        }
        else
            cout << "\nInvalid Input Or No Customers Found That Ordered Books After The Specific Date\n" << endl;
        
        pstmt1 = con->prepareStatement("drop table temp3");
        pstmt1->executeQuery();
        
        delete con;
        delete pstmt1;
        delete rset;
    }
}

void customers::newCustomers(){
    CON;
    if (con) {
        
        string Date;
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Customers WHERE Added_To_System_Date>=?");
        
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        string temp;
        getline(cin, temp);
        getline(cin, Date);
        pstmt->setString(1, Date);
        
        ResultSet *rset = pstmt->executeQuery();
        
        if (rset->first()){
            rset->beforeFirst();
            cout << "\n" << rset->rowsCount() << " Customers Joind Since " << Date << "\n" << endl;
            
        }
        else
            cout << "\nInvalid Input Or No Customers Joined Since " << Date << "\n" << endl;
        
        delete con;
        delete pstmt;
        delete rset;
    }
}

void customers::discountForCustomer(){
    CON;
    if (con) {
        
         string CustomerName, Date;
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Customers WHERE Customer_Name=? AND Added_To_System_Date>=?");
        
        cout << "Please Enter Customer Name > ";
        string temp;
        getline(cin, temp);
        getline(cin, CustomerName);
        pstmt->setString(1, CustomerName);
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        getline(cin, Date);
        
        pstmt->setString(2, Date);
        ResultSet *rset = pstmt->executeQuery();
        
        
        if (rset->first()){
            float dis = stof(rset->getString("Total_discount_recived"));
            dis*=100;
            cout << "\n" << CustomerName << " Recived " <<
            dis << "% Discount since "  << Date << "\n" << endl;
        }
        else
            cout << "\nInvalid Input Or No Discount for Customer Since " << Date << "\n" << endl;
        
        delete con;
        delete pstmt;
        delete rset;
    }
}


