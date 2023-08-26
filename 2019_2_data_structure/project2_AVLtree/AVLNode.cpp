#include "AVLNode.h"

AVLNode::AVLNode()
{
}

AVLNode::~AVLNode()
{
}

CityData * AVLNode::GetCityData()//get citydata
{
	return pCityData;
}

AVLNode * AVLNode::GetLeft()//get left node
{
	return pLeft;
}

AVLNode * AVLNode::GetRight()//get right node
{
	return pRight;
}

int AVLNode::GetmBF()//get mbf value
{
	return mBF;
}

void AVLNode::SetCityData(CityData * node)//give citydata to avlnode
{
	this->pCityData = node;
}

void AVLNode::SetLeft(AVLNode * node)//give leftnode to avlnode
{
	this->pLeft = node;
}

void AVLNode::SetRight(AVLNode * node)//give rightnode to alvnode
{
	this->pRight = node;
}

void AVLNode::SetmBF(int n)//give setmBF
{
	this->mBF = n;
}

