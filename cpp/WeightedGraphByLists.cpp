#include "../header/WeightedGraphByLists.h"

using namespace GraphByLists;
WeightedGraph::WeightedGraph(int i_Size)
{
	
	if(i_Size <= 0)
	{
		throw "Invalid.";
	}
	
	m_Size = i_Size;
	m_Vertices = new AdjacentList[m_Size];
}
WeightedGraph::~WeightedGraph()
{
	
	delete[] m_Vertices;
}
WeightedGraph WeightedGraph::MakeEmptyGraph(int i_Size)
{
	
	return WeightedGraph(i_Size);
}
WeightedGraph::WeightedGraph(const WeightedGraph &org)
{
	
	if(this != &org)
	{
		*this = org;
	}
}
const WeightedGraph &WeightedGraph::operator=(const WeightedGraph &org)
{
	
	if(this != &org)
	{
		// delete old data
		delete[] m_Vertices;
		
		// copy data
		m_Size = org.m_Size;
		m_Vertices = new AdjacentList[m_Size];
		
		for(int i = 0; i < m_Size; i++)
		{
			m_Vertices[i] = org.m_Vertices[i];
		}
	}
	
	return *this;
}
bool WeightedGraph::IsAdjacent(int i_U, int i_V)
{
	
	if(!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw "Invalid";
	}
	
	return m_Vertices[i_U - 1].Find(i_V) != nullptr;
}
AdjacentList WeightedGraph::GetAdjList(int i_U)
{
	
	if(!this->isValidVertex(i_U))
	{
		throw "Invalid.";
	}
	
	return m_Vertices[i_U - 1];
}
void WeightedGraph::AddEdge(int i_U, int i_V, int i_Weight)
{
	
	if(!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw "Invalid.";
	}
	
	m_Vertices[i_U - 1].ToTail(i_V, i_Weight);
}
void WeightedGraph::RemoveEdge(int i_U, int i_V)
{
	
	if(!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw "Invalid.";
	}
	
	m_Vertices[i_U - 1].DeleteVertex(i_V);
}
