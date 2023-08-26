#include "Edge.h"

Edge::Edge() : m_key(0), m_weight(0), m_pNext(NULL) {}
Edge::Edge(int key, int weight) : m_key(key), m_weight(weight), m_pNext(NULL) {}

void Edge::SetNext(Edge* pNext) { 
	m_pNext = pNext; 
}	//set next edge

int Edge::GetKey() const { 
	return m_key; 
}	//get key
int Edge::GetWeight() const { 
	return m_weight; 
}	//get weight
Edge* Edge::GetNext() const {
	return m_pNext; 
}	//get next edge