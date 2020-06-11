// GiaPhaGiaDinh.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Source.h";

int main()
{
    Person* p = new Person();
    p->age = 15;
    p->firstName = "Vo";
    p->lastName = "Tam";
    p->show();
}