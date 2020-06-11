#pragma once
#include <string>
#include <iostream>
using namespace std;

typedef struct Person
{
	int id;
	int age;
	bool gender;
	string firstName;
	string lastName;
	
	// Family
	Person* mom;
	Person* dad;
	
	// Function
	Person();
	void addMom(Person* mom);
	void addDad(Person* dad);
	void show();
};

Person::Person() 
{
	age = 0;
	firstName = "";
	lastName = "";
	gender = true; // True is a man
	mom = NULL;
	dad = NULL;
}

void Person::addMom(Person* mom)
{
	this->mom = mom;
}

void Person::addDad(Person* dad)
{
	this->dad = dad;
}

void Person::show()
{
	cout	<< "Person {FullName: " 
			<< this->firstName 
			<< " " 
			<< this->lastName 
			<< ", Age: "
			<< this->age 
			<< "}";
}
