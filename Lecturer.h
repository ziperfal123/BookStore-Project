#ifndef _LECTURER_H
#define _LECTURER_H

#include <iostream>
#include "Database.h"
#include <boost/date_time/posix_time/posix_time.hpp>

#define CON Database &db = Database::getInstance();Connection *con = db.getConnection();

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class Lecturer
{
	string id;
	string firstname;
	string lastname;
	string city;
	string street;
	unsigned int street_num;
	date birthdate;


public:
	// CRUD - CREATE UPDATE DESTROY

	static int count() {
		CON;
		int res = 0;
		if (con) {
			Statement *stmt = con->createStatement();
			ResultSet *rset = stmt->executeQuery("SELECT count(*) as cnt from Lecturers");
			rset->first();
			res = rset->getInt("cnt");
			delete con;
			delete rset;
			delete stmt;
		}

		return res;


	}

	static Lecturer * create (
		string id,
		string firstname,
		string lastname,
		string city,
		string street,
		unsigned int street_num,
		date birthdate
	) {
		Database &db = Database::getInstance();
		Connection *con = db.getConnection();
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("INSERT INTO Lecturers (id, firstname, lastname, city, street, street_num, birth_date) VALUES(?,?,?,?,?,?,?)");
			pstmt->setString(1, id);
			pstmt->setString(2, firstname);
			pstmt->setString(3, lastname);
			pstmt->setString(4, city);
			pstmt->setString(5, street);
			pstmt->setUInt(6, street_num);
			pstmt->setString(7, to_iso_extended_string(birthdate));

			int affected = pstmt->executeUpdate();
			if (affected == 1) {
				delete con;
				delete pstmt;
				return new Lecturer(id, firstname, lastname, city, street, street_num, to_iso_extended_string(birthdate));
			}

			delete con;
			delete pstmt;
		}

		return 0;
	}

	static bool destroy(string id) {
		if (id != 0 && id.length() == 0) return false;
		bool res = false;
		Database &db = Database::getInstance();
		Connection *con = db.getConnection();
		if (con) {
			PreparedStatement *pstmt = con->prepareStatement("DELETE FROM Lecturers WHERE id=?");
			pstmt->setString(1, id);
			res = pstmt->execute();
			delete con;
			delete pstmt;
		}
		return res;
	}

	static Lecturer * getById(string id) {
		Database &db = Database::getInstance();
		Connection *con = db.getConnection();
		PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Lecturers WHERE id = ?");
		pstmt->setString(1, id);
		ResultSet *rset = pstmt->executeQuery();
		if (rset->rowsCount() == 1) {
			rset->first();
			Lecturer *result = new Lecturer(
				rset->getString("id"), 
				rset->getString("firstname"), 
				rset->getString("lastname"), 
				rset->getString("city"), 
				rset->getString("street"), 
				rset->getInt("street_num"), 
				rset->getString("birth_date"));

			delete pstmt;
			delete rset;
			delete con;
			cout 
				<< result->firstname << " " << result->lastname << endl
				<< result->birthdate << endl;
			return result;
		}
	
		delete pstmt;
		delete rset;
		delete con;

		return 0;
	}

	bool update() {
		Database &db = Database::getInstance();
		Connection *con = db.getConnection();
		bool res = false;
		if (!con) return 0;
		
		PreparedStatement *pstmt = con->prepareStatement("UPDATE Lecturers SET firstname=?, lastname=?, city=?, street=?, street_num=?, birth_date=? WHERE id=?");
		pstmt->setString(1, this->firstname);
		pstmt->setString(2, this->lastname);
		pstmt->setString(3, this->city);
		pstmt->setString(4, this->street);
		pstmt->setUInt(5, this->street_num);
		pstmt->setString(6, to_iso_extended_string(this->birthdate));
		pstmt->setString(7, this->id);
		res = pstmt->executeUpdate() == 1;
		delete pstmt;

		return res;
	}

	Lecturer(string id, string firstname, string lastname, string city, string street, unsigned int street_num, string birthdate);
	~Lecturer();
};

#endif
