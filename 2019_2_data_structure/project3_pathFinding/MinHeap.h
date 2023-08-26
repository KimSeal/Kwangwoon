#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
	// array for the elements which should be heap-sorted
	std::vector<std::pair<TKey, TValue>> m_vec;

public:
	MinHeap() {
		m_vec.push_back(make_pair(999999, 999999));//give infinity value
	}
	~MinHeap() {
		m_vec.clear();//delete them
	}
	
	void Push(TKey key, TValue value) {
		m_vec.push_back(make_pair(key, value));						//push values
		if (m_vec.size() > 2) Heapify((m_vec.size() - 1) / 2);		//size check and sort them
	};

	void Pop() {
		if (m_vec.size() == 1) return;		//size check
		if (m_vec.size() == 2)
		{
			m_vec.pop_back();				//delete minimum value
			return;
		}

		// Delete
		m_vec.at(1).first = 0;				//delete contents
		m_vec.at(1).second = 0;

		pair<TKey, TValue> poped = m_vec.back();
		m_vec.pop_back();				// Pop
		int parent = 1, child = 2;		// Parent, child

		while (child <= m_vec.size() - 1)
		{
			// Set child to smaller one
			if (child < m_vec.size() - 1 && m_vec.at(child).second > m_vec.at(child + 1).second) child++;
			// Check last one
			if (poped.second <= m_vec[child].second) break;

			m_vec[parent] = m_vec[child];	//change between parent and chile(downward)
			parent = child;					
			child *= 2;						//mul child
		}

		m_vec.at(parent) = poped;
	}
	
	std::pair<TKey, TValue> Top() {
		if (!IsEmpty()) {
			return m_vec.at(1);			//return first value
		}
	};

	std::pair<TKey, TValue> Get(TValue target){
		for (int i = 1; m_vec.size() > 1; i++) {
			if (m_vec.at(i).second == target) {		//find value
				return m_vec.at(i);					//and return that
			}
		}
	}
	
	bool IsEmpty() {
		if (m_vec.size() == 1) {//size check
			return true;		//size = 1 is empty
		}
		else {
			return false;
		}
	};

	void DecKey(TValue target, TKey newKey) {
		int index = 0;			// Index
		pair<TKey, TValue> found = Get(target);//make variable use target

		for (int i = 1; i < m_vec.size(); i++)
		{
			if (m_vec[i].first == found.first)	//find right value
			{
				m_vec.at(i).first = target;		// Key update
				index = i;						// Get index
			}
		}
	}

private:
    /// <summary>
    /// heap-sort, heapify.<para/>
    /// this function can be called recursively
    /// </summary>
    void Heapify(int index) {
		int parent = index;		//parent
		int left = parent * 2;	//left child
		int right = left + 1;	//right child

		pair<TKey, TValue> temp;	//temporary pair

		if (m_vec.size() == right)	//Right is not Exist
		{
			if (m_vec[left].second < m_vec[parent].second)	//left is smaller than right
			{
				// Swap
				temp = m_vec[parent];
				m_vec[parent] = m_vec[left];
				m_vec[left] = temp;
			}
		}
		else						//right ia exist
		{
			if (m_vec[left].second < m_vec[right].second)
			{
				if (m_vec[left].second < m_vec[parent].second)	//left is smaller than parent
				{
					temp = m_vec[left];				//swap left and parent
					m_vec[left] = m_vec[parent];
					m_vec[parent] = temp;
				}
			}
			else
			{
				if (m_vec[right].second < m_vec[parent].second)	// right is smaller than parent
				{
					temp = m_vec[right];			//swap right and parent
					m_vec[right] = m_vec[parent];
					m_vec[parent] = temp;
				}
			}
		}
		if (index == 1) {
			return;	//end heapify
		}
		index /= 2;				//check parent
		Heapify(index);			//recursive
	}
};

#endif
