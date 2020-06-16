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
void writeNodeInFile(ofstream& file, Person node, bool isEndFile);
Person** getAllPersonInFile();
void addNodeToTree(Person* tree, Person* node);

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

void writeNodeInFile(ofstream& file, Person node, bool isEndFile)
{
    file << node.id;
    file << " ";
    file << node.gender;
    file << node.firstName;
    file << ",";
    file << node.lastName;
    
    if (!isEndFile)
    {
        file << '\n';
    }
}

Person** getAllPersonInFile()
{
    Person** arr = new Person*[100];
    ifstream file("data.txt");

    for (int i = 0; i < 100; i++)
    {
        arr[i] = NULL;
    }

    while (!file.eof())
    {
        try
        {
            Person* p = new Person();
            file >> p->id;
            file >> p->gender;
            getline(file, p->firstName, ',');
            getline(file, p->lastName);
            
            // Store
            arr[p->id] = p;
        }
        catch (const std::exception&)
        {

        }
    }

    return arr;
}

void addNodeToTree(Person* tree, Person* node)
{
    // Check father
    if (2 * tree->id == node->id)
    {
        tree->addDad(node);
        return;
    }
    // Check mother
    if ((2 * tree->id) + 1 == node->id)
    {
        tree->addMom(node);
        return;
    }

    if(tree->dad != NULL)
    {
        addNodeToTree(tree->dad, node);
    }

    if (tree->mom != NULL)
    {
        addNodeToTree(tree->mom, node);
    }
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
        if (i != length - 1)
        {
            writeNodeInFile(file, persons[i], false);
        }
        else
        {
            writeNodeInFile(file, persons[i], true);
        }
    }
    file.close();
    
    cout << "Save file success!\n";
    system("pause");
}

void readFile()
{
    Person** arr = getAllPersonInFile();
    if (arr[1] == NULL) {
        cout << "No Data!\n";
        system("pause");
        return;
    }

    root = arr[1];
    for (int i = 2; i < 100; i++) {
        if (arr[i] != NULL)
        {
            addNodeToTree(root, arr[i]);
        }
    }

    // Current point is root
    point = root;
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
