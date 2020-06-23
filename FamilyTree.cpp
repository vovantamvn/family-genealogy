#include "FamilyTree.h"
#include <fstream>


void FamilyTree::createIndexOfTree()
{
    if (root == NULL) {
        exit(1);
    }

    createIndexOfNode(root, 1);
}

void FamilyTree::createIndexOfNode(Person* person, int index)
{
    person->id = index;

    if (person->dad != NULL)
    {
        createIndexOfNode(person->dad, 2 * index);
    }

    if (person->mom != NULL)
    {
        createIndexOfNode(person->mom, 2 * index + 1);
    }
}

int FamilyTree::getSizeOfTree(Person* tree)
{
    if (tree == NULL) {
        return 0;
    }

    return 1 + getSizeOfTree(tree->dad) + getSizeOfTree(tree->mom);
}

Person* FamilyTree::getAllPersonInTree()
{
    int length = getSizeOfTree(root);
    Person* persons = new Person[length];
    int index = 0;
    addNodeInArray(persons, index, root);
    return persons;
}

void FamilyTree::addNodeInArray(Person* arr, int& index, Person* tree)
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

void FamilyTree::writeNodeInFile(ofstream& file, Person node, bool isEndFile)
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

Person** FamilyTree::getAllPersonInFile()
{
    Person** arr = new Person * [100];
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

void FamilyTree::addNodeToTree(Person* tree, Person* node)
{
    // Check father
    if (2 * tree->id == node->id)
    {
        tree->dad = node;
        return;
    }
    // Check mother
    if ((2 * tree->id) + 1 == node->id)
    {
        tree->mom = node;
        return;
    }

    if (tree->dad != NULL)
    {
        addNodeToTree(tree->dad, node);
    }

    if (tree->mom != NULL)
    {
        addNodeToTree(tree->mom, node);
    }
}

/*
FamilyTree::FamilyTree()
{
	root = NULL;
	point = NULL;
}
*/

void FamilyTree::goToRoot()
{
    point = root;
}

void FamilyTree::printTree(Person* current, int level)
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

Person* FamilyTree::getPerson()
{
    Person* ptr = new Person();
    rewind(stdin);
    cout << "Enter the first name: ";
    getline(cin, ptr->firstName);
    cout << "Enter the last name: ";
    getline(cin, ptr->lastName);
    return ptr;
}

void FamilyTree::showData()
{
    printTree(root, 0);
}

void FamilyTree::addRoot()
{
    cout << "Create root!\n";
    root = getPerson();
    point = root;
}

void FamilyTree::addDad()
{
    cout << "Add father\n";
    Person* dad = getPerson();
    dad->gender = true;
    point->dad = dad;
}

void FamilyTree::addMom()
{
    cout << "Add mother\n";
    Person* mom = getPerson();
    mom->gender = false;
    point->mom = mom;
}

void FamilyTree::saveFile()
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
}

void FamilyTree::readFile()
{
    Person** arr = getAllPersonInFile();
    if (arr[1] == NULL) {
        cout << "No Data!\n";
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

void FamilyTree::goToDad()
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

void FamilyTree::goToMom()
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

void FamilyTree::goUpOneLevel()
{
    cout << "Create a child for root!\n";
    Person* child = getPerson();
    Person* parent = root;
    root = child;

    if (parent->gender == true)
    {
        root->dad = parent;
    }
    else
    {
        root->mom = parent;
    }
}
