#include "Graph.h"
#include<utility>
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Manager
{
public:
	AVLTree * avl;	//avl tree
	Graph * gp;		//graph

	char * cmd;
	int iter;
	int rootcheck;
	int didload;//error check variable about load, graph, mst 
	int didgraph;
	int didmst;

public:
	Manager();
	~Manager();

	char * one2;

	ofstream flog;//output about text
	ifstream fin;//input about text

	ifstream fin2;//city list input

	void run(const char * command);	//start program
	bool LOAD();					//take text file and change datas to avl tree
	bool INSERT();					//insert node in avl tree
	bool PRINT_AVL();				//print all node of avl tree
	bool SEARCH_AVL(int two);		//search node that have two value
	bool SEARCH_AVL2(int two);		//check existence of node that have two value

	bool DELETE_AVL();				//Delete value
	bool BUILD_GP();				//make graph
	bool PRINT_GP();				//print graph
	bool BUILD_MST();				//build mst
	bool PRINT_MST();				//print mst
	void EXIT();					//end of code

	void printErrorCode(int n, const char * cmdname);//error print
	void printSuccessCode(const char * cmdname);	//success print

};
