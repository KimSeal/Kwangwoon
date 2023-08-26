#include "Vertex.h"

Vertex::Vertex() : m_key(0), m_size(0), m_pEHead(NULL), m_pNext(NULL) {}
Vertex::Vertex(int key) : m_key(key), m_size(0), m_pEHead(NULL), m_pNext(NULL) {}
Vertex::~Vertex() {							//clear them
	if (m_pEHead) Clear();
}

void Vertex::SetNext(Vertex* pNext) { m_pNext = pNext; }	//put next vertex

int Vertex::GetKey() const { return m_key; }				//key
Vertex* Vertex::GetNext() const { return m_pNext; }			//next vertex
Edge* Vertex::GetHeadOfEdge() const { return m_pEHead; }	//first edge
int Vertex::Size() const { return m_size; }	// Get size

void Vertex::AddEdge(int edgeKey, int weight)
{
	if (weight == 0) return;	//check no connected

	Edge* newed = new Edge(edgeKey, weight);
	Edge* cur = m_pEHead;


	if (cur){
		while (cur->GetNext()) {
			cur = cur->GetNext();	//go to next
		}
		cur->SetNext(newed);	//new edge
	}
	else m_pEHead = newed;		//if head is not exist
	m_size++;	// Size up
}

void Vertex::Clear()
{
	Edge* del = m_pEHead;
	while (del)
	{
		m_pEHead = m_pEHead->GetNext();	// Move head
		delete del;						// Delete
		del = m_pEHead;					// Get next head edge
		m_size--;						// Size down
	}
}