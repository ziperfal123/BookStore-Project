#include "Database.hpp"

Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
    connection_properties["hostName"] = DB_HOST;
    connection_properties["port"] = DB_PORT;
    connection_properties["userName"] = DB_USER;
    connection_properties["password"] = DB_PASS;
    connection_properties["OPT_RECONNECT"] = true;
    
    // use database
    try {
        Connection *con = driver->connect(connection_properties);
        try {
            con->setSchema("BookStore");
        }
        catch (SQLException &e) {
            Statement *stmt = con->createStatement();
            stmt->execute("CREATE DATABASE IF NOT EXISTS BookStore");
            con->setSchema("BookStore");
            stmt->execute("CREATE TABLE IF NOT EXISTS Books ( "
                          "ISBN varchar(13), "
                          "Book_Name varchar(30) not null, "
                          "Category varchar(30), "
                          "Book_Language varchar(30), "
                          "Author varchar(30), "
                          "Publishing_Year varchar(4), "
                          "PRIMARY KEY (ISBN), "
                          "KEY (Book_Name) "
                          ")");
            stmt->execute("CREATE TABLE IF NOT EXISTS TheStoreBooks ( "
                          "ISBN varchar(13), "
                          "Books_Amount INT, "
                          "Price FLOAT, "
                          "Global_Discount FLOAT,"
                          "PRIMARY KEY(ISBN), "
                          "FOREIGN KEY (ISBN) REFERENCES Books(ISBN) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Employees ( "
                          "Emp_ID varchar(10), "
                          "Emp_Name varchar(30), "
                          "Salary FLOAT, "
                          "JoiningToStoreDate date, "
                          "BooksSold_TotalMoneyAmount FLOAT, "
                          "PRIMARY KEY (Emp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS EmployeesPhones ( "
                          "Emp_ID varchar (10), "
                          "Phone_Number varchar (14), "
                          "PRIMARY KEY (Emp_ID,Phone_Number), "
                          "FOREIGN KEY (Emp_ID) REFERENCES Employees(emp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Suppliers ( "
                          "Supp_ID varchar(10), "
                          "Supp_Name varchar(30) not null, "
                          "Incomes_From_Store float, "
                          "Added_To_System_Date date, "
                          "PRIMARY KEY (Supp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS SuppliersPhones ( "
                          "Supp_ID varchar (10), "
                          "phone_number varchar (14), "
                          "PRIMARY KEY (Supp_ID,phone_number), "
                          "FOREIGN KEY (Supp_ID) REFERENCES Suppliers (Supp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS SuppliersBooks ( "
                          "Supp_ID varchar(10), "
                          "ISBN varchar(13), "
                          "Amount int, "
                          "Price float, "
                          "PRIMARY KEY (Supp_ID,ISBN), "
                          "FOREIGN KEY (ISBN) REFERENCES Books (ISBN), "
                          "FOREIGN KEY (Supp_ID) REFERENCES Suppliers (Supp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Customers ( "
                          "Customer_ID varchar(10), "
                          "Customer_Name varchar(30), "
                          "Expenses FLOAT, "
                          "Expenses_This_Year INT, "
                          "Total_discount_recived FLOAT,"
                          "Added_To_System_Date date, "
                          "PRIMARY KEY (Customer_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS Orders ( "
                          "Order_Number INT UNSIGNED AUTO_INCREMENT, "
                          "Customer_ID varchar(10), "
                          "Emp_ID varchar(10), "
                          "Order_Status ENUM ('Ordered', 'Arrived', 'messageSent', 'Purchased' , 'Cancelled'), "
                          "Order_Date date, "
                          "Total_Price FLOAT, "
                          "PRIMARY KEY (Order_Number), "
                          "FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID), "
                          "FOREIGN KEY (Emp_ID) REFERENCES Employees(Emp_ID) "
                          ");");
            stmt->execute("CREATE TABLE IF NOT EXISTS OrdersContent ( "
                          "Order_Number INT UNSIGNED AUTO_INCREMENT,"
                          "Book_Name varchar(30) not null,"
                          "FOREIGN KEY (Order_Number) REFERENCES Orders(Order_Number),"
                          "FOREIGN KEY (Book_Name) REFERENCES Books(Book_Name),"
                          "PRIMARY KEY (Order_Number,Book_Name)"
                          ");");
            stmt->execute("CREATE TABLE  IF NOT EXISTS Suppliment("
                          "Supp_ID varchar (9),"
                          "ISBN varchar (13),"
                          "supplied INT,"
                          "Order_Date date,"
                          "FOREIGN KEY (Supp_ID) REFERENCES Suppliers (Supp_ID),"
                          "PRIMARY KEY (Supp_ID,ISBN));");
            stmt->execute("CREATE TABLE IF NOT EXISTS CustomersPhones ( "
                          "Customer_ID varchar(30), "
                          "Phone_number varchar(14), "
                          "PRIMARY KEY (Customer_ID,Phone_number), "
                          "FOREIGN KEY (Customer_ID) REFERENCES Customers(Customer_ID) "
                          ")");
            addBooksToWorld();     
            addBooksToStore();
            addCustomers();
            addCustomersPhones();
            addEmployees();
            addEmployeesPhones();
            addSuppliers();
            addSuppliersPhones();
            addOrders();
            addSuppliersBooks();
            addOrdersDetails();
            addSuppliment();
            
            delete stmt;
        }
        
        delete con;
    }
    catch (SQLException &e) {
        cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
    }
}

