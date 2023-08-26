#pragma once

#include "BinarySearchTree.h"

#include <iostream>
#include <string>				//head file for string

class TransferWindowManager
{
private:
	int m_budget;

	BinarySearchTree fwBST;
	BinarySearchTree mfBST;
	BinarySearchTree dfBST;
	BinarySearchTree gkBST;
	SoccerPlayerData fw2;		//add variable to save in soccer team
	SoccerPlayerData mf2;
	SoccerPlayerData df2;
	SoccerPlayerData gk2;

public:

	struct SoccerTeam
	{
		SoccerPlayerData fw;
		SoccerPlayerData mf;
		SoccerPlayerData df;
		SoccerPlayerData gk;

		int sum_transfer_fee;
		int sum_ability;

		SoccerTeam();
		SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk);
		friend std::ostream& operator<<(std::ostream& os, const SoccerTeam& team);

	};

	TransferWindowManager(std::string file_dir, int budget);

	friend std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager);

	SoccerTeam getBestTeam();

	void inorder(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best);//function to read every binarysearchtree and compare their ability and fee 
	void inorder2(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best);
	void inorder3(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best);
	void inorder4(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best);
	void cmpbud(SoccerPlayerData* a, SoccerPlayerData* b, SoccerPlayerData* c, SoccerPlayerData* d, int * best);

};
 

