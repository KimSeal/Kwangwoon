#pragma once

#include "SoccerPlayerData.h"
#include <iostream>

class TreeNode
{
	friend class BinarySearchTree;		//friend to use other function's elements 
	friend class TransferWindowManager;
private:
	SoccerPlayerData m_data;			//information in node
	TreeNode* m_left;					//left node
	TreeNode* m_right;					//right node
public:
	TreeNode() :m_left(NULL), m_right(NULL) {}
	~TreeNode() { }
	TreeNode(SoccerPlayerData & data, TreeNode* left = NULL, TreeNode* right = NULL)
	{
		this->m_data = data;
		this->m_left = left;
		this->m_right = right;
	}

	TreeNode* getLeftNode() const { return m_left; }
	TreeNode* getRightNode() const { return m_right; }

	friend std::ostream& operator<<(std::ostream& os, const TreeNode* node) //function to read
	{
		if (node != NULL)
			os << node->m_data;
		return os;
	}
};
 