Database & Database::getInstance() {
    if (Database::instance == 0) {
        instance = new Database();
    }
    return *instance;
}

Connection * Database::getConnection() {
    try {
        Connection *con = driver->connect(connection_properties);
        con->setSchema(DB_NAME);
        return con;
    } catch (SQLException &e) {
        cout << e.what();
    }
    return 0;
}

void Database::addBooksToWorld(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Books(ISBN,Book_Name,Category,Book_Language,Author,Publishing_Year)"
                  "VALUES('888147660-6','Medic Of The Banished','Adventure','English','Laurena Mee','2016'),"
                  "('623753193-9','Armies Of Agony','Drama','English','Kanya Stocken','1997'),"
                  "('161913965-0','Sounds Of The Maze','Drama','Franch','Aylmer Clemow', '2013'),"
                  "('561800464-X','Ogre Without Desire','Fantacy','English','Fletch Dormand','1990'),"
                  "('089179767-X','Vanish At The Past','Fantasy','English','Davey Dykins','1989'),"
                  "('374822624-1','Women Of The Evening','Romance','Franch','Markos Krebs','1993'),"
                  "('867529509-X','Careful Of Nature','Horor','Hebrew','Shellie Service','1998'),"
                  "('754692835-4','Bunnies Of Mystery','Children','English','Paxon Oxby','2017'),"
                  "('578859010-8','Revival In My Town','Mystery','English','Sherwood Patience','1990'),"
                  "('600789272-7','Songs With A Hat','Humor','Hebrew','Urbain Cescotti','1992'),"
                  "('250024852-6','Mutants Asking Questions','Horor','English','Drusilla Van De Cappelle','2018'),"
                  "('552547148-5','Patrons And Patrons','Drama','English','Constantin Jodrelle','2015'),"
                  "('119639776-7','Union Of The Stockades','Adventure','Italian','Erastus McBeath','1990'),"
                  "('126219423-7','Admiring The Light','Drama','Hindi','Rae Venton','1992'),"
                  "('095254332-X','Lust Of Hell','Romance','English','Clarissa Addionisio','1988');");
}

