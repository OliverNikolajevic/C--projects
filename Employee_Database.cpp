/*
This code defines two classes, Employee and Database, which are used to manage a database of employees.
The Employee class represents an individual employee, with a first name, last name, company name, and position.
The Database class stores a collection of Employee objects and provides methods to add, search,
update, and delete employees, as well as retrieve all employees, search by position, and search by company.
The program then prompts the user to enter a choice from a menu, and performs the corresponding action based on the user's choice. The menu options are:
Add employee - prompts the user to enter the details of a new employee and adds them to the database
Search employee - prompts the user to enter a first and last name, and displays a list of matching employees
Update employee position - prompts the user to enter the details of an existing employee and a new position, and updates the employee's position in the database
Delete employee - prompts the user to enter the details of an existing employee, and removes the employee from the database
View all employees - displays a list of all employees in the database
Search employee by position - prompts the user to enter a position, and displays a list of all employees in that position
Search by company - prompts the user to enter a company name, and displays a list of all employees in that company
Exit - exits the program.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
class Employee {
private:
     string m_first_name;
     string m_last_name;
     string m_company_name;
     string m_position;
public:
    Employee(const  string& first_name, const  string& last_name,
        const  string& company_name, const  string& position)
        : m_first_name(first_name), m_last_name(last_name),
        m_company_name(company_name), m_position(position) {}

    const  string& first_name() const { return m_first_name; }
    const  string& last_name() const { return m_last_name; }
    const  string& company_name() const { return m_company_name; }
    const  string& position() const { return m_position; }
    void set_position(const  string& position) {
        m_position = position;
    }

};

class Database {
private:
    bool employee_exists(const  string& first_name, const  string& last_name,
        const  string& company_name) const {
        return any_of(m_employees.begin(), m_employees.end(), [&](const Employee& employee) {
            return (employee.first_name() == first_name) && (employee.last_name() == last_name) && (employee.company_name() == company_name); // missing semicolon
            });
    }

     vector<Employee> m_employees;
public:
    void add_employee(const  string& first_name, const  string& last_name,
        const  string& company_name, const  string& position) {
        if (employee_exists(first_name, last_name, company_name)) {
            throw  invalid_argument("Employee already exists in this company");
        }
        m_employees.emplace_back(first_name, last_name, company_name, position);
    }

     vector<Employee> search_employee(const  string& first_name, const  string& last_name) const {
         vector<Employee> result;
         copy_if(m_employees.begin(), m_employees.end(),  back_inserter(result),
            [&](const Employee& employee) {
                return (employee.first_name() == first_name) && (employee.last_name() == last_name);
            });
        return result;
    }

    void update_employee_position(const  string& first_name, const  string& last_name,
        const  string& company_name, const  string& new_position) {
        auto it =  find_if(m_employees.begin(), m_employees.end(),
            [&](const Employee& employee) {
                return (employee.first_name() == first_name) &&
                    (employee.last_name() == last_name) &&
                    (employee.company_name() == company_name);
            });
        if (it != m_employees.end()) {
            it->set_position(new_position);
        }
        else {
            throw  invalid_argument("Employee not found in this company");
        }
    }


    void delete_employee(const  string& first_name, const  string& last_name, const  string& company_name) {
        m_employees.erase( remove_if(m_employees.begin(), m_employees.end(),
            [&](const Employee& employee) {
                return (employee.first_name() == first_name) &&
                    (employee.last_name() == last_name) &&
                    (employee.company_name() == company_name);
            }),
            m_employees.end());
    }
     vector<Employee> get_all_employees() const {
        return m_employees;
    }
     vector<Employee> search_employee_by_position(const  string& position) const {
         vector<Employee> result;
         copy_if(m_employees.begin(), m_employees.end(),  back_inserter(result),
            [&](const Employee& employee) {
                return employee.position() == position;
            });
        return result;
    }
     vector<Employee> search_employee_by_company(const  string& company_name) const {
         vector<Employee> result;
         copy_if(m_employees.begin(), m_employees.end(),  back_inserter(result),
            [&](const Employee& employee) {
                return employee.company_name() == company_name;
            });
        return result;
    }

};

int main() {
    system("color 2");
    cout << "\t\t\t\t\t\tThe game was developed by Oliver Nikolajevic" << endl;;
    Database db;

    while (true) {
         cout << "1. Add employee" <<  endl;
         cout << "2. Search employee" <<  endl;
         cout << "3. Update employee position" <<  endl;
         cout << "4. Delete employee" <<  endl;
         cout << "5. View all employees" <<  endl;
         cout << "6. Search employee by position" <<  endl;
         cout << "7. Search by company" <<  endl;
         cout << "8. Exit" <<  endl;
         cout << "Enter your choice: ";

        int choice;
         cin >> choice;

        switch (choice) {
        case 1: {
             string first_name, last_name, company_name, position;
             cout << "Enter first name: ";
             cin >> first_name;
             cout << "Enter last name: ";
             cin >> last_name;
             cout << "Enter company name: ";
             cin >> company_name;
             cout << "Enter position: ";
             cin >> position;

            try {
                db.add_employee(first_name, last_name, company_name, position);
                 cout << "Employee added successfully." <<  endl;
            }
            catch (const  invalid_argument& e) {
                 cout << "Error: " << e.what() <<  endl;
            }
            break;
        }
        case 2: {
             string first_name, last_name;
             cout << "Enter first name: ";
             cin >> first_name;
             cout << "Enter last name: ";
             cin >> last_name;

             vector<Employee> employees = db.search_employee(first_name, last_name);
            if (employees.empty()) {
                 cout << "No matching employees found." <<  endl;
            }
            else {
                 cout << "Matching employees:" <<  endl;
                for (const auto& employee : employees) {
                     cout << "- " << employee.first_name() << " " << employee.last_name() << ", "
                        << employee.company_name() << ", " << employee.position() <<  endl;
                }
            }
            break;
        }
        case 3: {
             string first_name, last_name, company_name, new_position;
             cout << "Enter first name: ";
             cin >> first_name;
             cout << "Enter last name: ";
             cin >> last_name;
             cout << "Enter company name: ";
             cin >> company_name;
             cout << "Enter new position: ";
             cin >> new_position;

            try {
                db.update_employee_position(first_name, last_name, company_name, new_position);
                 cout << "Employee position updated successfully." <<  endl;
            }
            catch (const  invalid_argument& e) {
                 cout << "Error: " << e.what() <<  endl;
            }
            break;
        }
        case 4: {
             string first_name, last_name, company_name;
             cout << "Enter first name: ";
             cin >> first_name;
             cout << "Enter last name: ";
             cin >> last_name;
             cout << "Enter company name: ";
             cin >> company_name;

            db.delete_employee(first_name, last_name, company_name);
            db.delete_employee(first_name, last_name, company_name);
             cout << "Employee deleted successfully." <<  endl;
            break;
        }
        case 5: {
             vector<Employee> employees = db.get_all_employees();
             cout << "All employees:" <<  endl;
            for (const auto& employee : employees) {
                 cout << "- " << employee.first_name() << " " << employee.last_name() << ", "
                    << employee.company_name() << ", " << employee.position() <<  endl;
            }
            break;
        }
        case 6: {
             string position;
             cout << "Enter position: ";
            cin >> position;
             vector<Employee> developers = db.search_employee_by_position(position);

            // Print the names of the developers
             cout << "The following employees are developers:" <<  endl;
            for (const Employee& employee : developers) {
                 cout << "- " << employee.first_name() << " " << employee.last_name() << ", "
                    << employee.company_name() << ", " << employee.position() <<  endl;
            }
            break;
        }
        case 7: {
             string company_name;
             cout << "Enter company name: ";
             cin >> company_name;
             vector<Employee> employees = db.search_employee_by_company(company_name);

            // print out the results
             cout << "Employees who work at " << company_name << ":" <<  endl;
            for (const auto& employee : employees) {
                 cout << employee.first_name() << " " << employee.last_name() << " - " << employee.position() <<  endl;
            }

            break;
        }
        case 8: {
            return 0;
        }
        default: {
             cout << "Invalid choice. Please enter a number from 1 to 5." <<  endl;
            break;
        }
        }
    }
    //The game was developed by Oliver Nikolajevic
}

