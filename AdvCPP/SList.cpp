#include "SList.h"

using namespace std;

template <typename T>
class SList
{
	// Forward declaration
	class Node;

public:
	SList<T>() noexcept
	{
		// caution: static members can't be
		// initialized by initializer list
		m_spRoot = nullptr;
	}

	class Iterator;

	// begin iterator
	Iterator begin()
	{
		return Iterator(m_spRoot);
	}

	// end iterator
	Iterator end()
	{
		return Iterator(nullptr);
	}

	// Adds data to the end of list
	void push_back(T data);
	void Traverse();

	class Iterator
	{
	public:
		Iterator() noexcept :
			m_pCurrentNode(m_spRoot) { }

		Iterator(const Node* pNode) noexcept :
			m_pCurrentNode(pNode) { }

		// == operator
		Iterator& operator=(Node* pNode)
		{
			this->m_pCurrentNode = pNode;
			return *this;
		}

		// Prefix ++ overload
		Iterator& operator++()
		{
			if (m_pCurrentNode)
				m_pCurrentNode = m_pCurrentNode->pNext;
			return *this;
		}

		// Postfix ++ overload
		Iterator operator++(int)
		{
			Iterator iterator = *this;
			++* this;
			return iterator;
		}

		// != operator
		bool operator!=(const Iterator& iterator)
		{
			return m_pCurrentNode != iterator.m_pCurrentNode;
		}

		// * operator
		T operator*()
		{
			return m_pCurrentNode->data;
		}

	private:
		const Node* m_pCurrentNode;
	};

private:

	class Node
	{
		T data;
		Node* pNext;

		friend class SList;
	};

	// Create a new Node
	Node* GetNode(T data)
	{
		Node* pNewNode = new Node;
		pNewNode->data = data;
		pNewNode->pNext = nullptr;

		return pNewNode;
	}

	// Return by reference so that it can be used in
	// left hand side of the assignment expression
	Node*& GetRootNode()
	{
		return m_spRoot;
	}

	static Node* m_spRoot;
};

template <typename T>
typename SList<T>::Node* SList<T>::m_spRoot = nullptr;

// pushback
template <typename T>
void SList<T>::push_back(T data)
{
	Node* pTemp = GetNode(data);
	if (!GetRootNode())
	{
		GetRootNode() = pTemp;
	}
	else
	{
		Node* pCrawler = GetRootNode();
		while (pCrawler->pNext)
		{
			pCrawler = pCrawler->pNext;
		}

		pCrawler->pNext = pTemp;
	}
}

// traverse
template <typename T>
void SList<T>::Traverse()
{
	Node* pCrawler = GetRootNode();

	while (pCrawler)
	{
		cout << pCrawler->data << " ";
		pCrawler = pCrawler->pNext;
	}

	cout << endl;
}

//Driver program
int main()
{
	// Creo la mia lista
	SList<int> list;

	// Utilizzare il pushback per popolare la mia lista
	list.push_back(15);
	list.push_back(43);
	list.push_back(25);

	// Posso poi utilizzare o il metodo Traverse
	// o utilizzare l'iteratore
	return 0;
}
