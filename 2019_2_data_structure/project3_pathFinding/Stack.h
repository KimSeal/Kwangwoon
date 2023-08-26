#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
    class StackNode
    {
    public:
        T Data;											//data in stack
        StackNode* pNext;								//connect node and next node
        StackNode(T data) : Data(data), pNext(NULL) {}
	};

	private:
		StackNode* m_pTop;								//head node

	public:
		Stack() {										//when stack is maked, top is null
			m_pTop(NULL);
		};
		~Stack() {										//delete nodes until top is poped
			while (m_pTop) {
				Pop();
			}
		}


		void Push(T data) {								//push data in stack
			StackNode* newNode = new StackNode(data);
			if (IsEmpty()) newNode->pNext = m_pTop;
			m_pTop = newNode;
		}

		void Pop() {									//delete last data in stack
			StackNode* delNode = m_pTop;
			m_pTop = delNode->pNext;
			delete delNode;
			delNode = NULL;
		}

		T Top() {										//get last data in stack
			return m_pTop->Data; 
		}
 
		bool IsEmpty() {								//empty check
			if (m_pTop) {
				return false;
			}
			else {
				return true;
			}
		}
};

#endif