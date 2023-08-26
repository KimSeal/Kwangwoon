#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define DFS_FIRST_PATH

Graph::Graph()
{
    // TODO: implement
	m_pVHead = NULL;
	m_vSize = 0;
}
Graph::~Graph()
{
    // TODO: implement
	Clear();
}

void Graph::Clear()
{
	Vertex* delVer = m_pVHead;
	while (delVer)
	{
		m_pVHead = m_pVHead->GetNext();	//move head
		delete delVer;					//delete
		delVer = m_pVHead;				//get next head vertex
		m_vSize--;						//size minus 1
	}
}

void Graph::AddVertex(int vertexKey)
{
	Vertex* curVer = m_pVHead;				//head check
	Vertex* newVer = new Vertex(vertexKey);	//new vertex

	if (curVer)
	{
		while (curVer->GetNext()) curVer = curVer->GetNext();	//move
		curVer->SetNext(newVer);								//add new vertex
	}
	else m_pVHead = newVer;	//if head isn't exist

	m_vSize++;	//size plus 1
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
	Vertex* curVer = m_pVHead;
	while (curVer && curVer->GetKey() != startVertexKey){
		curVer = curVer->GetNext();	//find edge
	}
	if (curVer) curVer->AddEdge(endVertexKey, weight);	//add edge
}

Vertex* Graph::FindVertex(int key)
{
	Vertex* curVer = m_pVHead;
	while (curVer && curVer->GetKey() != key) {//find using ket
		curVer = curVer->GetNext();	
	}
	return curVer;	//found vertex
}
int Graph::Size() const {					//take size
	return m_vSize; 
}

bool Graph::IsNegativeEdge()				//negative edge check
{
	Vertex* curVer = m_pVHead;
	Edge* curEdge = curVer->GetHeadOfEdge();
	while (curVer)
	{
		while (curEdge)
		{
			if (curEdge->GetWeight() < 0) return true;	//check negative edge
			curEdge = curEdge->GetNext();				//go to next
		}
		curVer = curVer->GetNext();						//go to next
	}
	return false;										//no negative edge
}

void Graph::Print(std::ofstream& fout)
{
	fout << "===== PRINT =====" << endl;
	for (int i = 0; i < m_vSize; i++)
	{
		Vertex* curVer = FindVertex(i);				//take vertex
		Edge* curEdge = curVer->GetHeadOfEdge();	//head edge
		for (int j = 0; j < m_vSize; j++)
		{
			if (curEdge && j == curEdge->GetKey())	//connect
			{
				fout << curEdge->GetWeight() << " ";//print weight
				curEdge = curEdge->GetNext();		//go to next
			}
			else fout << "0 ";						//no connected
		}
		fout << endl;								//line change
	}
	fout << "===============" << endl << endl;
}


std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	int* back = new int[m_vSize];	//prev array
	int i, key = startVertexKey;	//give input value

	vector<int> path;
	set<int> temp;					// Temporary set
	set<pair<int, int>>* min = new set<pair<int, int>>[m_vSize];
	for (i = 0; i < m_vSize; i++) { //initialize them using input value
		min[i].insert(make_pair(IN_FINITY, startVertexKey));
	}
	min[startVertexKey].erase(min[startVertexKey].begin());		//pop set's erase
	min[startVertexKey].insert(make_pair(0, startVertexKey));	//push information
	temp.insert(startVertexKey);								//insert start key

	while (!temp.empty())
	{
		key = *temp.begin();									//key check
		back[key] = min[key].begin()->second;
		temp.erase(key);										//find and delete key
		Edge* curEdge = FindVertex(key)->GetHeadOfEdge();

		while (curEdge)
		{
			if (min[curEdge->GetKey()].begin()->first > min[key].begin()->first + curEdge->GetWeight())			//if min[key]'s distance is bigger than min[key]'s distance + length
			{
				temp.insert(curEdge->GetKey());																	//insert to temp
				min[curEdge->GetKey()].insert(make_pair(min[key].begin()->first + curEdge->GetWeight(), key));	//insert to min set
			}
			curEdge = curEdge->GetNext();	//go to next
		}
	}

	for (i = endVertexKey; back[i] != i; i = back[i]) {
		path.insert(path.begin(), i);
	}
	path.insert(path.begin(), i);											//store last road
	path.insert(path.end(), min[endVertexKey].begin()->first);				//store weight

	delete[] min;
	delete back;
	return path;
}

