#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
class UserManagement
{
private:
	unordered_map<string, string> users;
public:
	UserManagement();
	bool addUser(const std::string& username, const std::string& password);
	string getPassword(const std::string& username);
};

