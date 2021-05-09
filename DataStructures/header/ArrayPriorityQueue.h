#pragma once
#include <iostream>

template<class T>
class ArrayPriorityQueue
{
  public:
	struct Node
	{
		int data;
		T key;
	};
  
  private:
	const std::string ERROR_FULL = "Queue is full";
	const std::string ERROR_EMPTY = "Queue is empty";
	const std::string ERROR_INVALID_KEY = "Invalid key";
	const std::string ERROR_INVALID_ARG = "Argument invalid";
	int m_Capacity, m_Size;
	Node *m_Arr;
	
	bool isValidVertex(int i_Vertex) const
	{
		return i_Vertex > 0 && i_Vertex <= m_Capacity;
	}
  
  public:
	ArrayPriorityQueue() = delete;
	ArrayPriorityQueue(const ArrayPriorityQueue &org) = default;
	ArrayPriorityQueue &operator=(const ArrayPriorityQueue &org) = default;
	
	~ArrayPriorityQueue()
	{
		delete[] m_Arr;
	}
	
	ArrayPriorityQueue(int i_Size)
	{
		if(i_Size == 0)
		{
			throw std::invalid_argument(ERROR_INVALID_ARG);
		}
		
		m_Capacity = i_Size + 1;
		m_Size = 0;
		m_Arr = new Node[m_Capacity];
		
		for(int i = 0; i < m_Capacity; i++)
		{
			m_Arr[i].data = i;
			m_Arr[i].key = INT_MAX;
		}
	}
	
	bool IsEmpty() const
	{
		return m_Size == 0;
	}
	
	int DeleteMin()
	{
		if(IsEmpty())
		{
			throw std::out_of_range(ERROR_EMPTY);
		}
		
		int minVertex = m_Arr[0].data;
		T minKey = m_Arr[0].key;
		
		for(int i = 1; i < m_Capacity; i++)
		{
			if(m_Arr[i].key < minKey)
			{
				minKey = m_Arr[i].key;
				minVertex = i;
			}
		}
		
		m_Size--;
		m_Arr[minVertex].data = m_Capacity + 1;
		m_Arr[minVertex].key = INT_MAX;
		
		return minVertex;
	}
	
	void DecreaseKey(int i_Vertex, T i_NewKey)
	{
		if(!isValidVertex(i_Vertex))
		{
			throw std::invalid_argument(ERROR_INVALID_KEY);
		}
		
		m_Arr[i_Vertex].key = i_NewKey;
	}
	
	int GetSize() const
	{
		return m_Size;
	}
	
	void Insert(const Node &i_NewNode)
	{
		if(m_Size == m_Capacity)
		{
			throw std::out_of_range(ERROR_FULL);
		}
		
		if(!isValidVertex(i_NewNode.data))
		{
			throw std::invalid_argument(ERROR_INVALID_KEY);
		}
		
		m_Arr[i_NewNode.data].data = i_NewNode.data;
		m_Arr[i_NewNode.data].key = i_NewNode.key;
		m_Size++;
	}
};

