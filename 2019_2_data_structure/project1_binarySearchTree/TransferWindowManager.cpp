#include "TransferWindowManager.h"
#include<iostream>
#include <fstream>
#include <string>
#include <vector> //vector

void TransferWindowManager::inorder(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best) {//print for fw
	if (a) {
		// if pointer is not null
		inorder(a->m_left, b, c, d, best);
		inorder2(a, b, c, d, best);
		inorder(a->m_right, b, c, d, best);
	}
}
void TransferWindowManager::inorder2(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best) {//print for mf
	if (b) {
		// if pointer is not null
		inorder2(a, b->m_left, c, d, best);
		inorder3(a, b, c, d, best);
		inorder2(a, b->m_right, c, d, best);
	}
}
void TransferWindowManager::inorder3(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int * best) {//print for df
	if (c) {
		// if pointer is not null
		inorder3(a, b, c->m_left, d, best);
		inorder4(a, b, c, d, best);
		inorder3(a, b, c->m_right, d, best);
	}
}
void TransferWindowManager::inorder4(TreeNode* a, TreeNode*b, TreeNode*c, TreeNode*d, int *best) {//print for gk
	if (d) {
		// if pointer is not null
		inorder4(a, b, c, d->m_left, best);
		cmpbud(&(a->m_data), &(b->m_data), &(c->m_data), &(d->m_data), best);					 //compare check
		inorder4(a, b, c, d->m_right, best);
	}
}
void TransferWindowManager::cmpbud(SoccerPlayerData* a, SoccerPlayerData* b, SoccerPlayerData* c, SoccerPlayerData* d, int * best) {
	//compare budget and result about 'ability added'
	if (m_budget >= ((a->m_transfer_fee) + (b->m_transfer_fee) + (c->m_transfer_fee) + (d->m_transfer_fee))) {//budget check
		if (*best < ((a->m_ability) + (b->m_ability) + (c->m_ability) + (d->m_ability))) {					  //now best check
			*best = (a->m_ability) + (b->m_ability) + (c->m_ability) + (d->m_ability);
			this->fw2 = *a;
			this->mf2 = *b;
			this->df2 = *c;
			this->gk2 = *d;
		}
	}
}
TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)
{
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager::SoccerTeam& team) //print soccerteam
{
	os << team.fw << std::endl;
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}


TransferWindowManager::TransferWindowManager(std::string file_dir, int budget)
{
	m_budget = budget;

	std::ifstream in(file_dir);		//read file
	std::string line;				//input file's string in line
	
	std::string i_name;				//variable to save each value
	std::string i_position;
	std::string power;
	std::string money;
	int i_power;
	int i_money;
	int i = 0;

	while (std::getline(in, line))	//read file by each line
	{
		i = 0;						//variable to check type of read variables
		int nPos = 0;
		std::vector<std::string> tokens;
		while ((nPos = line.find(",", 0)) != std::string::npos) {
			tokens.push_back(line.substr(0, nPos));
			line = line.substr(nPos + 2);
		}
		tokens.push_back(line);
		for (std::string token : tokens) {
			if (i == 0) {			//name check
				i_name = token;
			}
			else if (i == 1) {		//position check
				i_position = token;
			}
			else if (i == 2) {		//money check
				money = token;
				i_money = atoi(money.c_str());//change to int
			}
			else if (i == 3) {		//ability check
				power = token;
				i_power = atoi(power.c_str());//change to int
			}
			i++;
		}
		SoccerPlayerData a(i_name, i_position, i_money, i_power);//save data of soccerplayer
		if (!i_position.compare("Forward")) {//check position and put their data in approriate list
			fwBST.insert(a);
		}
		else if (!i_position.compare("Midfielder")) {
			mfBST.insert(a);
		}
		else if (!i_position.compare("Defender")) {
			dfBST.insert(a);
		}
		else if (!i_position.compare("Goalkeeper")) {
			gkBST.insert(a);
		}
		//Fill in the code to initialize 4 Binary Search Trees(fw, mf, df, gk)

	}
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager)//for print
{
	os << "********Forward List********" << std::endl;
	os << manager.fwBST;
	os << "****************************" << std::endl;

	os << "********Midflder List********" << std::endl;
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	os << "********Defender List********" << std::endl;
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	os << "********Goalkeeper List********" << std::endl;
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}

TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam() //make best team
{
	SoccerTeam best_team;											   //variable about best team

	TreeNode * cur_fwBST = fwBST.m_root;							   //variable to save Binary search tree
	TreeNode * cur_mfBST = mfBST.m_root;
	TreeNode * cur_dfBST = dfBST.m_root;
	TreeNode * cur_gkBST = gkBST.m_root;
	int best = 0;													  //initialize ability add value
	inorder(cur_fwBST, cur_mfBST, cur_dfBST, cur_gkBST, &best);		  //do inorder
	//Fill in the code to search the best_team from 4 BSTs
	//The datas for best team must be stored in the variable best_team.
	//*best team means the most powerful team that is defined in the project introduction file. 
	
	SoccerTeam best_team2(fw2,mf2,df2,gk2);							  //put values in soccerTeam
	best_team = best_team2;
	fwBST.deletion(best_team.fw.m_ability);							  //delete soccer player in best team
	mfBST.deletion(best_team.mf.m_ability);
	dfBST.deletion(best_team.df.m_ability);
	gkBST.deletion(best_team.gk.m_ability);

	return best_team;
} 
 