std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	vector<int> dist(m_vSize, IN_FINITY);	//initialize infinity vector
	vector<int> path;
	int* back = new int[m_vSize];
	Vertex* curVer = FindVertex(startVertexKey);
	dist[startVertexKey] = 0;

	for (int i = 0; i < m_vSize; i++) { //initialize them no check value
		back[i] = -1; //-1 is not check
	}				
	for (Edge* curEdge = curVer->GetHeadOfEdge(); curEdge; curEdge = curEdge->GetNext())
	{
		dist[curEdge->GetKey()] = curEdge->GetWeight();			//initialize weight
		back[curEdge->GetKey()] = startVertexKey;
	}

	for (int i = 2; i <= m_vSize; i++)							//check negative cycle
	{
		for (curVer = m_pVHead; curVer; curVer = curVer->GetNext())	//check all edge
		{
			for (Edge* curEdge = curVer->GetHeadOfEdge(); curEdge; curEdge = curEdge->GetNext())
			{
				if (dist[curEdge->GetKey()] > dist[curVer->GetKey()] + curEdge->GetWeight())		//min value did
				{
					if (i == m_vSize)						//negative cycle did
					{
						dist.clear();
						return dist;						//zero size vector
					}
					back[curEdge->GetKey()] = curVer->GetKey();			//index(Vertex)
					dist[curEdge->GetKey()] = dist[curVer->GetKey()] + curEdge->GetWeight();	//change distance
				}
			}
		}
	}
	for (int i = endVertexKey; i != -1; i = back[i]) {
		path.insert(path.begin(), i);
	}
	path.insert(path.end(), dist.at(endVertexKey));				//Save weight
	delete back;//delete used value
	return path;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	MinHeap<int, int> heap;			//minheap
	int* back = new int[m_vSize];	//prev array
	int i, key = startVertexKey;

	vector<int> path;
	set<int> temp;
	set<pair<int, int>>* min = new set<pair<int, int>>[m_vSize];
	for (i = 0; i < m_vSize; i++) min[i].insert(make_pair(IN_FINITY, startVertexKey));	//initialize using key

	min[startVertexKey].erase(min[startVertexKey].begin());			//pop set erase
	min[startVertexKey].insert(make_pair(0, startVertexKey));		//push length, start key
	temp.insert(startVertexKey);									//insert start key

	while (!temp.empty())
	{
		key = *temp.begin();									//key check
		back[key] = min[key].begin()->second;
		temp.erase(key);										//find and delete key
		Edge* curEdge = FindVertex(key)->GetHeadOfEdge();

		while (curEdge)
		{
			if (min[curEdge->GetKey()].begin()->first > min[key].begin()->first + curEdge->GetWeight())		//min[key]'s distance is bigger than min[key]'s distance + length
			{
				temp.insert(curEdge->GetKey());				//insert to temp
				min[curEdge->GetKey()].insert(make_pair(min[key].begin()->first + curEdge->GetWeight(), key));	//insert to min
			}
			curEdge = curEdge->GetNext();	//move
		}
	}

	for (i = endVertexKey; back[i] != i; i = back[i]) {
		path.insert(path.begin(), i);
	}
	path.insert(path.begin(), i);											//save last road
	path.insert(path.end(), min[endVertexKey].begin()->first);				//save weight

	delete[] min;
	delete back;
	heap.~MinHeap();
	return path;						//return path
}

std::vector<vector<int> > Graph::FindShortestPathFloyd()
{
	vector<vector<int>> arr, temp;		//two vector present double linked list
	int i = 0, j = 0, k = 0;			//iterator
	for (Vertex* curVer = m_pVHead; i < m_vSize; i++, curVer = curVer->GetNext())
	{
		temp.push_back(vector<int>());				//push empty vector
		Edge* curEdge = curVer->GetHeadOfEdge();
		for (j = 0; j < m_vSize; j++)
		{
			while (curEdge && curEdge->GetKey() < j) curEdge = curEdge->GetNext();	//move edge
			if (j == i) temp.back().push_back(0);		// Same node
			else if (curEdge && curEdge->GetKey() == j) temp.back().push_back(curEdge->GetWeight());	//push weight
			else temp.back().push_back(IN_FINITY);		//push infinity value to vector
		}
	}
	arr = temp;							//path vector copy initialize
	for (k = 0; k < m_vSize; k++)
	{
		for (i = 0; i < m_vSize; i++)
			for (j = 0; j < m_vSize; j++)
				// Assign smaller one
				arr[i][j] = (arr[i][j] > temp[i][k] + temp[k][j]) ? temp[i][k] + temp[k][j] : arr[i][j];

		temp = arr;						//copy path
	}
	return arr;
}