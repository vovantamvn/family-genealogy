#pragma once
#include "Person.h";

class FamilyTree
{
private:
	Person* root;
	Person* point;

	const char* MAN_GENERATIONS[10] = { "root", "father", "grandfather", "great-grandfather" };
	const char* WOMAN_GENERATIONS[10] = { "root", "mother", "granmother", "great-granmother" };

	void printTree(Person* current, int level);
	Person* getPerson();
	void createIndexOfTree();
	void createIndexOfNode(Person* person, int index);
	int getSizeOfTree(Person* tree);
	Person* getAllPersonInTree();
	void addNodeInArray(Person* arr, int& index, Person* tree);
	void writeNodeInFile(ofstream& file, Person node, bool isEndFile);
	Person** getAllPersonInFile();
	void addNodeToTree(Person* tree, Person* node);

public:
	void goToRoot();
	void showData();
	void addRoot();
	void addDad();
	void addMom();
	void saveFile();
	void readFile();
	void goToDad();
	void goToMom();
	void goUpOneLevel();
};

