#include "../header/WeightedGraphByMat.h"

using namespace GraphByMat;

WeightedGraph::WeightedGraph(int i_Size)
{
	if(i_Size <= 0)
	{
		throw std::invalid_argument(Error::CONSTRUCTOR_INPUT_NON_POSITIVE);
	}
	
	m_Size = i_Size;
	m_AdjMat = new float *[m_Size];
	
	for(int i = 0; i < m_Size; i++)
	{
		m_AdjMat[i] = new float[m_Size];
		
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
AdjacentList WeightedGraph::GetAdjList(int i_U) const
{
	if(!isValidVertex(i_U))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}
	
	AdjacentList resultList;
	
	for(int i = 0; i < m_Size; i++)
	{
		if(m_AdjMat[i_U - 1][i] != MAX_WEIGHT)
		{
			resultList.ToTail(i + 1, m_AdjMat[i_U - 1][i]);
		}
	}
	
	return resultList;
}

void WeightedGraph::AddEdge(int i_U, int i_V, float i_Weight)
{
	if(!isValidVertex(i_U) || !isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}
	
	m_AdjMat[i_U - 1][i_V - 1] = i_Weight;
}

void WeightedGraph::RemoveEdge(int i_U, int i_V)
{
	if(!isValidVertex(i_U) || !isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}
	
	m_AdjMat[i_U - 1][i_V - 1] = MAX_WEIGHT;
}
WeightedGraph WeightedGraph::MakeEmptyGraph(int i_Size)
{
	return WeightedGraph(i_Size);
}
WeightedGraph::WeightedGraph(const WeightedGraph &org)
{
	m_Size = 0;
	*this = org;
}
const WeightedGraph &WeightedGraph::operator=(const WeightedGraph &org)
{
	if(this != &org)
	{
		// delete old data
		if(m_Size > 0)
		{
			for(int i = 0; i < m_Size; i++)
			{
				delete[] m_AdjMat[i];
			}
			
			delete[] m_AdjMat;
		}
		
		// copy data
		m_Size = org.m_Size;
		m_AdjMat = new float *[m_Size];
		
		for(int i = 0; i < m_Size; i++)
		{
			m_AdjMat[i] = new float[m_Size];
			
			for(int j = 0; j < m_Size; j++)
			{
				m_AdjMat[i][j] = org.m_AdjMat[i][j];
			}
		}
	}
	
	return *this;
}
bool WeightedGraph::IsAdjacent(int i_U, int i_V) const
{
	if(!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}
	
	return m_AdjMat[i_U - 1][i_V - 1] != MAX_WEIGHT;
}
