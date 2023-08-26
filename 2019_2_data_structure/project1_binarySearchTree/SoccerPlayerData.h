#pragma once

#include <string>						//string head file
#include <iostream>
class SoccerPlayerData					//class for soccer player data
{
	friend class TreeNode;				//friend class for share their elements
	friend class BinarySearchTree;
	friend class TransferWindowManager;
private:
	std::string m_name;					//varialbe of name
	std::string m_position;				//variable of position

	int m_transfer_fee;					//variable of money
	int m_ability;						//varialbe of ability

public:
	SoccerPlayerData() { }
	SoccerPlayerData(std::string name, std::string position, int transfer_fee, int ability)//constructor with putting value
		:
		m_name(name),
		m_position(position),
		m_transfer_fee(transfer_fee),
		m_ability(ability)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const SoccerPlayerData& node) {//print thier elements
		os << "(node.m_name: " << node.m_name << "), "
			<< "(node.m_position: " << node.m_position << "), "
			<< "(node.m_transfer_fee: " << node.m_transfer_fee << "), "
			<< "(node.m_ability: " << node.m_ability << ")";
		return os;
	}
};
