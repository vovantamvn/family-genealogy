#pragma once
#include <string>
#include <iostream>
using namespace std;

typedef struct Person
{
	int id;
	int age;
	string firstName;
	string lastName;
	
	// Family
	Person* sibling;
	Person* mom;
	Person* dad;
	
	// Function
	Person();
	void addSibling(Person* sib);
	void addMom(Person* mom);
	void addDad(Person* dad);
	void show();
};

Person::Person() 
{
	age = 0;
	firstName = "";
	lastName = "";
	sibling = NULL;
	mom = NULL;
	dad = NULL;
}

void Person::addSibling(Person* sib)
{
	if (this->sibling == NULL) {
		this->sibling = sib;
		return;
	}

	Person* tSib = this->sibling;
	while (tSib != NULL)
	{
		tSib = tSib->sibling;
	}

	// Add sibling
	tSib = sib;
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
