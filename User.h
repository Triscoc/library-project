#pragma once
#include <string>
#include <vector>
using namespace std;

enum class UserAuthority {
	Student,
	Admin
};

class User
{
private:
	string firstName;
	string lastName;
	string userID;
	string password;
	UserAuthority authority;
public:
	User();
	User(const string& firstName, const string& lastName, const string& userID, const string& password, const UserAuthority& authority);

	string getUserID() const;
	string getPassword() const;
	void setUserID(string);
	void setPassword(string);

	static vector<User> readFile();
	static bool authenticate(const string& id, const string& pass, const vector<User>& users);
};

