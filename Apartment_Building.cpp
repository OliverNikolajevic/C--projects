/*
C++ program that simulates an apartment building. The program creates a class Stan that represents an apartment, 
and a class StanbenaZgrada that represents the apartment building. The Stan class has private data members for the 
apartment number, the room number, the floor number, whether the apartment is equipped, and the area in square meters. 
The StanbenaZgrada class has private data members for the building name, the address, the number of apartments 
in the building, and a vector of Stan objects that represents the apartments in the building.
The program takes input from the user for the building name, address, and number of apartments in the building. 
Then, for each apartment, the program takes input from the user for the apartment number, room number, floor number,
whether the apartment is equipped, and the area in square meters. The program then creates a Stan object for each apartment
and adds it to the StanbenaZgrada object. Program writes the information about the building and the apartments to 
a text file with the building name as the file name.
The program also has methods for calculating the price of each apartment based on its size, floor, 
and equipment, and for printing the information about the building and apartments to the console and to the text file.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Stan {
private:
    int brojNaStan;
    int brojNaSobi;
    int kat;
    bool opremen;
    double povrsina;
public:
    Stan(int brojNaStan, int brojNaSobi, int kat, bool opremen, double povrsina) {
        this->brojNaStan = brojNaStan;
        this->brojNaSobi = brojNaSobi;
        this->kat = kat;
        this->opremen = opremen;
        this->povrsina = povrsina;
    }

    double cena() {
        double cena = povrsina * 1400;

        if (kat == 1) {
            cena += cena * 0.2;
        }
        else if (kat == 2) {
            cena += cena * 0.1;
        }
        else if (kat == 3) {
            cena += cena * 0.05;
        }

        if (opremen) {
            cena += 5000;
        }

        return cena;
    }

    void pecati() {
        cout << brojNaStan << " - " << brojNaSobi << " - " << povrsina << "m2 - ";
        if (opremen) {
            cout << "equipped - ";
        }
        else {
            cout << "not equipped - ";
        }
        cout << cena() << " eur" << endl;
    }
    int getBrojNaStan() {
        return brojNaStan;
    }
    int getBrojNaSobi() {
        return brojNaSobi;
    }
    int getKat() {
        return kat;
    }
    bool isOpremen() {
        return opremen;
    }
    double getPovrsina() {
        return povrsina;
    }
};

class StanbenaZgrada {
private:
    string imeNaZgrada;
    string adresa;
    vector<Stan> stanovi;
    int brojNaStanovi;
public:
    StanbenaZgrada(string imeNaZgrada, string adresa, int brojNaStanovi) {
        this->imeNaZgrada = imeNaZgrada;
        this->adresa = adresa;
        this->brojNaStanovi = brojNaStanovi;
    }

    void dodadiStan(Stan stan) {
        if (stanovi.size() < brojNaStanovi) {
            stanovi.push_back(stan);
        }
        else {
            cout << "No more apartments can be added!" << endl;
        }
    }

    void pecati() {
        cout << "Building: " << imeNaZgrada << endl;
        cout << "Address: " << adresa << endl;

        int i = 1;
        for (auto stan : stanovi) {
            cout << i++ << ". ";
            stan.pecati();
        }
    }
    vector<Stan>& getStanovi() {
        return stanovi;
    }
    string getImeNaZgrada() {
        return imeNaZgrada;
    }
    string getAdresa() {
        return adresa;
    }
};

int main() {
    system("color 2");
    cout << "\t\t\t\t\t\tThe code was developed by Oliver Nikolajevic" << endl;;
    string imeNaZgrada, adresa;
    int brojNaStanovi;

    cout << "Enter building name: ";
    getline(cin, imeNaZgrada);

    cout << "Enter building address: ";
    getline(cin, adresa);

    cout << "Enter the number of apartments in the building: ";
    cin >> brojNaStanovi;

    StanbenaZgrada zgrada(imeNaZgrada, adresa, brojNaStanovi);

    for (int i = 1; i <= brojNaStanovi; i++) {
        int brojNaStan, brojNaSobi, kat;
        bool opremen;
        double povrsina;

        cout << "Apartment number: ";
        cin >> brojNaStan;

        cout << "Number of rooms: ";
        cin >> brojNaSobi;

        cout << "Floor: ";
        cin >> kat;

        cout << "Is equipped (1 for yes, 0 for no): ";
        cin >> opremen;

        cout << "Area in m2: ";
        cin >> povrsina;

        Stan stan(brojNaStan, brojNaSobi, kat, opremen, povrsina);
        zgrada.dodadiStan(stan);
    }

    string filename = imeNaZgrada + ".txt"; // add building name to filename
    ofstream outFile(filename); // create file with building name as filename

    if (outFile.is_open()) {
        outFile <<"Building name: "<< imeNaZgrada << endl;
        outFile <<"Building address: "<< adresa << endl;
        outFile <<"Number of apartments: "<< brojNaStanovi << endl;

        for (auto stan : zgrada.getStanovi()) {
            outFile <<"Apartment number: "<<stan.getBrojNaStan() << endl;
            outFile <<"Number of rooms: "<< stan.getBrojNaSobi() << endl;
            outFile <<"Floor: "<< stan.getKat() << endl;
            outFile <<"Is equipped (1 for yes, 0 for no): "<<stan.isOpremen() << endl;
            outFile <<"Area in m2: "<< stan.getPovrsina() << endl;
           
        }
        outFile << "Building: " << zgrada.getImeNaZgrada() << endl;
        outFile << "Address: " << zgrada.getAdresa() << endl;

        int i = 1;
        for (auto stan : zgrada.getStanovi()) {
            outFile << i++ << ". ";
            outFile << stan.getBrojNaStan() << " - " << stan.getBrojNaSobi() << " - " << stan.getPovrsina() << "m2 - ";
            if (stan.isOpremen()) {
                outFile << "equipped - ";
            }
            else {
                outFile << "not equipped - ";
            }
            outFile << stan.cena() << " eur" << endl;
        }
        outFile.close();
        cout << "The data has been saved to file: " << filename << endl;
    }
    else {
        cout << "Could not open save file: " << filename << endl;
    }
    zgrada.pecati();
    // ask user if they want to add more buildings
    char answer;
    cout << "Do you want to add another building? (y/n): ";
    cin >> answer;

    while (tolower(answer) == 'y') {
        cin.ignore(); // clear input buffer
        main(); // recursively call main to add another building
        cout << "Do you want to add another building? (y/n): ";
        cin >> answer;
    }
    //The code was developed by Oliver Nikolajevic
    return 0;
}
