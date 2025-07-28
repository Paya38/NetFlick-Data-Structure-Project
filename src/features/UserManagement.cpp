#include "UserManagement.h"

UserManagement::UserManagement()
{
    users["admin"] = "admin";
}

bool UserManagement::addUser(const std::string& username, const std::string& password)
{
    if (username == "admin" || password == "admin") {
        cout<< "Error: 'admin' cannot be used as username or password."<<endl;
        return false;
    }

    if (users.find(username) != users.end()) {
        cout<< "Error: Username already exists."<<endl;
        return false;
    }

    users[username] = password;
    cout<< "User '" + username + "' added successfully."<<endl;
    return true;
}

string UserManagement::getPassword(const std::string& username)
{
    auto it = users.find(username);
    if (it == users.end()) {
        cout<<"Error: Username not found."<<endl;
        return"%";
    }
    return it->second;
}
