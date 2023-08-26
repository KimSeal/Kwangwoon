#include "AVLTree.h"
#include <iostream>
#include <fstream>// header file declare
#include <map>
#include <stack>
using namespace std;
class Graph
{
public:
	map<int, int> * mList;			// mList[from vetex] = map<to vertex, weigth>
	CityData * * vertex;			// vetex[index] = CityData * 
	int size;						// AVLTree size
	int * mstMatrix;				// MST

	ofstream * flog;				//output datas

	int * * numcheck;			//check did vertex
	int * mstMatrix2;			// MST to make final mstMatrix

public:
	Graph(ofstream * flog);
	~Graph();

	bool	Build(AVLTree * root);	//build graph
	void 	Print_GP();				//print graph
	void	Print_MST();			//print mst

	/*for Kruskal union_set*/
	bool	Kruskal();
	void 	make_set(int x, int y);//if nodes are new node
	void 	make_tail(int x, int y);//if one node is new node
	void 	union_set(int x, int y);//if nodes are old node
	void	find(int x);

	void Inorder(AVLNode* tree, stack<CityData*>& stack1);//in order to stack and take data
	int hello(int, int);//find kruskal condition
};
