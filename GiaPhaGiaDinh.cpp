// GiaPhaGiaDinh.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Source.h";

Person* root = NULL;
Person* point = NULL;
const char* MAN_GENERATIONS[10] = { "root", "father", "grandfather", "great-grandfather" };
const char* WOMAN_GENERATIONS[10] = { "root", "mother", "granmother", "great-granmother" };

// 
Person* getPerson();

// Function
void printTree(Person* current, int level);
void addRoot();
void addDad();
void addMom();
void saveFile();
void readFile();
void goToDad();
void goToMom();
void goUpOneLevel();

/*-------------------- MAIN -------------------*/
int main()
{
    while (true)
    {
        system("cls");
        if (root != NULL) 
        {
            printTree(root, 0);
            cout << "\n";
        }
        else
        {
            cout << "No root exist!\n\n";
        }

        // Show menu
        cout << "R - Create a root node\n";
        cout << "V - Add father to current node\n";
        cout << "S - Saving the entire family tree in a file\n";
        cout << "F - Reading of the entire family tree from file\n";
        cout << "D - Navigation: go down to father\n";
        cout << "A - Navigation: go down to mother\n";
        cout << "W - Navigation: go up one level to descendants\n";
        cout << "E - Exit program\n";

        char choice;
        cout << "Enter the choice: ";
        cin >> choice;

        switch (choice)
        {
        case 'R':
            addRoot();
            break;

        case 'V':
            addDad();
            break;

        case 'S':
            saveFile();
            break;

        case 'F':
            readFile();
            break;

        case 'D':
            goToDad();
            break;

        case 'A':
            goToMom();
            break;

        case 'W':
            goUpOneLevel();
            break;

        case 'E':
            exit(0);
            break;
        default:
            cout << "You entered the wrong one\n";
        }
    }
}
/*------------------ END-MAIN ------------------*/

Person* getPerson()
{
    Person* ptr = new Person();
    rewind(stdin);
    cout << "Enter the first name: ";
    getline(cin, ptr->firstName);
    cout << "Enter the last name: ";
    getline(cin, ptr->lastName);
    //cout << "Enter the age: ";
    //cin >> ptr->age;
    return ptr;
}

void printTree(Person *current, int level)
{
    level %= 4;
    if (current == point)
    {
        cout << ">>> ";
    }

    if (current->gender) 
    {
        // Man
        cout << "Full name: " << current->firstName << " " << current->lastName << " ( " << MAN_GENERATIONS[level] << ")\n";
    }
    else 
    {
        cout << "Full name: " << current->firstName << " " << current->lastName << " ( " << WOMAN_GENERATIONS[level] << ")\n";
    }

    // Go to parent
    if (current->dad != NULL)
    {
        printTree(current->dad, level + 1);
    }

    if (current->mom != NULL)
    {
        printTree(current->mom, level + 1);
    }
}

void addRoot()
{
    if (root == NULL) 
    {
        root = getPerson();
        point = root;
    }
    else
    {
        cout << "Root already exist!\n";
    }
}

void addDad()
{
    system("cls");
    cout << "Add father\n";
    Person* dad = getPerson();
    dad->gender = true;
    point->addDad(dad);
}

void addMom()
{
    system("cls");
    cout << "Add mother\n";
    Person* mom = getPerson();
    mom->gender = false;
    point->addMom(mom);
}

void saveFile()
{
    cout << "Save file!\n";
}

void readFile()
{
    cout << "read file\n";
}

void goToDad()
{
    if (point->dad != NULL)
    {
        point = point->dad;
    }
    else
    {
        cout << "No father!\n";
    }
}

void goToMom()
{
    if (point->mom != NULL)
    {
        point = point->mom;
    }
    else
    {
        cout << "No mother!\n";
    }
}

void goUpOneLevel()
{
    // New children
}
