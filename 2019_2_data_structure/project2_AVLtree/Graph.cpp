#include "Graph.h"
#include <stack>
#include <map>

Graph::Graph(ofstream * flog)
{
	this->flog = flog;//function to write data in txt file
}

Graph::~Graph()
{
}

bool Graph::Build(AVLTree * root)
{
	stack<CityData*> stack1;//stack that save data

	AVLNode* curr = root->root;//AVLTree's root
	root->nodenumber = 0;
	root->numberinorder(root->root,stack1);//size check
	size = root->nodenumber;//number of call = size
	
	mList = new map<int, int> [size];//mList take data place
	
	if (root == NULL) {//root is NULL
		return false;
	}
	Inorder(root->root, stack1);

	vertex = new CityData*[size]();//vertex take data place
	for (int i = 0; i<size;i++) {
		vertex[i] = new CityData;//vertex[] take data place
		vertex[i] = stack1.top();//take data from stack's top data
		stack1.pop();//and delete value in stack
	}

	for (int i = 0;i<size;i++) {
		for (int j = 0; j<size; j++) {
			int k = abs(vertex[i]->GetLocationId() - vertex[j]->GetLocationId());//make absolute value of minus value
			mList[i].insert(make_pair(j,k));//insert datas in mList
		}
	}
	return false;
}
void Graph::Inorder(AVLNode* tree, stack<CityData*>& stack1) {//not inorder, post fix
	if (tree != nullptr) {
		Inorder(tree->GetRight(), stack1);//call funtion about right node
		stack1.push(tree->GetCityData());//put citydata in stack
		Inorder(tree->GetLeft(), stack1);//call function about left node
	}
	
}

void Graph::Print_GP()
{
	for (int i = 0; i<size; i++) {
		for (auto it = mList[i].begin(); it != mList[i].end();it++) {//loop in mList
			*flog << it->second << " ";//write Length between nodes
		}
		*flog << endl;//change line
	}
}

void Graph::Print_MST()
{
	int distance=0;
	int distance2 = 0;
	for (int i = 0;i<size-1; i++) {
		distance2 = (mList[mstMatrix2[i]].find(mstMatrix2[i+1])->second);//length between them
		*flog << "("<<vertex[mstMatrix2[i]]->Getname()<<", "<<vertex[mstMatrix2[i+1]]->Getname()<<"), "<<
			distance2<<endl;//call 2city and length between them
		distance += abs(vertex[mstMatrix2[i]]->GetLocationId() - vertex[mstMatrix2[i + 1]]->GetLocationId());//plus length to mst total length
	}
	
	*flog << "Total: " << distance << endl;;
}

