#include <iostream>
#include <stdlib.h>
#include <vector>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <bits/stdc++.h>

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

using namespace std;

std::vector<string> fetchArray(string);

unsigned hash_str(const char* s)
{
   unsigned h = FIRSTH;
   while (*s)
   {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}

class Database
{

private :

	string user = "admin";
	string password = "passwd=passwd";
	string database = "admon_rough";

public: 
	
	sql::Connection* connectDB(void)
	{
		sql::Connection *con = NULL;
		try
		{
			sql::Driver *driver;
			sql::Statement *stmt;
			sql::ResultSet *res;
			driver = get_driver_instance();
			con = driver->connect("tcp://127.0.0.1:3306", user, password);
			con->setSchema(database);
		}
		catch (sql::SQLException &e)
		{
		}
		return con;
	}
};

std::vector<string> fetchArray(string getString)
{
		vector <string> keypairs; 
      
	    stringstream temp1(getString);

	    string intermediate; 
	      
	    while(getline(temp1, intermediate, '&')) 
	    {
	    	stringstream temp2(intermediate);
	    	string seperator;
	    	while(getline(temp2, seperator, '=')) 
	    	{
	        	keypairs.push_back(seperator);
	    	}
	    }   
		return keypairs;
}

int findIndex(std::vector<string> v, string keyword)
{
  for (int i = 0; i < v.size(); i++)
  {
    if(v[i] == keyword)
    { 
      return i;
    }
  }
  return  -1;
}

bool replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int main()
{
try
{
	vector <string> getString = fetchArray((string)getenv("QUERY_STRING"));

	if(getString.empty())
	{
		cout << "Location: http://localhost/login.cgi\n\n";
		return 0;
	}
	int index = findIndex(getString, "action");
	if(getString[index+1] == "login")
	{
		int len;
		char* lenstr = getenv("CONTENT_LENGTH");
		string temp = "";

		if(lenstr != NULL && (len = atoi(lenstr)) != 0)
		{
			char *post_data = new char[len];

			fgets(post_data, len + 1, stdin);

		    for (int i = 0; i < len; i++)
		    { 
		        temp = temp + post_data[i]; 
		    }
		    std::vector<string> postString = fetchArray(temp);
			
		    string email = postString[1];
		    string password = postString[3];
			const char * c = password.c_str();
			password = to_string(hash_str(c));

			replace(email, "@", "%40");

			Database db;
			sql::Connection *con = db.connectDB();
			sql::PreparedStatement *pstmt;
			sql::ResultSet *res;
			pstmt = con->prepareStatement("SELECT * FROM user WHERE email = ? LIMIT 1");
			pstmt->setString(1, email);

			res = pstmt->executeQuery();
			if(!res->next())
			{
				cout << "Location: http://localhost/login.cgi?message=No user with that email address\n\n";
				return 0;
			}	
			if(res->getString("password") == password)
			{
				cout << "Content-Type: text/html\n";
				cout << "Set-Cookie:user=" << email << ";\n";
				cout << "Location: http://localhost/home.cgi?user=" << res->getString("name") << "\n\n";
			}
			else
			{
				cout << "Location: http://localhost/login.cgi?message=You entered wrong password\n\n" << endl;
			}
			delete res;
			delete pstmt;
			delete con;
			return 0;
		}
	}
	else if(getString[index+1] == "registration")
	{
		int len;
		char* lenstr = getenv("CONTENT_LENGTH");
		string temp = "";

		if(lenstr != NULL && (len = atoi(lenstr)) != 0)
		{
			char *post_data = new char[len];

			fgets(post_data, len + 1, stdin);

		    for (int i = 0; i < len; i++)
		    { 
		        temp = temp + post_data[i]; 
		    }
		    std::vector<string> postString = fetchArray(temp);

		    string name = (string)postString[1] + " " + postString[3];
		    string email = (string)postString[5];
		    string password = (string)postString[7];
		    const char * c = password.c_str();
			password = to_string(hash_str(c));

			Database db;
			sql::Connection *con = db.connectDB();
			sql::PreparedStatement *pstmt;
			sql::ResultSet *res;

			pstmt = con->prepareStatement("SELECT * FROM user WHERE email = ? LIMIT 1");
			pstmt->setString(1, email);

			res = pstmt->executeQuery();
			if(res->next())
			{
				cout << "Location: http://localhost/signup.cgi?message=There is already an user with that email\n\n";
				return 0;
			}
			pstmt = con->prepareStatement("INSERT INTO `user` (`email`, `name`, `password`) VALUES (?,?,?)");
			pstmt->setString(1, email);
			pstmt->setString(2, name);
			pstmt->setString(3, password);
			pstmt->execute();
			delete pstmt;
			delete con;
			cout << "Content-Type: text/html\n";
			cout << "Set-Cookie:user=" << email << ";\n";
			cout << "Location: http://localhost/home.cgi?user=" << name << "\n\n";
		}
	}
	else if(getString[index+1] == "cookie-resolve")
	{
		std::vector<string> v = fetchArray(getenv("HTTP_COOKIE"));
   			
   		int index2 = findIndex(getString, "user");

   		string email = getString[index2+1];

   		Database db;
		sql::Connection *con = db.connectDB();
		sql::PreparedStatement *pstmt;
		sql::ResultSet *res;
		pstmt = con->prepareStatement("SELECT * FROM user WHERE email = ? LIMIT 1");
		pstmt->setString(1, email);

		res = pstmt->executeQuery();
		if(!res->next())
		{
			cout << "Content-Type: text/html\n";
			cout << "Set-Cookie:user=" << email << ";expires=Thu, 01 Jan 1970 00:00:00 GMT\n";
			cout << "Location: http://localhost/login.cgi\n\n";
			return 0;
		}	
		else
		{
			cout << "Location: http://localhost/home.cgi?user=" << res->getString("name") << "\n\n";
		}
		delete res;
		delete pstmt;
		delete con;
		return 0;
	}
	else
	{	
		cout << "Location: http://localhost/login.cgi\n\n";
	}
	return 0;
}

catch(...)
{
	cout << "Location: http://localhost/login.cgi\n\n";
	return 0;
}
}
