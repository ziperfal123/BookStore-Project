#include "employees.hpp"

void clearBuff() {
    string temp;
    getline(cin, temp);
}

void employees::totalSales(){
    CON;
    if (con) {
        
        string employeeName, startDate, endDate;
        
        PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Orders natural join Employees where Emp_Name=? AND Order_Date>=? AND Order_Date<=?;");
        
        cout << "Please Enter Employee Name > ";
        clearBuff();
        getline(cin, employeeName);
        pstmt->setString(1, employeeName);
        cout << "Please Enter Start Date in the following format- YYYY-MM-DD > ";
        getline(cin, startDate);
        pstmt->setString(2, startDate);
        cout << "Please Enter End Date in the following format- YYYY-MM-DD > ";
        getline(cin, endDate);
        pstmt->setString(3, endDate);
        
        
        ResultSet *rset = pstmt->executeQuery();
        
        if (rset->first()){
            cout << "\n" << rset->rowsCount() << " Sales for  " << employeeName << " Between " << startDate << " and " << endDate << "\n" << endl;
        }
        else
            cout << "\nInvalid Input Or No Sales for " << employeeName << " in this range of dates\n" << endl;
        
        delete con;
        delete pstmt;
        delete rset;
    }
}