bool Graph::Kruskal()
{
	int t = 0, t2 = 0, n = 0;
	int min;
	
	numcheck = new int *[size];
	for (int i = 0; i < size; i++) {//initialize to check cycle
		numcheck[i] = new int[size];
		for (int j = 0; j < size; j++) {
			numcheck[i][j] = -2;
		}
	}
	map<int, int> * mList2 = new map<int, int>[size];//initialize to save real value
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			mList2[i].insert(make_pair(j, 0));
		}
	}
	
	map<int, int> * mList3 = new map<int, int>[size];//copy mList value in mList3
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			mList3[i].insert(make_pair(j, mList[i].find(j)->second));
		}
	}
	int min2;
	while (n != size - 1 && mList2 != NULL) {
		min = 9999;
		for (int i = 0; i < size; i++) {//find min value and min value's x and y point
			for (int j = 0; j < size; j++) {
				if (min >= mList3[i].find(j)->second && (mList3[i].find(j)->second != 0)) {
					min = mList3[i].find(j)->second;
					t = i; t2 = j;
				}
			}
		}
		min2 = min;
		mList3[t].find(t2)->second = 0;//min value's point change to 0
		mList3[t2].find(t)->second = 0;//and inverted point change to 0 too

		int a = hello(t, t2);//check x and y points condition
		if(a!=2) {//check cycle
			mList2[t].erase(t2);//delete original value in mList
			mList2[t2].erase(t);
			mList2[t].insert(make_pair(t2, min2));//and put new value in mList
			mList2[t2].insert(make_pair(t, min2));
			if (a==0) {//if they are new node
				make_set(t,t2);//make new array that have them
			}
			else if (a==3) {//if t2 is array value and t is new value
				make_tail(t2,t);//give t in t2's array
			}
			else if (a==4) {//if t is array value and t2 is new value
				make_tail(t,t2);//give t2 in t's array
			}
			else if(a==1){//if they are different array value and t exist at more near array
				union_set(t,t2);//give t2's array in t's array
			}
			else {//if they are different array value and t2 exist at more near array
				union_set(t2, t);//give t's array in t2's array
			}	
			n++;//number up
		}
	}
	mstMatrix = new int[size];//give data place to save mst
	mstMatrix2 = new int[size];//give data place to save data to make mst

	int mod = 0;
	int xpos, ypos;
	for (int i = 0; i<size; i++) {//find array have only one edge
		mod = 0;
		for (int j = 0; j < size; j++) {
			if (mList2[i].find(j)->second != 0) {
				mod++; xpos = j; ypos = i;
			}
		}
		if (mod == 1) {//this array is start node
			mstMatrix2[0] = ypos;//its first node
			mstMatrix2[1] = xpos;//and second node
			break;
		}
		
	}
	for (int num = 2; num < size; num++) {//find next node about x and y point
		for (int i = 0; i < size; i++) {
			if (mList2[xpos].find(i)->second != 0&& ypos != i) {
				mstMatrix2[num] = i;//put datas in mstMatrix
				ypos = xpos;//put next point
				xpos = i;
				break;
			}
		}
	}
	if (size == 1) {//no matrix because node number is only one
		mstMatrix[0]=mstMatrix2[0];
	}
	if (size > 1) {//have matrix because node number is upper than 1
		for (int num9 = 0; num9 < size; num9++) {
			if (num9 == (size - 1)) {
				mstMatrix[mstMatrix2[num9]] = mstMatrix2[num9];//final node call self
			}
			else {
				mstMatrix[mstMatrix2[num9]] = mstMatrix2[num9 + 1];//change mstMatrix2 datas and put them in mstMatrix
			}
		}
	}

	if (n < size - 1) {
		cout << "no spanning tree" << endl;
	}
	return false;
}
int Graph::hello(int i1, int i2){//check condition
	int a = -1; int b = -1; int c = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (numcheck[i][j] == -2) {//array have no value
				break;
			}
			if (numcheck[i][j] == i1) {//array y point check have i1 value
				a = i;
				break;
			}
		}
		if (a != -1) {
			break;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (numcheck[i][j] == -2) {//array have no value
				break;
			}
			if (numcheck[i][j] == i2) {//array y point check have i2 value
				b = i;
				break;
			}
		}
		if (b != -1) {
			break;
		}
	}
	if (a == -1 && b == -1) {//values are new node
		c = 0;
	}
	else if (a != b) {//values are different
		if (a == -1) {//a is new node
			c = 3;
		}
		else if (b == -1) {//b is new node
			c = 4;
		}
		else if(a < b){//b's ypoint is bigger than a's ypoint
			c = 1;
		}
		else {//b's ypoint is smaller than a's ypoint
			c = 5;
		}
	}
	else if (a == b) {//they are same array value
		c = 2;
	}
	return c;
}
void Graph::make_set(int i1, int i2)//make new array that have i1 and i2
{
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (numcheck[i][0]==-2){
			j = i;
			break;
		}
	}
	numcheck[j][0] = i1;//new array's first value
	numcheck[j][1] = i2;//new array's second value
}
void Graph::make_tail(int i1, int i2)//add i2 in i1's array's end
{
	int a = -1; int b = -1;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (numcheck[i][j] == i1) {//find i1's array
				a = i; b = j;
				break;
			}
		}
		if (b != -1) {
			break;
		}
	}
	int i = 0;
	while (numcheck[a][i]!=-2) {//go to i1/s array's end
		i++;
	}
	numcheck[a][i] = i2;//plus i2 value
}

void Graph::union_set(int x, int y)//combine array that have x and array that y
{
	int a = -1; 
	int b = -1;
	int k = 0;
	int c = 0;
	for (int i = 0; i < size; i++) {//find x's y point
		for (int j = 0; j < size; j++) {
			if (numcheck[i][j] == x) {
				a = i;
				break;
			}
		}
		if (a != -1) {
			break;
		}
	}
	for (int i = 0; i < size; i++) {//find y;s y point
		for (int j = 0; j < size; j++) {
			if (numcheck[i][j] == y) {
				b = i;
				break;
			}
		}
	}
	while (numcheck[a][k] != -2) {//find x's array end
		k++;
	}
	while (numcheck[b][c] != -2) {//and add y's array to x's array end
		numcheck[a][k] = numcheck[b][c];
		numcheck[b][c] = -2;
		k++;
		c++;
	}
}

void Graph::find(int x)
{
}

