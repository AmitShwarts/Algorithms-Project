#include "../header/WeightedGraphByMat.h"

using namespace GraphByMat;

WeightedGraph::WeightedGraph(int i_Size)
{
	
	if(i_Size <= 0)
	{
		throw "Invalid.";
	}
	
	m_Size = i_Size;
	m_AdjMat = new int *[m_Size];
	
	for(int i = 0; i < m_Size; i++)
	{
		m_AdjMat[i] = new int[m_Size];
		
		for(int j = 0; j < m_Size; j++)
		{
			m_AdjMat[i][j] = MAX_WEIGHT;
		}
	}
}
WeightedGraph::~WeightedGraph()
{
	
	for(int i = 0; i < m_Size; i++)
	{
		delete[] m_AdjMat[i];
	}
	
	delete[] m_AdjMat;
}
AdjacentList WeightedGraph::GetAdjList(int i_U)
{
	
	if(!isValidVertex(i_U))
	{
		throw "Invalid.";
	}
	
	AdjacentList resultList;
	
	for(int i = 0; i < m_Size; i++)
	{
		resultList.ToTail(i + 1, m_AdjMat[i_U - 1][i]);
	}
	
	return resultList;
}
void WeightedGraph::AddEdge(int i_U, int i_V, int i_Weight)
{
	
	if(!isValidVertex(i_U) || !isValidVertex(i_V) || m_AdjMat[i_U - 1][i_V - 1] != MAX_WEIGHT)
	{
		throw "Invalid";
	}
	
	m_AdjMat[i_U - 1][i_V - 1] = i_Weight;
}
void WeightedGraph::RemoveEdge(int i_U, int i_V)
{
	
	if(!isValidVertex(i_U) || !isValidVertex(i_V) || m_AdjMat[i_U - 1][i_V - 1] == MAX_WEIGHT)
	{
		throw "Invalid";
	}
	
	m_AdjMat[i_U - 1][i_V - 1] = MAX_WEIGHT;
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
		for(int i = 0; i < m_Size; i++)
		{
			delete[] m_AdjMat[i];
		}
		
		delete[] m_AdjMat;
		
		// copy data
		m_Size = org.m_Size;
		m_AdjMat = new int *[m_Size];
		
		for(int i = 0; i < m_Size; i++)
		{
			m_AdjMat[i] = new int[m_Size];
			
			for(int j = 0; j < m_Size; j++)
			{
				m_AdjMat[i][j] = org.m_AdjMat[i][j];
			}
		}
	}
	
	return *this;
}
