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
    std::string m_first_name;
    std::string m_last_name;
    std::string m_company_name;
    std::string m_position;
public:
    Employee(const std::string& first_name, const std::string& last_name,
        const std::string& company_name, const std::string& position)
        : m_first_name(first_name), m_last_name(last_name),
        m_company_name(company_name), m_position(position) {}

    const std::string& first_name() const { return m_first_name; }
    const std::string& last_name() const { return m_last_name; }
    const std::string& company_name() const { return m_company_name; }
    const std::string& position() const { return m_position; }
    void set_position(const std::string& position) {
        m_position = position;
    }

};

class Database {
private:
    bool employee_exists(const std::string& first_name, const std::string& last_name,
        const std::string& company_name) const {
        return any_of(m_employees.begin(), m_employees.end(), [&](const Employee& employee) {
            return (employee.first_name() == first_name) && (employee.last_name() == last_name) && (employee.company_name() == company_name); // missing semicolon
            });
    }

    std::vector<Employee> m_employees;
public:
    void add_employee(const std::string& first_name, const std::string& last_name,
        const std::string& company_name, const std::string& position) {
        if (employee_exists(first_name, last_name, company_name)) {
            throw std::invalid_argument("Employee already exists in this company");
        }
        m_employees.emplace_back(first_name, last_name, company_name, position);
    }

    std::vector<Employee> search_employee(const std::string& first_name, const std::string& last_name) const {
        std::vector<Employee> result;
        std::copy_if(m_employees.begin(), m_employees.end(), std::back_inserter(result),
            [&](const Employee& employee) {
                return (employee.first_name() == first_name) && (employee.last_name() == last_name);
            });
        return result;
    }

    void update_employee_position(const std::string& first_name, const std::string& last_name,
        const std::string& company_name, const std::string& new_position) {
        auto it = std::find_if(m_employees.begin(), m_employees.end(),
            [&](const Employee& employee) {
                return (employee.first_name() == first_name) &&
                    (employee.last_name() == last_name) &&
                    (employee.company_name() == company_name);
            });
        if (it != m_employees.end()) {
            it->set_position(new_position);
        }
        else {
            throw std::invalid_argument("Employee not found in this company");
        }
    }


    void delete_employee(const std::string& first_name, const std::string& last_name, const std::string& company_name) {
        m_employees.erase(std::remove_if(m_employees.begin(), m_employees.end(),
            [&](const Employee& employee) {
                return (employee.first_name() == first_name) &&
                    (employee.last_name() == last_name) &&
                    (employee.company_name() == company_name);
            }),
            m_employees.end());
    }
    std::vector<Employee> get_all_employees() const {
        return m_employees;
    }
    std::vector<Employee> search_employee_by_position(const std::string& position) const {
        std::vector<Employee> result;
        std::copy_if(m_employees.begin(), m_employees.end(), std::back_inserter(result),
            [&](const Employee& employee) {
                return employee.position() == position;
            });
        return result;
    }
    std::vector<Employee> search_employee_by_company(const std::string& company_name) const {
        std::vector<Employee> result;
        std::copy_if(m_employees.begin(), m_employees.end(), std::back_inserter(result),
            [&](const Employee& employee) {
                return employee.company_name() == company_name;
            });
        return result;
    }

};

int main() {
    system("color 2");
    cout << "\t\t\t\t\t\tThe game was developed by Oliver Nikolajevic"<< endl;;
    Database db;

    while (true) {
        std::cout << "1. Add employee" << std::endl;
        std::cout << "2. Search employee" << std::endl;
        std::cout << "3. Update employee position" << std::endl;
        std::cout << "4. Delete employee" << std::endl;
        std::cout << "5. View all employees" << std::endl;
        std::cout << "6. Search employee by position" << std::endl;
        std::cout << "7. Search by company" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string first_name, last_name, company_name, position;
            std::cout << "Enter first name: ";
            std::cin >> first_name;
            std::cout << "Enter last name: ";
            std::cin >> last_name;
            std::cout << "Enter company name: ";
            std::cin >> company_name;
            std::cout << "Enter position: ";
            std::cin >> position;

            try {
                db.add_employee(first_name, last_name, company_name, position);
                std::cout << "Employee added successfully." << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }
        case 2: {
            std::string first_name, last_name;
            std::cout << "Enter first name: ";
            std::cin >> first_name;
            std::cout << "Enter last name: ";
            std::cin >> last_name;

            std::vector<Employee> employees = db.search_employee(first_name, last_name);
            if (employees.empty()) {
                std::cout << "No matching employees found." << std::endl;
            }
            else {
                std::cout << "Matching employees:" << std::endl;
                for (const auto& employee : employees) {
                    std::cout << "- " << employee.first_name() << " " << employee.last_name() << ", "
                        << employee.company_name() << ", " << employee.position() << std::endl;
                }
            }
            break;
        }
        case 3: {
            std::string first_name, last_name, company_name, new_position;
            std::cout << "Enter first name: ";
            std::cin >> first_name;
            std::cout << "Enter last name: ";
            std::cin >> last_name;
            std::cout << "Enter company name: ";
            std::cin >> company_name;
            std::cout << "Enter new position: ";
            std::cin >> new_position;

            try {
                db.update_employee_position(first_name, last_name, company_name, new_position);
                std::cout << "Employee position updated successfully." << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }
        case 4: {
            std::string first_name, last_name, company_name;
            std::cout << "Enter first name: ";
            std::cin >> first_name;
            std::cout << "Enter last name: ";
            std::cin >> last_name;
            std::cout << "Enter company name: ";
            std::cin >> company_name;

            db.delete_employee(first_name, last_name, company_name);
                db.delete_employee(first_name, last_name, company_name);
            std::cout << "Employee deleted successfully." << std::endl;
            break;
        }
        case 5: {
            std::vector<Employee> employees = db.get_all_employees();
            std::cout << "All employees:" << std::endl;
            for (const auto& employee : employees) {
                std::cout << "- " << employee.first_name() << " " << employee.last_name() << ", "
                    << employee.company_name() << ", " << employee.position() << std::endl;
            }
            break;
        }
        case 6: {
            std::string position;
            std::cout << "Enter position: ";
            cin >> position;
            std::vector<Employee> developers = db.search_employee_by_position(position);

            // Print the names of the developers
            std::cout << "The following employees are developers:" << std::endl;
            for (const Employee& employee : developers) {
                std::cout << "- " << employee.first_name() << " " << employee.last_name() << ", "
                    << employee.company_name() << ", " << employee.position() << std::endl;
            }
            break;
        }
        case 7: {
            std::string company_name;
            std::cout << "Enter company name: ";
            std::cin >> company_name;
            std::vector<Employee> employees = db.search_employee_by_company(company_name);

            // print out the results
            std::cout << "Employees who work at " << company_name << ":" << std::endl;
            for (const auto& employee : employees) {
                std::cout << employee.first_name() << " " << employee.last_name() << " - " << employee.position() << std::endl;
            }

            break;
        }
        case 8: {
            return 0;
        }
        default: {
            std::cout << "Invalid choice. Please enter a number from 1 to 5." << std::endl;
            break;
        }
        }
    }
    //The game was developed by Oliver Nikolajevic
}

