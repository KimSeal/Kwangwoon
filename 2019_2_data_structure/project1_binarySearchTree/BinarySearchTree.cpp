#include "BinarySearchTree.h"

BinarySearchTree::~BinarySearchTree() {
	FreeTree(m_root);							//call function
}
void BinarySearchTree::FreeTree(TreeNode* a) {  //function to delete
	if (a) {
		if (a->getLeftNode()) {					//go left
			FreeTree(a->getLeftNode());
		}

		if (a->getRightNode()) {				//go right
			FreeTree(a->getRightNode());
		}
		delete(a);								//delete current node
	}
}
void BinarySearchTree::insert(SoccerPlayerData& data) {//function to insert
	TreeNode * p = m_root, *pp = NULL;
	while (p) {
		pp = p;
		if (data.m_ability < p->m_data.m_ability) p=p->m_left;		//go left
		else if (data.m_ability > p->m_data.m_ability) p=p->m_right;//go right
		else { p->m_data.m_name = data.m_name;						//put value
		p->m_data.m_position = data.m_position;	
		p->m_data.m_transfer_fee = data.m_transfer_fee;
		return;
		}
	}
	p = new TreeNode(data);											//make place to save data
	if (m_root != NULL) {
		if (data.m_ability < pp->m_data.m_ability) pp->m_left = p;	//compare ability and put value in left or right
		else pp->m_right = p;
	}
	else { m_root = p; };
}
void BinarySearchTree::deletion(int ability) {						//delete node
	TreeNode* checknode = m_root, * delnode = 0;
	while (checknode && ability != checknode->m_data.m_ability) {	//find change node
		delnode=checknode;
		if ((checknode->m_data.m_ability) > ability) {				//compare their node's ability
			checknode = checknode->m_left;
		}
		else if ((checknode->m_data.m_ability) < ability) {
			checknode = checknode->m_right;
		}
	}
	if (checknode == 0)return;

	if (checknode->m_left == 0 && checknode->m_right == 0) {		//p is leaf
		if (delnode == 0) m_root = 0;
		else if (delnode->m_left == checknode) delnode->m_left = 0;
		else delnode->m_right = 0;
		delete checknode; return;
	}
	else if(checknode->m_left==0) {									//p have only right node
		if (delnode == 0)m_root = checknode->m_right;
		else if (delnode->m_left == checknode) delnode->m_left=checknode->m_right;
		else delnode->m_right = checknode->m_right;
		delete checknode; return;
	}
	else if (checknode->m_right == 0) {								//p have only left node
		if (delnode == 0)m_root = checknode->m_left;
		else if (delnode->m_left == checknode)delnode->m_left = checknode->m_left;
		else delnode->m_right = checknode->m_left;
		delete checknode; return;
	}
	else {															//p have left and right node
		TreeNode*prevprev = checknode, *prev = checknode->m_left, *curr = checknode->m_left->m_right;
		while (curr) {
			prevprev = prev;
			prev = curr;
			curr = curr->m_right;
		}
	}
}
 
