/*
C++ code is an implementation of a File Processor which performs various operations like creating, reading, modifying, and deleting files.
Class Person which is a basic structure to hold personal information. The program also creates several classes for exceptions, FileException, 
and its derived class FileNotFoundException.
It then creates a base abstract class FileOperation which has a pure virtual function execute(). This class is inherited by
classes like CreateFile, ReadFile, ModifyFile, and DeleteFile which perform the specific file operations based on the user's choice.
The FileProcessor class is the driver program which runs the program in a loop and allows the user to choose between different 
file operations. The program takes the user's input and performs the selected operation by calling the respective function of the inherited classes.
The createFile() function of the FileProcessor class takes input from the user for creating a new Person object and adds it to the vector m_people.
It then creates a CreateFile object and passes m_people to its constructor. The execute() function of the CreateFile class is then called, 
which creates a file with the Person object's data.
The readFile() function of the FileProcessor class takes input from the user for the file name and creates a ReadFile object. 
The execute() function of the ReadFile class is then called, which reads the contents of the specified file.
The modifyFile() function of the FileProcessor class takes input from the user for the file name, key, and value. 
It then creates a ModifyFile object and passes the file name, key, and value to its constructor. 
The execute() function of the ModifyFile class is then called, which modifies the specified file's contents.
The deleteFile() function of the FileProcessor class takes input from the user for the file name and creates 
a DeleteFile object. The execute() function of the DeleteFile class is then called, which deletes the specified file.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class FileException : public exception {
public:
    virtual const char* what() const throw() {
        return "File operation failed";
    }
};

class FileNotFoundException : public FileException {
public:
    virtual const char* what() const throw() {
        return "File not found";
    }
};

class Person {
private:
    string m_name;
    string m_lastName;
    string m_birthday;
    string m_residence;
    string m_address;
public:
    Person() {}

    void setName(string name) { m_name = name; }
    string getName() const { return m_name; }

    void setLastName(string lastName) { m_lastName = lastName; }
    string getLastName() const { return m_lastName; }

    void setBirthday(string birthday) { m_birthday = birthday; }
    string getBirthday() const { return m_birthday; }

    void setResidence(string residence) { m_residence = residence; }
    string getResidence() const { return m_residence; }

    void setAddress(string address) { m_address = address; }
    string getAddress() const { return m_address; }


};

class FileOperation {
public:
    virtual void execute() = 0;
    virtual ~FileOperation() {}
};

class CreateFile : public FileOperation {
private:
    vector<Person> m_people;
public:
    CreateFile(vector<Person>& people) : m_people(people) {}

    void execute() {
        for (auto& person : m_people) {
            string fileName = person.getName() + "_" + person.getLastName() + ".txt";
            ofstream file(fileName);
            if (!file.is_open()) {
                throw FileException();
            }
            file << "Name: " << person.getName() << endl;
            file << "Last name: " << person.getLastName() << endl;
            file << "Birthday: " << person.getBirthday() << endl;
            file << "Residence: " << person.getResidence() << endl;
            file << "Address: " << person.getAddress() << endl;
            file.close();
        }
    }


};

class ReadFile : public FileOperation {
private:
    string m_fileName;
public:
    ReadFile(string fileName) : m_fileName(fileName) {}

    void execute() {
        ifstream file(m_fileName);
        if (!file.is_open()) {
            throw FileNotFoundException();
        }
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }


};

class ModifyFile : public FileOperation {
private:
    string m_fileName;
    string m_key;
    string m_value;
public:
    ModifyFile(string fileName, string key, string value) : m_fileName(fileName), m_key(key), m_value(value) {}

    void execute() {
        ifstream file(m_fileName);
        if (!file.is_open()) {
            throw FileNotFoundException();
        }
        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        bool foundKey = false;
        for (auto& line : lines) {
            if (line.substr(0, m_key.length()) == m_key) {
                line = m_key + ": " + m_value;
                foundKey = true;
                break;
            }
        }
        if (!foundKey) {
            lines.push_back(m_key + ": " + m_value);
        }

        ofstream outFile(m_fileName);
        if (!outFile.is_open()) {
            throw FileException();
        }
        for (auto& line : lines) {
            outFile << line << endl;
        }
        outFile.close();
    }

};
class DeleteFile : public FileOperation {
public:
    DeleteFile(string fileName) : m_fileName(fileName) {}
    void execute() {
        if (remove(m_fileName.c_str()) != 0) {
            throw FileException();
        }
    }

private:
    string m_fileName;
};

class FileProcessor {
private:
    vector<Person> m_people;
    Person person;
public:
    FileProcessor() {}
    void run() {
        while (true) {
            cout << "Choose an option:" << endl;
            cout << "1. Create file" << endl;
            cout << "2. Read file" << endl;
            cout << "3. Modify file" << endl;
            cout << "4. Delete file" << endl;
            cout << "5. Exit" << endl;

            int option;
            cin >> option;
            cin.ignore(); 

            switch (option) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                modifyFile();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                return;
            default:
                cout << "Invalid option" << endl;
                break;
            }
        }
    }
    //The code was developed by Oliver Nikolajevic
    void createFile() {
        Person person;
        cout << "Enter name: ";
        string Name, LastName, Birthday, Residence, Address;
        getline(cin, Name);
        person.setName(Name);
        cout << "Enter last name: ";
        getline(cin, LastName);
        person.setLastName(LastName);
        cout << "Enter birthday: ";
        getline(cin, Birthday);
     person.setBirthday(Birthday);
     cout << "Enter residence: ";
            getline(cin, Residence);
         person.setResidence(Residence);
        cout << "Enter address: ";
        getline(cin, Address);
    person.setAddress(Address);
        m_people.push_back(person);

        try {
            CreateFile createFileOp(m_people);
            createFileOp.execute();
            cout << "File(s) created successfully" << endl;
        }
        catch (FileException& ex) {
            cout << "Failed to create file(s): " << ex.what() << endl;
        }
    }

    void readFile() {
        cout << "Enter file name: ";
        string fileName;
        getline(cin, fileName);

        try {
            ReadFile readFileOp(fileName);
            readFileOp.execute();
        }
        catch (FileException& ex) {
            cout << "Failed to read file: " << ex.what() << endl;
        }
    }

    void modifyFile() {
        cout << "Enter file name: ";
        string fileName;
        getline(cin, fileName);

        cout << "Enter key to modify: ";
        string key;
        getline(cin, key);

        cout << "Enter new value: ";
        string value;
        getline(cin, value);
       
        try {
            ModifyFile modifyFileOp(fileName, key, value);
            modifyFileOp.execute();
            cout << "File modified successfully" << endl;
        }
        catch (FileException& ex) {
            cout << "Failed to modify file: " << ex.what() << endl;
        }
    }

    void deleteFile() {
        cout << "Enter file name: ";
        string fileName;
        getline(cin, fileName);

        try {
            DeleteFile deleteFileOp(fileName);
            deleteFileOp.execute();
            cout << "File deleted successfully" << endl;
        }
        catch (FileException& ex) {
            cout << "Failed to delete file: " << ex.what() << endl;
        }
    }

};

int main() {
    system("color 2");
    cout << "\t\t\t\t\t\tThe code was developed by Oliver Nikolajevic" << endl;;
    FileProcessor processor;
    processor.run();
    return 0;
}