void Database::addBooksToStore(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into TheStoreBooks(ISBN,Books_Amount,Price,Global_Discount)"
                  "VALUES('888147660-6','12','39','0'),"
                  "('623753193-9','20','56','0.2'),"
                  "('561800464-X','10','49','0'),"
                  "('374822624-1','35','39','0.1'),"
                  "('867529509-X','25','59','0'),"
                  "('600789272-7','30','25','0'),"
                  "('250024852-6','15','49','0.3'),"
                  "('552547148-5','10','25','0'),"
                  "('119639776-7','40','39','0.2'),"
                  "('095254332-X','50','20','0');");
}

void Database::addCustomers(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Customers(Customer_ID,Customer_Name,Expenses,Expenses_This_Year,Total_discount_recived,Added_To_System_Date)"
                  "VALUES('201764949','Erik Hounsham','3000','1200','0.1','2018-07-09'),"
                  "('201954912','Niels Strelitzer','819','500','0.1','2017-02-21'),"
                  "('401795834','Cindelyn Labeuil','955','800','0.2','2018-04-01'),"
                  "('503860353','Collete Thomerson','1990','1000','0.1','2017-12-15'),"
                  "('201943842','Andrea Ozintsev','485','200','0.1','2017-01-25'),"
                  "('302993813','Pearla McOrkill','1843','1300','0','2018-02-21'),"
                  "('561038427','Chadd Kloska','1300','940','0.2','2017-07-08'),"
                  "('354095689','Geri Tuftin','1663','1340','0','2018-01-25'),"
                  "('353941513','Danny Fourcade','55','55','0.1','2018-02-07'),"
                  "('491756877','Tamara Perassi','1998','1398','0.1','2017-08-03');");
}
    
void Database::addCustomersPhones(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into CustomersPhones(Customer_ID,Phone_number)"
                  "VALUES('201764949','(504) 8008524'),"
                  "('201954912','(965) 9821447'),"
                  "('401795834','(339) 3047428'),"
                  "('503860353','(339) 5281345'),"
                  "('201943842','(420) 2437829'),"
                  "('201943842','(846) 3771753'),"
                  "('302993813','(697) 6491263'),"
                  "('561038427','(432) 1211491'),"
                  "('354095689','(755) 8739067'),"
                  "('353941513','(164) 6929417'),"
                  "('353941513','(319) 1754773'),"
                  "('491756877','(149) 6587422');");
}

void Database::addEmployees(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Employees(Emp_ID,Emp_Name,Salary,JoiningToStoreDate,BooksSold_TotalMoneyAmount)"
                  "VALUES('079727787','Kala Rollins',4752,'2018-07-19','110'),"
                  "('569422207','Barry Henrichsen','9235','2018-04-22','710'),"
                  "('499263433','Yorgos Meredyth','8869','2017-02-09','820'),"
                  "('392704018','Helga Longhirst','5044','2017-01-15','560'),"
                  "('823213354','Rafe Newlands','5718','2018-07-06','780'),"
                  "('403252037','Morty Assandri','6514','2017-09-13','290'),"
                  "('157438974','Kikelia Mahaddy','5799','2018-08-03','950'),"
                  "('582039536','Mahmud Blaise','9062','2017-07-11','500'),"
                  "('534971565','Kikelia Mahaddy','5799','2017-10-06','950'),"
                  "('652444153','Ynes St. Paul','4712','2017-07-19','590'),"
                  "('382224948','Armand Berthouloume','8555','2017-11-20','790');");
}

void Database::addEmployeesPhones(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into EmployeesPhones(Emp_ID,Phone_number)"
                  "VALUES('079727787','(419) 8717088'),"
                  "('569422207','(604) 4280875'),"
                  "('499263433','(687) 5190471'),"
                  "('392704018','(878) 7121872'),"
                  "('823213354','(371) 3050646'),"
                  "('403252037','(251) 9554452'),"
                  "('157438974','(784) 5712861'),"
                  "('582039536','(432) 1211491'),"
                  "('534971565','(620) 7515862'),"
                  "('652444153','(287) 8807580'),"
                  "('382224948','(716) 5155960');");
}

