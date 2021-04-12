#include "../header/WeightedGraphByMat.h"

using namespace DataStructure1;

WeightedGraphByMat::WeightedGraphByMat(int i_Size)
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
			m_AdjMat[i][j] = r_MaxWeight;
		}
	}
}
WeightedGraphByMat::~WeightedGraphByMat()
{
	
	for(int i = 0; i < m_Size; i++)
	{
		delete[] m_AdjMat[i];
	}
	
	delete[] m_AdjMat;
}
AdjacentList WeightedGraphByMat::GetAdjList(int i_U)
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
void WeightedGraphByMat::AddEdge(int i_U, int i_V, int i_Weight)
{
	
	if(!isValidVertex(i_U) || !isValidVertex(i_V) || m_AdjMat[i_U - 1][i_V - 1] != r_MaxWeight)
	{
		throw "Invalid";
	}
	
	m_AdjMat[i_U - 1][i_V - 1] = i_Weight;
}
void WeightedGraphByMat::RemoveEdge(int i_U, int i_V)
{
	
	if(!isValidVertex(i_U) || !isValidVertex(i_V) || m_AdjMat[i_U - 1][i_V - 1] == r_MaxWeight)
	{
		throw "Invalid";
	}
	
	m_AdjMat[i_U - 1][i_V - 1] = r_MaxWeight;
}
WeightedGraphByMat WeightedGraphByMat::MakeEmptyGraph(int i_Size)
{
	
	return WeightedGraphByMat(i_Size);
}
WeightedGraphByMat::WeightedGraphByMat(const WeightedGraphByMat &org)
{
	
	if(this != &org)
	{
		*this = org;
	}
}
const WeightedGraphByMat &WeightedGraphByMat::operator=(const WeightedGraphByMat &org)
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
