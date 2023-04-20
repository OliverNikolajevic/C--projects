/*
A program that prompts the user to enter information for multiple users, writes the 
user information to individual text files, and then sorts and prints the users based on their age. 
It saves each text as the user's first and last name.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct User {
     string firstName;
     string lastName;
    int age;
};

bool compareByAge(const User& user1, const User& user2) {
    return user1.age < user2.age;
}

int main() {
	system("color 2");
    cout << "\t\t\t\t\t\tThe game was developed by Oliver Nikolajevic" << endl;;
     vector<User> users;
    while (true) {
        User user;
         cout << "Enter first name for quit input '.':): ";
        if (!( cin >> user.firstName) || user.firstName == ".") {
            break; 
        }
         cout << "Enter last name: ";
         cin >> user.lastName;
         cout << "Enter age: ";
         cin >> user.age;

    string fileName = user.firstName + "_" + user.lastName + ".txt";
 ofstream outputFile(fileName.c_str());
        if (outputFile.is_open()) {
            outputFile << "First Name: " << user.firstName <<  endl;
            outputFile << "Last Name: " << user.lastName <<  endl;
            outputFile << "Age: " << user.age <<  endl;
            outputFile.close();
            users.push_back(user); 
        }
        else {
             cout << "Failed to create file for user " << user.firstName << " " << user.lastName <<  endl;
        }
    }

     sort(users.begin(), users.end(), compareByAge);

     cout << "Users sorted by age (youngest to oldest):" <<  endl;
   for (int i = 0; i < users.size(); ++i) {
 const User& user = users[i];
         cout << "Name: " << users[i].firstName << " " << users[i].lastName << ", Age: " << users[i].age <<  endl;
    }
//The game was developed by Oliver Nikolajevic
    return 0;
}
