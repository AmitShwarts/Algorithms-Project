#pragma once
#include <iostream>

template<class T>
class MinHeap
{
  public:
	struct Node
	{
		T data;
		int key;
	};
  
  private:
	const std::string ERROR_FULL_HEAP = "Heap is full";
	const std::string ERROR_EMPTY_HEAP = "Heap is empty";
	const std::string ERROR_INVALID_KEY = "Invalid key";
	int m_Capacity, m_Size;
	Node *m_Arr;
	bool m_NeedToDeAllocate;
	
	int getParent(int i_Size) const
	{
		return i_Size / 2;
	}
	
	int getLeft(int i_Size) const
	{
		return (i_Size * 2) + 1;
	}
	
	int getRight(int i_Size) const
	{
		return (i_Size * 2) + 2;
	}
	
	void swap(int i_First, int i_Second)
	{
		Node temp = m_Arr[i_First];
		
		m_Arr[i_First] = m_Arr[i_Second];
		m_Arr[i_Second] = temp;
	}
	
	void heapify(int i_Root = 0)
	{
		int i = i_Root;
		
		while(i < m_Size)
		{
			int left = getLeft(i), right = getRight(i);
			
			if(isValidKey(left) && m_Arr[i].key > m_Arr[left].key)
			{
				swap(i, left);
				i = left;
			}
			else if(isValidKey(right) && m_Arr[i].key > m_Arr[right].key)
			{
				swap(i, right);
				i = right;
			}
			else
			{
				break;
			}
		}
	}
	
	void fixUp()
	{
		int i = m_Size - 1;
		
		while(i > 0)
		{
			int parent = getParent(i);
			
			if(m_Arr[i].key < m_Arr[parent].key)
			{
				swap(i, parent);
				i = parent;
			}
			else
			{
				break;
			}
		}
	}
	
	bool isValidKey(int i_Key) const
	{
		return i_Key >= 0 && i_Key < m_Size;
	}
  
  public:
	MinHeap() = delete;
	MinHeap(const MinHeap &org) = delete;
	const MinHeap &operator=(const MinHeap &org) = delete;
	
	~MinHeap()
	{
		if(m_NeedToDeAllocate)
		{
			delete[] m_Arr;
		}
	}
	
	MinHeap(int i_Size)
	{
		m_Capacity = i_Size;
		m_Size = 0;
		m_Arr = new T[m_Capacity];
		m_NeedToDeAllocate = true;
	}
	
	MinHeap(Node *io_Arr, int i_Size)
	{
		m_Size = m_Capacity = i_Size;
		m_Arr = io_Arr;
		m_NeedToDeAllocate = false;
		
		for(int i = (m_Size / 2) - 1; i >= 0; i--)
		{
			heapify(i);
		}
	}
	
	static MinHeap<T> Build(int i_Size)
	{
		return MinHeap<T>(i_Size);
	}
	
	static MinHeap<T> Build(Node *io_Arr, int i_Size)
	{
		return MinHeap<T>(io_Arr, i_Size);
	}
	
	bool IsEmpty() const
	{
		return m_Size == 0;
	}
	
	T DeleteMin()
	{
		if(IsEmpty())
		{
			throw std::out_of_range(ERROR_EMPTY_HEAP);
		}
		
		T res = m_Arr[0].data;
		
		m_Arr[0] = m_Arr[--m_Size];
		heapify();
		
		return res;
	}
	
	void DecreaseKey(int i_OldKey, int i_NewKey)
	{
		if(!isValidKey(i_OldKey) || !isValidKey(i_NewKey))
		{
			throw std::invalid_argument(ERROR_INVALID_KEY);
		}
		
		for(int i = 0; i < m_Size; i++)
		{
			if(m_Arr[i].key == i_OldKey)
			{
				m_Arr[i].key = i_NewKey;
				heapify(i);
				break;
			}
		}
	}
	
	int GetSize() const
	{
		return m_Size;
	}
	
	void Insert(const Node &i_NewNode)
	{
		if(m_Size == m_Capacity)
		{
			throw std::out_of_range(ERROR_FULL_HEAP);
		}
		
		m_Arr[m_Size++] = i_NewNode;
		fixUp();
	}
};

