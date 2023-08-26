#include "AVLNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class AVLTree
{
public:
	AVLNode * root;	// AVLTree Root
	ofstream * flog;//variable to write
	int nodenumber;
	int searched;//find search_AVL error
	int searched2;//find search_AVL error

public:
	AVLTree(ofstream * flog);
	~AVLTree();

	AVLNode  *  Getroot();
	void	 	Setroot(AVLNode * node);
	bool		Insert(CityData * node);
	CityData *	Delete(int num);
	CityData *	Search(int num);
	CityData *	Search2(int num);

	bool		Print();//print by inorder
	void inorder(AVLNode * a);//to print datas about bool Print()
	void inorder2(AVLNode * a, int i);//variable to search data
	void inorder22(AVLNode * a, int i);//varialbe to search error check
	void inorder3(AVLNode * a, int i);//delete search varialbe
	char * delsearch;				//delete search check
	void numberinorder(AVLNode*a, stack<CityData*>stack1);//inorder to get data

};

