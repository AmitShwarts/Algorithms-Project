#include "../headers/BellmanFord.h"

BellmanFord::BellmanFord(int i_Size, int i_StartIndex)
{
	m_Size = i_Size;
	m_pathWeightArr = new int[m_Size + 1];
	m_lastVertexArr = new int[m_Size + 1];
	
	for(int i = 1; i <= m_Size; i++)
	{
		m_pathWeightArr[i] = MAX_WEIGHT;
		m_lastVertexArr[i] = 0;
	}
	
	m_pathWeightArr[0] = m_lastVertexArr[0] = 0;
	m_pathWeightArr[i_StartIndex] = 0;
}
void BellmanFord::relax(int i_U, int i_V, int i_Weight)
{
	// d & p as mention at the algorithm
	int *d = m_pathWeightArr, *p = m_lastVertexArr;
	
	if(d[i_U] != MAX_WEIGHT && d[i_V] > d[i_U] + i_Weight)
	{
		d[i_V] = d[i_U] + i_Weight;
		p[i_V] = i_U;
	}
}
BellmanFord::~BellmanFord()
{
	delete[] m_pathWeightArr;
	delete[] m_lastVertexArr;
}
int BellmanFord::Execute(const Graph &i_Graph, int i_Start, int i_Target)
{
	BellmanFord bellmanFord(i_Graph.GetSize(), i_Start);
	
	for(int iteration = 1; iteration <= i_Graph.GetSize() - 1; iteration++)
	{
		for(int uIndex = 1; uIndex <= i_Graph.GetSize(); uIndex++)
		{
			auto currList = i_Graph.GetAdjList(uIndex);
			auto currEdge = currList.Front();
			
			while(currEdge != nullptr)
			{
				bellmanFord.relax(uIndex, currEdge->vertex, currEdge->weight);
				currEdge = currEdge->next;
			}
		}
	}
	
	if(bellmanFord.isThereImprovingEdge(i_Graph))
	{
		throw std::logic_error(Error::NEGATIVE_CYCLE);
	}
	
	return bellmanFord.m_pathWeightArr[i_Target];
}

bool BellmanFord::isThereImprovingEdge(const Graph &i_Graph)
{
	// d as mention at the algorithm
	int *d = m_pathWeightArr;
	bool foundImproving = false;
	
	for(int uIndex = 1; uIndex <= i_Graph.GetSize() && !foundImproving; uIndex++)
	{
		auto currList = i_Graph.GetAdjList(uIndex);
		auto currEdge = currList.Front();
		
		while(currEdge != nullptr && !foundImproving)
		{
			foundImproving = d[uIndex] != MAX_WEIGHT && d[currEdge->vertex] > d[uIndex] + currEdge->weight;
			currEdge = currEdge->next;
		}
	}
	
	return foundImproving;
}
