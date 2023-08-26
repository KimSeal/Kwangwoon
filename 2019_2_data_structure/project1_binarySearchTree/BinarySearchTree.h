#pragma once

#include "TreeNode.h"
#include <iostream>

class BinarySearchTree					//for BinarySearchTree
{
	friend class TransferWindowManager;
private:
	TreeNode * m_root;					//treenode about BinarySearchTree

public:
	BinarySearchTree() { m_root = NULL; }
	~BinarySearchTree();
	void FreeTree(TreeNode*a);
	void insert(SoccerPlayerData& data);
	void deletion(int ability); // ability = key
	
	const void Inorder(std::ostream &out, const TreeNode*tree) const { //print inorder system 
		if (tree != nullptr) {										   //check nullptr
			Inorder(out, tree->m_left);								   //left check
			out << tree << std::endl;								   //print self
			Inorder(out, tree->m_right);							   //right check
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {
		tree.Inorder(os, tree.m_root);								  //call binarysearchtree
		return os;													  //return os
	}
};
 
