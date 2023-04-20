/*
Program that simulates a virtual psychiatrist in C++. The program prompts the user to enter their first name, 
last name, age, and gender, and then selects a file of questions based on the user's gender. 
The questions are asked randomly, and the user's responses are recorded in a conversation vector. 
The conversation is then saved to a file with the user's name as the filename.
The askQuestions() function opens the question file, shuffles the questions randomly, and asks the questions to the user. 
The saveConversation() function creates the file and saves the conversation to it.
Where the program will be saved, you must have two files, which are female_questions.txt and male_questions.txt. 
They contain the questions that the program will ask.

*/
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
    // Open the file and read the questions
    ifstream infile(fileName);
    vector<string> questions;
    string question;
    while (getline(infile, question)) {
        questions.push_back(question);
    }

    // Shuffle the questions randomly
    random_device rd;
    mt19937 g(rd());
    shuffle(questions.begin(), questions.end(), g);

    // Ask questions and save the conversation
    vector<string> conversation;
    bool conversationOver = false;
    for (const auto& q : questions) {
        cout << q << endl;
        string answer;
        getline(cin, answer);
        conversation.push_back("Q: " + q + "\nA: " + answer + "\n");
        if (answer == "exit") {
            conversationOver = true;
            break;
        }
    }

    // Save the conversation to a file
    saveConversation(user, conversation);

    // Display message if conversation was ended prematurely
    if (!conversationOver) {
        cout << "Conversation ended without exiting." << endl;
    }
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
//Example for male_questions.txt
/*
What brings you in today?
How long have you been feeling this way?
Have you had any recent changes in your life?
Are you feeling more irritable than usual?
Have you experienced any suicidal thoughts or tendencies?
How has your sleep been lately?
Do you feel anxious or worried about anything in particular?
Have you experienced any traumatic events recently?
Do you find it hard to concentrate or focus on tasks?
Are you feeling more sad or down than usual?
*/

//Example for female_questions.txt
/*
What brings you in today?
How long have you been feeling this way?
Have you had any recent changes in your life?
Are you feeling more irritable than usual?
Have you experienced any suicidal thoughts or tendencies?
How has your sleep been lately?
Do you feel anxious or worried about anything in particular?
Have you experienced any traumatic events recently?
Do you find it hard to concentrate or focus on tasks?
Are you feeling more sad or down than usual?
*/
