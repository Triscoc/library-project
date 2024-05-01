#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include "Variables.h"
#include <fstream>
#include <sstream>
using namespace std;

User::User()
{
	firstName = "";
	lastName = "";
	userID = "";
	password = "";
	authority = UserAuthority::Student;
}

User::User(const string& firstName, const string& lastName, const string& userID, const string& password, const UserAuthority& authority)
	: firstName(firstName), lastName(lastName), userID(userID), password(password), authority(authority)
{
	
}

string User::getUserID() const
{
	return userID;
}

string User::getPassword() const
{
	return password;
}

void User::setUserID(string ID)
{
	userID = ID;
}

void User::setPassword(string pass)
{
	password = pass;
}

vector<User> User::readFile()
{
	vector<User> users;
	ifstream file(idPass);

	if (!file.is_open()) {
		return users;
	}

	string line;
	while (getline(file, line)){
		istringstream iss(line);
		string firstName, lastName, userID, password;
		int authInt;
		if (iss >> firstName >> lastName >> userID >> password >> authInt){
			UserAuthority authority = static_cast<UserAuthority>(authInt);
			users.push_back(User(firstName, lastName, userID, password, authority));
		}
	}
	file.close();
	return users;
}

bool User::authenticate(const string& inputID, const string& inputPass, const vector<User>& users)
{
	for (const auto& user : users) {
		if (user.getUserID() == inputID && user.getPassword() == inputPass) {
			return true;
		}
	}
	return false;
}



