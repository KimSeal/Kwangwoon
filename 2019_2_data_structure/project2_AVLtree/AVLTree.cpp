#include "AVLTree.h"

AVLTree::AVLTree(ofstream * flog)
{
	root = NULL;//root is null because tree is empty
	this->flog = flog;//call flog
	nodenumber = 0;//initialize node check variable
	searched = 0;//initialize error check variables
	searched2 = 0;

}

AVLTree::~AVLTree()
{
}

AVLNode * AVLTree::Getroot()
{
	return this->root;//get root function
}

void AVLTree::Setroot(AVLNode * node)
{
	this->root = node;//give root to avltree
}

bool AVLTree::Insert(CityData * node)
{
	if (root == NULL) {			//no root case
		root = new AVLNode;		//give data place to root
		root->SetCityData(node);//give node citydata to root
		Getroot()->SetmBF(0);	//give mBF data to root
		return true;
	}
	AVLNode *a = Getroot(),//mast recent node with bf=+-1
		*pa = NULL, //parent of a
		*p=Getroot(), //p moves through the tree
		*pp=NULL, //parent of p
		*rootSub=NULL;
	while (p != NULL) {
		if (p->GetmBF() != 0) { a = p; pa = pp; }
		if (strcmp(p->GetCityData()->Getname(), node->Getname())>0) { pp = p; p=p->GetLeft(); }//take left branch
		else if (strcmp(node->Getname(), p->GetCityData()->Getname())>0) { pp = p; p=p->GetRight(); }//take right branch
		else { p->SetCityData(node); return true; }//node is already in tree. update it
	}
	//Phase 2:insert and rebalance. k is not in the tree and
	//may be inserted as the apropriate chile of pp
	AVLNode *y = new AVLNode;
	y->SetCityData(node);
	if (strcmp(pp->GetCityData()->Getname(), node->Getname() )>0) { pp->SetLeft(y); }//insert as left child
	else { pp->SetRight(y); }//insert as right child

	int d;
	AVLNode *b, *c;//child of a and b
	if (strcmp(node->Getname(), a->GetCityData()->Getname())>0) { b = a->GetRight(); p = a->GetRight(); d = -1; }
	else { b = a->GetLeft(); (p = a->GetLeft()); d = 1; }
	while (p != y) {
		if (strcmp(node->Getname(), p->GetCityData()->Getname())>0) {//height of right increases by 1
			p->SetmBF(-1); p = p->GetRight();
		}
		else {//height of left increases by 1
			p->SetmBF(1); p = p->GetLeft();
		}
	}
	if (a->GetmBF() == 0 || (a->GetmBF() + d) == 0) {//tree still balanced
		a->SetmBF(a->GetmBF() + d); return true;
	}
	//tree unbalanced, determine rotation type
	if (d == 1) {//left imbalance
		if (b->GetmBF() == 1) {//rotation type LL
			a->SetLeft(b->GetRight());
			b->SetRight(a); a->SetmBF(0); b->SetmBF(0);
			rootSub=b;//b is th new root of the subtree
		}
		else {//rotation type LR
			c = b->GetRight();
			b->SetRight(c->GetLeft());
			a->SetLeft(c->GetRight());
			c->SetLeft(b);
			c->SetRight(a);
			switch(c->GetmBF())
			{
			case 0:
				b->SetmBF(0); a->SetmBF(0);
				break;
			case 1:
				a->SetmBF(-1); b->SetmBF(0);
				break;
			case -1:
				b->SetmBF(1); a->SetmBF(0);
				break;
			default:
				break;
			}
			c->SetmBF(0); rootSub = c;//c is the now root of the subtree
		}//end of LR
	}//end of left imbalance
	else {//right imbalance: this is symmetric to left imbalance
		if (b->GetmBF() == -1) {//rotation type RR
			a->SetRight(b->GetLeft());
			b->SetLeft(a);
			a->SetmBF(0);
			b->SetmBF(0);
			rootSub = b;//b is the new root of the subtree
		}
		else {//rotation type RL
			c = b->GetLeft();
			b->SetLeft(c->GetRight());
			a->SetRight(c->GetLeft());
			c->SetRight(b);
			c->SetLeft(a);
			switch (c->GetmBF())
			{
			case 0:
				b->SetmBF(0); a->SetmBF(0);
				break;
			case 1:
				b->SetmBF(-1); a->SetmBF(0);
				break;
			case -1:
				a->SetmBF(1); b->SetmBF(0);
				break;
			default:
				break;
			}
			c->SetmBF(0); rootSub = c;//c is the new root of the subtree
		}//end of RL
	}
	//Subtree with root b has been rebalanced
	if (pa == NULL)root = rootSub;
	else if (a == pa->GetLeft())pa->SetLeft(rootSub);
	else pa->SetRight(rootSub);
	return true;
}//end of AVL

CityData * AVLTree::Delete(int num)
{
	if (root == NULL) {//no delete value
		return NULL;
	}
	
	return NULL;
}

CityData * AVLTree::Search(int num)
{
	inorder2(root, num);//call inorder to find num
	return NULL;
}

CityData * AVLTree::Search2(int num)
{
	inorder22(root, num);//call inorder to find num and success check
	return NULL;
}

bool AVLTree::Print()
{
	inorder(root);//call inorder to print avltree
	return true;
}

void AVLTree::numberinorder(AVLNode*a, stack<CityData*>stack1) {
	if (a != nullptr) {
		numberinorder(a->GetLeft(),stack1);//call function about left node
		nodenumber += 1;//node number check
		stack1.push(a->GetCityData());//give data to node
		numberinorder(a->GetRight(),stack1);//call function about right node
	}
}
void AVLTree::inorder(AVLNode * a) {
	if (a != nullptr) {
		inorder(a->GetLeft());//call function about left node
		*flog << "(" << a->GetCityData()->GetLocationId() << ", " << (a->GetCityData()->Getname()) << ", " << a->GetCityData()->Getcountry() << ")" << endl;
		//put data to txt file
		inorder(a->GetRight());//call function about right node
	}
}
void AVLTree::inorder22(AVLNode * a, int i) {
	if (a != nullptr) {
		inorder22(a->GetLeft(), i);//call function about left node
		if (a->GetCityData()->GetLocationId() == i) {
			searched2 = 1;//success check
		}
		inorder22(a->GetRight(), i);//call function about right node
	}
}

void AVLTree::inorder2(AVLNode * a, int i) {
	if (a != nullptr) {
		inorder2(a->GetLeft(), i);//call function about left node
		if (a->GetCityData()->GetLocationId() == i) {
			*flog << "(" << a->GetCityData()->GetLocationId() << ", " << a->GetCityData()->Getname() << ", " << a->GetCityData()->Getcountry() << ")" << endl;
			searched = 1;//success check and write values to txt file
		}
		inorder2(a->GetRight(), i);//call function about right node
	}
}

void AVLTree::inorder3(AVLNode * a, int i) {
	if (a != nullptr) {
		inorder2(a->GetLeft(), i);//call function about left node
		if (a->GetCityData()->GetLocationId() == i) {
			delsearch = a->GetCityData()->Getname();//delvalue check
		}
		inorder2(a->GetRight(), i);//call function about right node
	}
}
