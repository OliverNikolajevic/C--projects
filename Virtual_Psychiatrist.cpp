#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct User {
    string firstName;
    string lastName;
    int age;
    string gender;
};
void saveConversation(const User& user, const vector<string>& conversation)
{
    string filename = user.firstName + "_" + user.lastName + ".txt";

    ofstream outfile(filename);
    outfile << "Name: " << user.firstName << " " << user.lastName << "\n";
    outfile << "Gender: " << user.gender << "\n";
    outfile << "Age: " << user.age << "\n\n";
    for (const auto& line : conversation) {
        outfile << line << endl;
    }
    outfile.close();

    cout << "Conversation saved to file " << filename << endl;
}

void askQuestions(const string& fileName, const User& user)
{
    ifstream infile(fileName);
    vector<string> questions;
    string question;
    while (getline(infile, question)) {
        questions.push_back(question);
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(questions.begin(), questions.end(), g);
    vector<string> conversation;
    for (const auto& q : questions) {
        cout << q << endl;
        string answer;
        getline(cin, answer);
        conversation.push_back("Q: " + q + "\nA: " + answer + "\n");
        if (answer == "exit") {
            break;
        }
    }
    saveConversation(user, conversation);
}



int main()
{
    system("color 2");
    cout << "\t\t\t\t\t\t\tThe code was developed by Oliver Nikolajevic" << endl;;
    User user;
    cout << "Hello, I am your professional psychiatrist. To end the conversation, enter exit." << endl;
    cout << "Please enter your first name: ";
    getline(cin, user.firstName);
    cout << "Please enter your last name: ";
    getline(cin, user.lastName);
    cout << "Please enter your age: ";
    cin >> user.age;
    cout << "Please enter your gender (male/female): ";
    cin >> user.gender;
    string fileName = (user.gender == "male") ? "male_questions.txt" : "female_questions.txt";
    askQuestions(fileName, user);
    //The code was developed by Oliver Nikolajevic
    return 0;
}


