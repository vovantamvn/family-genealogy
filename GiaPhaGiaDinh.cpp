// GiaPhaGiaDinh.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Source.h";
#include <fstream>

Person* root = NULL;
Person* point = NULL;
const char* MAN_GENERATIONS[10] = { "root", "father", "grandfather", "great-grandfather" };
const char* WOMAN_GENERATIONS[10] = { "root", "mother", "granmother", "great-granmother" };

// 
Person* getPerson();
void initData();
void mainMenu();
void createIndexOfTree();
void createIndexOfNode(Person* person, int index);
int getSizeOfTree(Person* tree);
Person* getAllPersonInTree();
void addNodeInArray(Person* arr, int& index, Person* tree);
void writeNodeInFile(ofstream& file, Person node);

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
            mainMenu();
        }
        else
        {
            cout << "No root exist!\n\n";
            initData();
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

void initData()
{
    cout << "R - Create a root node\n";
    cout << "F - Reading of the entire family tree from file\n";

    char choice;
    cout << "Enter the choice: ";
    cin >> choice;

    switch (choice)
    {
    case 'R':
        addRoot();
        break;

    case 'F':
        readFile();
        break;

    default:
        cout << "You entered the wrong one\n";
    }
}

void mainMenu()
{
    // Show menu
    cout << "R - Go to root\n";
    cout << "V - Add father to current node\n";
    cout << "M - Add mother to current node\n";
    cout << "S - Saving the entire family tree in a file\n";
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
        point = root;
        break;
 
    case 'V':
        addDad();
        break;

    case 'M':
        addMom();
        break;

    case 'S':
        saveFile();
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
        system("pause");
    }
}

void createIndexOfTree()
{
    if (root == NULL) {
        exit(1);
    }

    createIndexOfNode(root, 1);
}

void createIndexOfNode(Person* person, int index)
{
    person->id = index;

    if (person->dad != NULL) 
    {
        createIndexOfNode(person->dad, 2 * index);
    }

    if(person->mom != NULL)
    {
        createIndexOfNode(person->mom, 2 * index + 1);
    }
}

int getSizeOfTree(Person* tree)
{
    if (tree == NULL) {
        return 0;
    }

    return 1 + getSizeOfTree(tree->dad) + getSizeOfTree(tree->mom);
}

Person* getAllPersonInTree()
{
    int length = getSizeOfTree(root);
    Person* persons = new Person[length];
    int index = 0;
    addNodeInArray(persons, index, root);
    return persons;
}

void addNodeInArray(Person* arr, int& index, Person* tree)
{
    arr[index] = *tree;
    index++;
    
    if (tree->dad != NULL) 
    {
        addNodeInArray(arr, index, tree->dad);
    }

    if (tree->mom)
    {
        addNodeInArray(arr, index, tree->mom);
    }
}

void writeNodeInFile(ofstream& file, Person node)
{
    file << node.id;
    file << ",";
    file << node.firstName;
    file << ",";
    file << node.lastName;
    file << ",";
    file << node.gender;
    file << '\n';
}

void printTree(Person *current, int level)
{
    if (level > 3) {
        level = 3;
    }

    if (current == point)
    {
        cout << ">>> ";
    }

    if (current->gender) 
    {
        // Man
        cout << "Full name: " << current->firstName << " " << current->lastName << " (" << MAN_GENERATIONS[level] << ")\n";
    }
    else 
    {
        cout << "Full name: " << current->firstName << " " << current->lastName << " (" << WOMAN_GENERATIONS[level] << ")\n";
    }

    // Go to father
    if (current->dad != NULL)
    {
        printTree(current->dad, level + 1);
    }

    // Go to mother
    if (current->mom != NULL)
    {
        printTree(current->mom, level + 1);
    }
}

void addRoot()
{
    system("cls");
    cout << "Create root!\n";
    root = getPerson();
    point = root;
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
    createIndexOfTree();
    // Create a array to store tree
    Person* persons = getAllPersonInTree();
    int length = getSizeOfTree(root);
    
    // Create file
    ofstream file;
    file.open("data.txt");

    // Write data
    for (int i = 0; i < length; i++) {
        writeNodeInFile(file, persons[i]);
    }
    file.close();
    
    cout << "Save file success!\n";
    system("pause");
}

void readFile()
{
    cout << "read file\n";
    system("pause");
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
        system("pause");
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
        system("pause");
    }
}

void goUpOneLevel()
{
    // New child for root
    system("cls");
    cout << "Create a child for root!\n";
    Person* child = getPerson();
    Person* temp = root;
    root = child;
    
    if (temp->gender == true) 
    {
        root->addDad(temp);
    }
    else
    {
        root->addMom(temp);
    }
}