void Database::addSuppliers(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Suppliers(Supp_ID,Supp_Name,Incomes_From_Store,Added_To_System_Date)"
                  "VALUES('625632797', 'Harvey Winkle', 1200, '2017-12-18'),"
                  "('721276415', 'Giralda Boddice', 1950, '2017-01-26'),"
                  "('839113642', 'Winn Shutte', 400, '2018-07-01'),"
                  "('349686016', 'Seth Joesbury', 3042, '2017-06-22'),"
                  "('288423058', 'Scarlett Dibb', 600, '2018-01-09'),"
                  "('015129428', 'Shari Besant', 1080, '2018-08-03'),"
                  "('631483430', 'Val Standrin', 480, '2017-11-15'),"
                  "('412616694', 'Lari Bartolomeu', 0, '2017-06-22'),"
                  "('809995153', 'Mommy Chilcott', 1080, '2018-03-21'),"
                  "('124425982', 'Grover Goozee', 0, '2017-02-24'),"
                  "('935903924', 'Flossi Ricciardiello', 1170, '2017-08-10');");
}


void Database::addSuppliersPhones(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into SuppliersPhones(Supp_ID,phone_number)"
                  "VALUES('625632797','(251) 9236825'),"
                  "('721276415','(780) 7426268'),"
                  "('839113642','(992) 7678403'),"
                  "('349686016','(878) 3950699'),"
                  "('288423058','(798) 4668310'),"
                  "('015129428','(231) 8339530'),"
                  "('631483430','(632) 7303280'),"
                  "('631483430','(904) 2061602'),"
                  "('412616694','(278) 8631288'),"
                  "('809995153','(933) 5318535'),"
                  "('124425982','(893) 6377544'),"
                  "('935903924','(808) 3284963');");
}

void Database::addOrders(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Orders(Customer_ID,Emp_ID,Order_Status,Order_Date,Total_Price)"
                  "VALUES('201954912','382224948','ordered','2017-06-27','1557'),"
                  "('401795834','079727787','Ordered','2017-12-02','1625'),"
                  "('503860353','569422207','MessageSent','2017-05-19','852'),"
                  "('503860353','499263433','Purchased','2017-12-17','1221'),"
                  "('201943842','499263433','Arrived','2017-01-22','1630'),"
                  "('302993813','499263433','Cancelled','2017-04-07','904'),"
                  "('561038427','403252037','Purchased','2018-05-14','1493'),"
                  "('561038427','823213354','Purchased','2017-11-27','1847'),"
                  "('353941513','582039536','Arrived','2018-07-11','1334'),"
                  "('491756877','582039536','Ordered','2018-06-24','2671'),"
                  "('401795834','382224948','MessageSent','2018-01-22','1256'),"
                  "('201764949','382224948','Ordered','2017-07-03','1112'),"
                  "('354095689','652444153','Ordered','2018-10-02','939');");
}


void Database::addSuppliersBooks(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into SuppliersBooks(Supp_ID,ISBN,Amount,Price)"
                  "VALUES('625632797','552547148-5','50','20'),"
                  "('625632797','623753193-9','130','50'),"
                  "('625632797','867529509-X','300','50'),"
                  "('721276415','161913965-0','240','40'),"
                  "('721276415','119639776-7','240','30'),"
                  "('721276415','095254332-X','190','15'),"
                  "('839113642','561800464-X','455','40'),"
                  "('349686016','867529509-X','95','45'),"
                  "('288423058','089179767-X','85','75'),"
                  "('288423058','250024852-6','85','40'),"
                  "('015129428','867529509-X','100','48'),"
                  "('015129428','600789272-7','140','20'),"
                  "('631483430','623753193-9','230','48'),"
                  "('631483430','161913965-0','275','45'),"
                  "('412616694','561800464-X','135','34'),"
                  "('412616694','754692835-4','460','45'),"
                  "('809995153','374822624-1','250','30'),"
                  "('809995153','867529509-X','120','52'),"
                  "('124425982','623753193-9','235','50'),"
                  "('124425982','578859010-8','350','45'),"
                  "('935903924','089179767-X','110','70'),"
                  "('935903924','374822624-1','110','30'),"
                  "('935903924','888147660-6','300','35'),"
                  "('935903924','161913965-0','210','55');");
}

