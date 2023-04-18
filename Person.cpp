#include <iostream>
#include <string>
#include <map>
using namespace std;
class Person {
private:
    std::string name;
    std::string lastName;
    double weight;
    double height;

public:
    Person() {}

    Person(std::string n, std::string ln, double w, double h) : name(n), lastName(ln), weight(w), height(h) {}

    void setDetails() {
        std::cout << "Enter name: ";
        std::getline(std::cin, name);
        std::cout << "Enter last name: ";
        std::getline(std::cin, lastName);
        std::cout << "Enter weight (in kg): ";
        std::cin >> weight;
        std::cout << "Enter height (in cm): ";
        std::cin >> height;
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
        std::cout << "Calories needed to lose weight: " << caloriesToLose << " kcal/day" << std::endl;
    }

    std::string getName() {
        return name;
    }

    std::string getLastName() {
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
    std::map<std::string, Person> db;

public:
    void addPerson(Person p) {
        db.insert(std::make_pair(p.getName() + " " + p.getLastName(), p));
    }

    void removePerson(std::string name, std::string lastName) {
        std::string fullName = name + " " + lastName;
        db.erase(fullName);
    }
/*
    void updatePerson(std::string name, std::string lastName, Person p) {
        std::string fullName = name + " " + lastName;
        db[fullName] = p;
    }
    */
    void updatePerson() {
        std::string name, lastName;
        std::cout << "Enter name: ";
        std::getline(std::cin, name);
        std::cout << "Enter last name: ";
        std::getline(std::cin, lastName);
        auto it = db.find(name + " " + lastName);
        if (it != db.end()) {
            Person p = it->second;
            p.setDetails();
            db[name + " " + lastName] = p;
        }
        else {
            std::cout << "Person not found" << std::endl;
        }
    }

    void displayAll() {
        for (auto it = db.begin(); it != db.end(); it++) {
            std::cout << "Name: " << it->second.getName() << std::endl;
            std::cout << "Last Name: " << it->second.getLastName() << std::endl;
            std::cout << "Weight: " << it->second.getWeight() << " kg" << std::endl;
            std::cout << "Height: " << it->second.getHeight() << " cm" << std::endl;
            std::cout << std::endl;
        }
    }

    void displayCalories(std::string name, std::string lastName, double activityLevel) {
        std::string fullName = name + " " + lastName;
        auto it = db.find(fullName);
        if (it == db.end()) {
            cout << "Person not found" << std::endl;
        }
        else {
            std::cout << "Name: " << it->second.getName() << std::endl;
            std::cout << "Last Name: " << it->second.getLastName() << std::endl;
            std::cout << "Weight: " << it->second.getWeight() << " kg" << std::endl;
            std::cout << "Height: " << it->second.getHeight() << " cm" << std::endl;
            std::cout << std::endl;
            it->second.displayCalories(activityLevel);
        }
    }
    Person* find(std::string name, std::string lastName) {
        std::string fullName = name + " " + lastName;
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
        std::cout << "1. Add person" << std::endl;
        std::cout << "2. Remove person" << std::endl;
        std::cout << "3. Update person" << std::endl;
        std::cout << "4. Display all persons" << std::endl;
        std::cout << "5. Display calories for person" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // ignore the newline character
        std::cout << std::endl;
        switch (choice) {
        case 1: {
            Person p;
            p.setDetails();
            db.addPerson(p);
          
            break;
        }
        case 2: {
            std::string name, lastName;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter last name: ";
            std::getline(std::cin, lastName);
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
            std::string name, lastName;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter last name: ";
            std::getline(std::cin, lastName);
            double activityLevel;
            std::cout << "Enter activity level: ";
            std::cin >> activityLevel;
            db.displayCalories(name, lastName, activityLevel);
            break;
        }
        case 6: {
            std::cout << "Exiting program" << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice" << std::endl;
            break;
        }
        }
        std::cout << std::endl;
    } while (choice != 6);
    //The game was developed by Oliver Nikolajevic
    return 0;
}
