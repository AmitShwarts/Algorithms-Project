#include "../header/AdjacentList.h"

AdjacentList::~AdjacentList()
{
	
	ListNode *currentNode = m_Head;
	
	while(currentNode != nullptr)
	{
		ListNode *tempNode = currentNode;
		
		currentNode = currentNode->next;
		delete tempNode;
	}
}
ListNode *AdjacentList::makeNewNode(int i_Vertex, int i_Weight, ListNode *io_Next)
{
	
	ListNode *newNode = new ListNode;
	
	newNode->vertex = i_Vertex;
	newNode->weight = i_Weight;
	newNode->next = io_Next;
	newNode->prev = nullptr;
	
	return newNode;
}
void AdjacentList::ToHead(int i_Vertex, int i_Weight)
{
	
	ListNode *newHead = this->makeNewNode(i_Vertex, i_Weight, m_Head);
	
	if(this->IsEmpty())
	{
		m_Head = m_Tail = newHead;
	}
	else
	{
		m_Head->prev = newHead;
		m_Head = newHead;
	}
	
	m_Size++;
}
void AdjacentList::ToTail(int i_Vertex, int i_Weight)
{
	
	ListNode *newTail = this->makeNewNode(i_Vertex, i_Weight);
	
	newTail->prev = m_Tail;
	if(this->IsEmpty())
	{
		m_Head = m_Tail = newTail;
	}
	else
	{
		m_Tail->next = newTail;
		m_Tail = newTail;
	}
	
	m_Size++;
}
void AdjacentList::DeleteFromHead()
{
	
	if(this->IsEmpty())
	{
		throw "Invalid";
	}
	
	if(m_Size == 1)
	{
		delete m_Head;
		m_Head = m_Tail = nullptr;
	}
	else
	{
		ListNode *lastHead = m_Head;
		
		m_Head = lastHead->next;
		m_Head->prev = nullptr;
		delete lastHead;
	}
	
	m_Size--;
}
void AdjacentList::DeleteFromTail()
{
	
	if(this->IsEmpty())
	{
		throw "Invalid";
	}
	
	if(m_Size == 1)
	{
		delete m_Head;
		m_Head = m_Tail = nullptr;
	}
	else
	{
		ListNode *lastTail = m_Tail;
		
		m_Tail = lastTail->prev;
		m_Tail->next = nullptr;
		delete lastTail;
	}
	
	m_Size--;
}
AdjacentList::AdjacentList(const AdjacentList &org)
{
	
	if(this != &org)
	{
		*this = org;
	}
}
const AdjacentList &AdjacentList::operator=(const AdjacentList &org)
{
	
	if(this != &org)
	{
		// delete old data
		ListNode *currentNode = m_Head;
		
		while(currentNode != nullptr)
		{
			ListNode *tempNode = currentNode;
			
			currentNode = currentNode->next;
			delete tempNode;
		}
		
		// copy data
		currentNode = org.m_Head;
		while(currentNode != nullptr)
		{
			this->ToTail(currentNode->vertex, currentNode->weight);
			currentNode = currentNode->next;
		}
	}
	
	return *this;
}
const ListNode *AdjacentList::Find(int i_U)
{
	
	ListNode *currentNode = m_Head;
	
	while(currentNode != nullptr)
	{
		if(currentNode->vertex == i_U)
		{
			break;
		}
	}
	
	return currentNode;
}
void AdjacentList::DeleteVertex(int i_Vertex)
{
	
	ListNode *currentNode = m_Head;
	
	while(currentNode != nullptr && currentNode->vertex != i_Vertex)
	{
		currentNode = currentNode->next;
	}
	
	if(currentNode == m_Head)
	{
		this->DeleteFromHead();
	}
	else if(currentNode == m_Tail)
	{
		this->DeleteFromTail();
	}
	else if(currentNode != nullptr)
	{
		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
		delete currentNode;
		m_Size--;
	}
}