void Database::addOrdersDetails(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into OrdersContent(Order_Number,Book_Name)"
                  "VALUES('1','Songs With A Hat'),"
                  "('1','Medic Of The Banished'),"
                  "('1','Armies Of Agony'),"
                  "('1','Mutants Asking Questions'),"
                  "('2','Union Of The Stockades'),"
                  "('3','Medic Of The Banished'),"
                  "('4','Songs With A Hat'),"
                  "('5','Mutants Asking Questions'),"
                  "('6','Union Of The Stockades'),"
                  "('7','Mutants Asking Questions'),"
                  "('7','Medic Of The Banished'),"
                  "('8','Careful Of Nature'),"
                  "('9','Mutants Asking Questions'),"
                  "('9','Lust Of Hell'),"
                  "('10','Medic Of The Banished'),"
                  "('11','Lust Of Hell'),"
                  "('11','Careful Of Nature'),"
                  "('12','Mutants Asking Questions');");
}

void Database::addSuppliment(){
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    stmt->execute("insert into Suppliment(Supp_ID,ISBN,supplied,Order_Date)"
                  "VALUES('625632797','552547148-5',10,'2017-06-09'),"
                  "('721276415','095254332-X',50,'2018-05-09'),"
                  "('839113642','561800464-X',10,'2018-05-02'),"
                  "('349686016','867529509-X',10,'2017-04-17'),"
                  "('288423058','250024852-6',15,'2018-08-19'),"
                  "('015129428','600789272-7',30,'2017-09-22'),"
                  "('631483430','623753193-9',10,'2017-03-22'),"
                  "('412616694','561800464-X',12,'2017-02-17'),"
                  "('809995153','374822624-1',10,'2017-09-27'),"
                  "('809995153','867529509-X',15,'2018-10-06'),"
                  "('124425982','623753193-9',10,'2018-10-31'),"
                  "('935903924','374822624-1',25,'2018-01-19');");
}

void Database:: printMenu(){
    cout << "- press 1 In order to watch the inventory" << endl
    << "- press 2 In order to watch Open Orders" << endl
    << "- press 3 In order to watch Customers List" << endl
    << "- press 4 In order to watch Suppliers List" << endl
    << "- press 5 In order to watch Orders By Date" << endl
    << "- press 6 In order to watch All the Discounted Books" << endl
    << "- press 7 In order to search for specific Book" << endl
    << "- press 8 In order to search for suppliers of specific" << endl
    << "- press 9 In order to check how many copies of a specific book were sold since a specific date" << endl
    << "- press 10 In order to check how many Books a specific Customer Purchased since a specific date" << endl
    << "- press 11 In order to check Who is the Customer who Purchased the most since a specific date" << endl
    << "- press 12 In order to watch the details of the Supplier who supplied the most books since a specific date" << endl
    << "- press 13 In order to check the Amount of Orders for specific range of dates" << endl
    << "- press 14 In order to check the Amount of Purchases for specific range of dates" << endl
    << "- press 15 In order to check what is the discount a customer got since a specific date" << endl
    << "- press 16 In order to check Store Incomes for specific quarter in a specific year" << endl
    << "- press 17 In order to check The Amount of new Customers for specific range of dates" << endl
    << "- press 18 In order to check purchases from specific Supplier in a specific range of dates" << endl
    << "- press 19 In order to check Sales for specific employee in a specific range of dates" << endl
    << "- press 20 In order to watch top 10 Books in a specific range of dates" << endl
    << "- press 99 For Exit" << endl;
}
