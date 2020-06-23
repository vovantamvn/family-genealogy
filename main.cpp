// This file contains the 'main' function. Program execution begins and ends there.
//

#include "FamilyTree.h"


int main()
{
    FamilyTree familyTree;

    while (true)
    {
        char choice;
        bool isHasData = true;

        cout << "R - Create a root node\n";
        cout << "F - Reading of the entire family tree from file\n";
        cout << "Enter the choice: ";

        cin >> choice;
        if (choice >= 'a' && choice <= 'z')
        {
            choice -= 'a' - 'A';
        }

        switch (choice)
        {
        case 'R':
            familyTree.addRoot();
            break;

        case 'F':
            familyTree.readFile();
            break;

        default:
            isHasData = false;
            cout << "You entered the wrong one\n";
        }

        if (isHasData)
        {
            break;
        }
    }

    while (true)
    {
        char choice;
        familyTree.showData();
        cout << "R - Go to root\n";
        cout << "V - Add father to current node\n";
        cout << "M - Add mother to current node\n";
        cout << "S - Saving the entire family tree in a file\n";
        cout << "D - Navigation: go down to father\n";
        cout << "A - Navigation: go down to mother\n";
        cout << "W - Navigation: go up one level to descendants\n";
        cout << "E - Exit program\n";
        cout << "Enter the choice: ";

        cin >> choice;
        if (choice >= 'a' && choice <= 'z')
        {
            choice -= 'a' - 'A';
        }

        switch (choice)
        {
        case 'R':
            
            break;

        case 'V':
            familyTree.addDad();
            break;

        case 'M':
            familyTree.addMom();
            break;

        case 'S':
            familyTree.saveFile();
            break;

        case 'D':
            familyTree.goToDad();
            break;

        case 'A':
            familyTree.goToMom();
            break;

        case 'W':
            familyTree.goUpOneLevel();
            break;

        case 'E':
            exit(0);
            break;

        default:
            cout << "You entered the wrong one\n";
        }
    }
}