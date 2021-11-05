/*
* This program is 3 projects in 1 assignment, with 3 parts.
* All created by Preston Leigh, with the exception of the DLinkedList, which was created by Dr. Alnaeli
* November 4, 2021 
*/

#include <iostream>
#include <string>
#include <fstream>
#include "DLinkedList.h"
#include "CarStore.h"
#include "Inventory.h"

using namespace std;

void printMenu();
bool readingDataFromDBFile(Inventory&,ifstream&,int);
bool printToFile(ofstream&, Inventory&, int);

int main()
{

    ifstream infile;
    ofstream outfile;
      Inventory carList;
        int numrentals = 0;
        int seats = 0; // used in case 4

        if (!readingDataFromDBFile(carList, infile, numrentals)) {
            cout << "Could not open file! Exiting program."; return (17);
        }

        int userinput = 0; // default 
        string inputstring; // input string user will use to input words

        while (userinput != 8) //while menu is still active
        {
          
            printMenu();
            cin >> userinput;

            switch (userinput) {
            case 1: // print all registered
                system("cls");
                carList.printList();
                break;

            case 2: // print all available
                system("cls");
                carList.printReserved(1); // print available
                break;

            case 3: // print reserved
                system("cls");
                carList.printReserved(0); // print reserved
                break;

            case 4: // check availability, check number of seats
               
                cout << endl << "Input the minimum amount of seats you want to see in your car : ";
              
                do { // input checking
                    cin >> seats;
                    if (!seats) {
                        system("cls");
                        cout << "Incorrect input. Please enter an option!" << endl << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        seats = -3; // random number to keep the while loop going
                    } // end if
                } while (seats == -3); 

                carList.searchSeats(seats);
                break;

            case 5: // reserve a vehicle output to file then input back into the thing
                system("cls");

                carList.printReserved(1); // print available cars
                cout << endl << "Input the ID of the car you wish to reserve and hit enter : ";
                cin.ignore();
                getline(cin, inputstring);
                if (carList.reserveCar(inputstring)) { // check if the input id is already taken
                    cout << "Car is reserved!" << endl;
                }
                else {
                    cout << "Either your input was not valid, or the ID you input is already reserved." << endl;
                }
                cout << endl;

                break;

            case 6: // return a reserved vehicle output to file then input back into the thing
                system("cls");

                carList.printReserved(0);
                cout << endl << "Input the ID of the car you wish to return and hit enter : ";
                cin.ignore();
                getline(cin, inputstring);
                if (carList.unreserveCar(inputstring)) {
                    cout << "Car is returned!" << endl;
                }
                else {
                    cout << "Either your input was not valid, or the ID you input is already available." << endl;
                }
                cout << endl;
                
                break;

            case 7: // print everything to vehicles.txt
                system("cls");
                
                if (!printToFile(outfile, carList, numrentals)) {
                    cout << "Printing to file failed, exiting! Error 7" << endl;
                    exit(7);
                }
                cout << "Vehicles File Updated!" << endl << endl;
                
                break;

            case 8: // exit the program
                system("cls");
                cin.ignore();
                cout << "Before you go, would you like to save the car list to vehicles.txt? Enter Y or N : ";
                getline(cin, inputstring); // instead of having to create a new char, just reuse inputstring
                
                if (inputstring.at(0) == 'Y' || inputstring.at(0) == 'y') { 
                    if (!printToFile(outfile, carList, numrentals)) {
                        cout << "Printing to file failed, exiting! Error 7" << endl;
                        exit(7);
                    }
                    cout << "Vehicles File Updated!" << endl << endl;
                }

                cout << "Exiting program." << endl << endl;
                break;

            case 9: // add a new car to the list
                system("cls");
               
                carList.createCar();
              
                ++numrentals;
                cout << endl;
                break;

            default:
                system("cls");
                cout << "Incorrect input. Please enter a valid option!" << endl << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                userinput = 0;
                break;
            } // end switch
        } // end while


    return 0;
}


void printMenu() {
    cout << "1. Print All of the registered vehicles. (available and already reserved)" << endl;
    cout << "2. Print list of the available vehicles." << endl;
    cout << "3. List of the reserved vehicles (rented currently by customers)." << endl;
    cout << "4. Check availability" << endl;
    cout << "5. Reserve a vehicle" << endl;
    cout << "6. Return a reserved vehicle" << endl;
    cout << "7. Print all registered vehicles to a text file" << endl;
    cout << "8. Exit" << endl;
    cout << "9. Add a new car to the list." << endl;
    cout << "Enter your answer --->  ";
}

bool readingDataFromDBFile(Inventory& carList, ifstream& infile, int numrentals)
{
    int reserved, numSeats, numFeatures;
    string id, brand, model, feature;

    infile.open("vehicles.txt");
    if (!infile.fail()) {
        if (infile.is_open()) {
   
        infile >> numrentals; // number of rentals to go through
        carList.setsize(numrentals);
            int count = 0;
            infile.ignore();

            while (count < numrentals) {

                getline(infile, id); // 10004 
                getline(infile, brand); // Dodge
                getline(infile, model); // grand caravan

                infile.clear(); // make sure is needed

                infile >> numSeats; // 7 num seat
                infile >> reserved; // 1, is reserved
                infile >> numFeatures; // 3

                infile.clear();
                infile.ignore();


                 DLinkedList<string> cflist;
               

                for (int j = 0; j < numFeatures; ++j) { // put features into thing
                    getline(infile, feature);

                    cflist.addBack(feature);

                }
                // infile.ignore();

                carList.addCar(CarRental(reserved, id, numSeats, numFeatures, brand, model, cflist));
             
                ++count;
            } // end while


        } // carList is now full from vehicles.txt
        infile.close();
        return true;
    }
    return false;
}


bool printToFile(ofstream& outfile, Inventory& inven, int RecordsInFile)
{
    outfile.open("vehicles.txt");
    if (!outfile.fail()) {
        if (outfile.is_open()) {
            outfile << inven;
            return true;
        }//end if
    } // end if
    return false;
}


void checkInt(int checked) {
    bool valid = false;
    do {

        if (!checked) {
            cin >> checked;
        }

    } while (!valid);
}

