#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <fstream>
#include "DLinkedList.h"
#include "CarStore.h"

using namespace std;

class Inventory {
public:

	//default constructor
	Inventory() { registeredVehicles = 0; }
	
	//overloaded contructor
	Inventory(DLinkedList<CarRental> NList) { carList = NList; }

	//destructor
	~Inventory() {};

	//copy constructor
	Inventory(const Inventory& rhs);

	//reserve / unreserve / check if id is available
	bool reserveCar(string CarID);
	bool unreserveCar(string CarID);
	bool IDAvailable(string id);

	//getters
	int getsize() { return registeredVehicles; }
	void setsize(int e) { registeredVehicles = e; }
	
	//void
	void addCar(const CarRental& org);
	void printList();
	void printReserved(int which);
	void searchSeats(int seats);
	void createCar();
	void increaseNum() { registeredVehicles++; }
	void descreaseNum() { registeredVehicles--; }
	void clear();

	//assignment operator
	Inventory operator=(const Inventory& rhs);
	friend ofstream& operator<<(ofstream& out, const Inventory& objV); // output file

private:
	DLinkedList<CarRental> carList;
	int registeredVehicles;
};

void Inventory::clear() {
	for (int i = 0; i < registeredVehicles; ++i) {
		carList.removeBack();
	}
}

ofstream& operator<<(ofstream& out, const Inventory& objV)
{	
	out << objV.registeredVehicles << endl;
	for (DNode<CarRental>* curr = objV.carList.getHead()->getNext(); curr != objV.carList.getTail(); curr = curr->getNext())
	{
		out << curr->getElem();
		//curr->getElem().getFeaturesList();  WORKS WHAT
	}//end for
return out;
}


Inventory Inventory::operator=(const Inventory& rhs) {
	if (this != &rhs) {
		registeredVehicles = rhs.registeredVehicles;

		for (DNode<CarRental>* curr = rhs.carList.getHead()->getNext(); curr != rhs.carList.getTail(); curr = curr->getNext())
		{
			carList.addBack(curr->getElem());
			
		}//end for
	}//end if
		return *this;
}

void Inventory::addCar(const CarRental& org) // add car to list
{
	carList.addBack(org);
	
}

void Inventory::printList() { // print every car in the list
	for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
	{
		cout << curr->getElem() << endl;
		//curr->getElem().getFeaturesList();  WORKS WHAT
	}//end for
	
}

void Inventory::createCar() {
	int reserved, numSeats, numFeatures;
	string id, brand, model, feature;

	cin.ignore();
	cout << endl;
	cout << "Who created the car? : ";
	getline(cin, brand);
	cout << endl << "What is the car model? : ";
	getline(cin, model);
	cout << "What is the ID of this car? If the ID is already taken, then you will have to repeat your input (Enter Integer):";
	
	do { // do while loop for checking if the ID is available or not

		getline(cin, id);

	} while (!IDAvailable(id));

	
	cout << endl << "How many seats are in this car? (Greater than 0) :";
	
	cin >> numSeats;
	while (!numSeats || numSeats < 1) {
		cout << "Enter a valid input please! : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		numSeats = 0;
		cin >> numSeats;
	}
	
	cout <<endl << "How many features are in this car? (Cannot be less than 0) :";
	cin >> numFeatures;
	while (!numFeatures || numFeatures < 0) {
		cout << "Enter a valid input please! : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		numFeatures = 0;
		cin >> numFeatures;
	}
	cin.ignore();

	if ( numFeatures > 0) {
		cout << "What are these features? (Hit enter after each feature, NO SPACES:" << endl;
		DLinkedList<string> tempVec; 
			string inputstring;
			
		for (int i = 0; i < numFeatures; ++i) {
			getline(cin, inputstring);
			tempVec.addBack(inputstring);
		} // end for

		carList.addBack(CarRental(0, id, numSeats, numFeatures, brand, model, tempVec));
		registeredVehicles++;
	}
	
}

void Inventory::printReserved(int which)
{
	if (which == 1) { // show available
		for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
		{
			
			if (curr->getElem().getreserved() == 1) {
				cout << curr->getElem() << endl;
			}
		}//end for
	} // end if
	else { // show reserved

		for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
		{

			if (curr->getElem().getreserved() == 0) {
				cout << curr->getElem() << endl;
			}
		}//end for
	} // end else
}

void Inventory::searchSeats(int seats)
{
	cout <<  "Number of cars available with " << seats << " seats: " << endl << endl;
	for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
	{
		if (curr->getElem().getnumseats() >= seats){
			cout << curr->getElem() << endl;
		} // end if
	} // end for
	
}

bool Inventory::IDAvailable(string id)
{
	for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
	{
		if (curr->getElem().getid() == id) {
			return false;
		} // end if
	} // end for
	return true;
}


Inventory::Inventory(const Inventory& rhs)
{
	registeredVehicles = rhs.registeredVehicles;

	for (DNode<CarRental>* curr = rhs.carList.getHead()->getNext(); curr != rhs.carList.getTail(); curr = curr->getNext())
	{
		carList.addBack(curr->getElem());

	}//end for
}

bool Inventory::reserveCar(string CarID)
	{
		//look up a car in my doubly linked list that has the car ID

		for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
		{
			if (curr->getElem().getid() == CarID) {
				if (curr->getElem().getreserved() == 1) {
					
					curr->getElem().setreserved();
					return true;
				} // end if
				else {
					return false;
				} // end else
			} // end if
		}//end for

		
		return false;
	}

	bool Inventory::unreserveCar(string CarID) // set to 1
{
		for (DNode<CarRental>* curr = carList.getHead()->getNext(); curr != carList.getTail(); curr = curr->getNext())
		{
			if (curr->getElem().getid() == CarID) {
				if (curr->getElem().getreserved() == 0) {
					
					curr->getElem().setavailable();
					return true;
				} // end if
				else {
					return false;
				} // end else
			} // end if
		}//end for

		return false;
}



#endif