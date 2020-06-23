#pragma once
#include <string>
#include <iostream>
using namespace std;

typedef struct Person
{
	int id;
	bool gender;
	string firstName;
	string lastName;
	Person* mom;
	Person* dad;
};