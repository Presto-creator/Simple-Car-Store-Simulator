#ifndef CARSTORE_H
#define CARSTORE_H
#include <iostream>
#include <string>
#include "DLinkedList.h"

#include <vector>




using namespace std;

class CarRental {

public:
	//default constructor
	CarRental() { reserved = 0; id = -1; numSeats = -1; numFeatures = -1; brand = "No Brand"; model = "No Model"; }
	
	//overloaded constructor
	
	CarRental(int reserved_, string id_, int numSeats_, int numFeatures_, string brand_, string model_, DLinkedList<string> features_) {
		reserved = reserved_; id = id_; numSeats = numSeats_; numFeatures = numFeatures_; brand = brand_; model = model_;
		
		features = features_; // do i need to make this a for loop?
	}

	//copy constructor
	CarRental(const CarRental& copy);

	//destructor
	~CarRental() {}

	//getters
	string getid() const { return id; }
	int getnumseats() const{ return numSeats; }
	int getreserved() const { return reserved; }
	int getnumfeatures() const { return numFeatures; }
	string getbrand() const { return brand; }
	 string getmodel() const { return model; }
	DLinkedList<string> getFeaturesList() const { // broken
		return features;
	}

	//setters
	void setid(int e) { id = e; }
	void setnumseats(int e) { numSeats = e; }
	void setnumfeatures(int e) { numFeatures = e; }
	void setreserved() { reserved = 0; }
	void setavailable () { reserved = 1; }
	void setbrand(string e) { brand = e; }
	void setmodel(string e) { model = e; }
	void setfeatures(DLinkedList<string> features_)
	{features = features_;} // DLinkedList inmplementation, might need to do for loop to copy everythign over
	

	//operator overloading
	bool operator>(const CarRental&);
	bool operator<(const CarRental&);
	bool operator==(const CarRental&);
	bool operator<=(const CarRental&);
	bool operator>=(const CarRental&);
	bool operator!=(const CarRental&);

	//assignment operator
	CarRental operator=(const CarRental& rhs);

	//output operators
	friend ostream& operator<<(ostream& os, const CarRental& car); // console screen
	friend ofstream& operator<<(ofstream& out, const CarRental& objV); // output file


private:
	int reserved, numSeats, numFeatures;
	string id, brand, model;
	DLinkedList<string> features; 

};

ofstream& operator<<(ofstream& out, const CarRental& objV) {
	out << objV.id << endl;
	out << objV.brand << endl;
	out << objV.model << endl;
	out << objV.numSeats << endl;
	out << objV.reserved << endl;
	out << objV.numFeatures << endl;
	for (DNode<string>* current = objV.features.getHead()->getNext(); current != objV.features.getTail(); current = current->getNext()) {
		out << current->getElem() << endl;
	}

	return out;
}
ostream& operator<<(ostream& os, const CarRental& car)
{
	os << "ID: " << car.id << endl;
	os << "Make: " << car.brand << endl;
	os << "Model: " << car.model << endl;
	os << "Number of seats: " << car.numSeats << endl;
	os << "Is available : ";
	if (car.reserved == 1) { os << "Yes" << endl; }
	else { os << "No" << endl; }
	os << "Extra Features[" << car.numFeatures << "]:" << endl;
	
	for (DNode<string>* current = car.features.getHead()->getNext(); current != car.features.getTail(); current = current->getNext()) {
		os << current->getElem();
		if (current->getNext() != car.features.getTail()) {
			os << ", ";
		}
	}

	os <<endl << "========================================================" << endl;
	return os;
}

CarRental CarRental::operator=(const CarRental& rhs)
{
	if (this != &rhs) {
		reserved = rhs.reserved;
		numSeats = rhs.numSeats;
		numFeatures = rhs.numFeatures;
		id = rhs.id;
		brand = rhs.brand;
		model = rhs.model;
		//for (DNode<string>* current = rhs.getFeaturesList().getHead()->getNext(); current != rhs.getFeaturesList().getTail(); current = current->getNext()) {
		//	features.addBack(current->getElem());
		//}
		DLinkedList<string> other = rhs.getFeaturesList();
		features = other;

	}
	return *this;
}

CarRental::CarRental(const CarRental& rhs)
{
	reserved = rhs.reserved;
	numSeats = rhs.numSeats;
	numFeatures = rhs.numFeatures;
	id = rhs.id;
	brand = rhs.brand;
	model = rhs.model;
	//for (DNode<string>* current = rhs.getFeaturesList().getHead()->getNext(); current != rhs.getFeaturesList().getTail(); current = current->getNext()) {
	//	features.addBack(current->getElem());
	//}
	DLinkedList<string> other = rhs.getFeaturesList();
	features = other;
}

bool CarRental::operator>(const CarRental& rhs)
{
	if (numSeats > rhs.numSeats) {
		return true;
	}
	return false;
}

bool CarRental::operator<(const CarRental& rhs)
{
	if (numSeats < rhs.numSeats) {
		return true;
	}
	return false;
}

bool CarRental::operator==(const CarRental& rhs)
{
	if (id == rhs.id) {
		return true;
	}
	return false;
}

bool CarRental::operator>=(const CarRental& rhs)
{
	if (numSeats >= rhs.numSeats) {
		return true;
	}
	return false;
}

bool CarRental::operator<=(const CarRental& rhs)
{
	if (numSeats <= rhs.numSeats) {
		return true;
	}
	return false;
}

bool CarRental::operator!=(const CarRental& rhs)
{
	if (id != rhs.id) {
		return true;
	}
	return false;
}




#endif