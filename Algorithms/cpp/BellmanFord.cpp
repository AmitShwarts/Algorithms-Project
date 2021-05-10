#include "../headers/BellmanFord.h"

BellmanFord::BellmanFord(int i_Size, int i_StartIndex)
{
	m_Size = i_Size;
	m_pathWeightArr = new Node[m_Size + 1];
	
	for(int i = 1; i <= m_Size; i++)
	{
		m_pathWeightArr[i].isInfinity = true;
	}
	
	m_pathWeightArr[i_StartIndex].weight = 0;
	m_pathWeightArr[i_StartIndex].isInfinity = false;
}

void BellmanFord::relax(int i_U, int i_V, float i_Weight)
{
	// d as mention at the algorithm
	auto *d = m_pathWeightArr;
	
	if(d[i_U].isInfinity == false)
	{
		if(d[i_V].isInfinity == true || d[i_V].weight > d[i_U].weight + i_Weight)
		{
			d[i_V].weight = d[i_U].weight + i_Weight;
			d[i_V].isInfinity = false;
		}
	}
}

BellmanFord::~BellmanFord()
{
	delete[] m_pathWeightArr;
}

float BellmanFord::Execute(const Graph &i_Graph, int i_Start, int i_Target)
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
	
	return bellmanFord.m_pathWeightArr[i_Target].weight;
}

bool BellmanFord::isThereImprovingEdge(const Graph &i_Graph)
{
	// d as mention at the algorithm
	auto *d = m_pathWeightArr;
	bool foundImproving = false;
	
	for(int uIndex = 1; uIndex <= i_Graph.GetSize() && !foundImproving; uIndex++)
	{
		auto currList = i_Graph.GetAdjList(uIndex);
		auto currEdge = currList.Front();
		
		while(currEdge != nullptr && !foundImproving)
		{
			bool case1 = d[uIndex].isInfinity == false;
			bool case2 = d[currEdge->vertex].isInfinity == true ||
						 d[currEdge->vertex].weight > d[uIndex].weight + currEdge->weight;
			
			foundImproving = case1 && case2;
			currEdge = currEdge->next;
		}
	}
	
	return foundImproving;
}
