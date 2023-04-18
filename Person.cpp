/*This program defines two classes, Person and Database, which are used to store and manipulate 
information about people and their calorie needs.

The Person class has private member variables for a person's name, last name, weight, 
and height. It also has a constructor that can initialize these variables, as well as a
default constructor and a setDetails() method that prompts the user to enter information 
about a person's name, last name, weight, and height.

The Person class also has a calculateCalories() method that takes an activity level as 
a parameter and calculates the number of calories needed per day to lose weight, based 
on the person's weight, height, and basal metabolic rate (BMR). It uses the Harris-Benedict
equation to calculate the BMR, which takes into account a person's weight, height, age, and gender.
The displayCalories() method takes an activity level as a parameter and displays the number of 
calories needed to lose weight for a particular person.

The Database class uses a std::map to store instances of the Person class, with the key 
being the person's name and last name. It has methods to add a person, remove a person,
update a person's details, display all people, and display calories for a specific person.

The main() function presents a menu of options for the user to choose from, and calls the
appropriate methods of the Database class based on the user's input.

Overall, this program provides a simple way to store and manage information about 
people's calorie needs, and could be useful for individuals or professionals in the 
health and fitness industry. However, it could benefit from additional error checking 
and input validation to improve its robustness and reliability.
*/
#include <iostream>
#include <string>
#include <map>
using namespace std;
class Person {
private:
    string name;
    string lastName;
    double weight;
    double height;

public:
    Person() {}

    Person(string n,string ln, double w, double h) : name(n), lastName(ln), weight(w), height(h) {}

    void setDetails() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter last name: ";
        getline(cin, lastName);
        cout << "Enter weight (in kg): ";
        cin >> weight;
        cout << "Enter height (in cm): ";
        cin >> height;
    }

    double calculateCalories(double activityLevel) {
        double bmi = weight / ((height / 100) * (height / 100)); // calculate Body Mass Index
        double bmr = 10 * weight + 6.25 * height - 5 * 25 + 5; // calculate Basal Metabolic Rate
        double caloriesNeeded = bmr * activityLevel; // multiply BMR by activity level
        double caloriesToLose = (caloriesNeeded - 500) - caloriesNeeded * 0.2; // subtract 500 calories to lose weight and take 20% deficit into account
        return caloriesToLose;
    }

    void displayCalories(double activityLevel) {
        double caloriesToLose = calculateCalories(activityLevel);
        cout << "Calories needed to lose weight: " << caloriesToLose << " kcal/day" << endl;
    }

    string getName() {
        return name;
    }

    string getLastName() {
        return lastName;
    }

    double getWeight() {
        return weight;
    }

    double getHeight() {
        return height;
    }
};

class Database {
private:
    map<string, Person> db;

public:
    void addPerson(Person p) {
        db.insert(make_pair(p.getName() + " " + p.getLastName(), p));
    }

    void removePerson(string name,string lastName) {
        string fullName = name + " " + lastName;
        db.erase(fullName);
    }
/*
    void updatePerson(string name, string lastName, Person p) {
        string fullName = name + " " + lastName;
        db[fullName] = p;
    }
    */
    void updatePerson() {
        string name, lastName;
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter last name: ";
        getline(cin, lastName);
        auto it = db.find(name + " " + lastName);
        if (it != db.end()) {
            Person p = it->second;
            p.setDetails();
            db[name + " " + lastName] = p;
        }
        else {
            cout << "Person not found" << endl;
        }
    }

    void displayAll() {
        for (auto it = db.begin(); it != db.end(); it++) {
           cout << "Name: " << it->second.getName() << endl;
           cout << "Last Name: " << it->second.getLastName() << endl;
           cout << "Weight: " << it->second.getWeight() << " kg" << endl;
           cout << "Height: " << it->second.getHeight() << " cm" << endl;
           cout << endl;
        }
    }

    void displayCalories( string name, string lastName, double activityLevel) {
         string fullName = name + " " + lastName;
        auto it = db.find(fullName);
        if (it == db.end()) {
            cout << "Person not found" <<  endl;
        }
        else {
             cout << "Name: " << it->second.getName() <<  endl;
             cout << "Last Name: " << it->second.getLastName() <<  endl;
             cout << "Weight: " << it->second.getWeight() << " kg" <<  endl;
             cout << "Height: " << it->second.getHeight() << " cm" <<  endl;
             cout <<  endl;
            it->second.displayCalories(activityLevel);
        }
    }
    Person* find( string name,  string lastName) {
         string fullName = name + " " + lastName;
        auto it = db.find(fullName);
        if (it == db.end()) {
            return nullptr;
        }
        else {
            return &(it->second);
        }
    }
};

int main() {
    system("color 2");
    cout << "\t\t\t\t\t\tThe game was developed by Oliver Nikolajevic" << endl;;
    Database db;
    int choice;
    do {
         cout << "1. Add person" <<  endl;
         cout << "2. Remove person" <<  endl;
         cout << "3. Update person" <<  endl;
         cout << "4. Display all persons" <<  endl;
         cout << "5. Display calories for person" <<  endl;
         cout << "6. Exit" <<  endl;
         cout << "Enter your choice: ";
         cin >> choice;
         cin.ignore(); // ignore the newline character
         cout <<  endl;
        switch (choice) {
        case 1: {
            Person p;
            p.setDetails();
            db.addPerson(p);
          
            break;
        }
        case 2: {
             string name, lastName;
             cout << "Enter name: ";
             getline( cin, name);
             cout << "Enter last name: ";
             getline( cin, lastName);
            db.removePerson(name, lastName);
            break;
        }
        
        
        case 3: {
            db.updatePerson();
            break;
        
        }
        case 4: {
            db.displayAll();
            break;
        }
        case 5: {
             string name, lastName;
             cout << "Enter name: ";
             getline( cin, name);
             cout << "Enter last name: ";
             getline( cin, lastName);
            double activityLevel;
             cout << "Enter activity level: ";
             cin >> activityLevel;
            db.displayCalories(name, lastName, activityLevel);
            break;
        }
        case 6: {
             cout << "Exiting program" <<  endl;
            break;
        }
        default: {
             cout << "Invalid choice" <<  endl;
            break;
        }
        }
         cout <<  endl;
    } while (choice != 6);
    //The game was developed by Oliver Nikolajevic
    return 0;
}
