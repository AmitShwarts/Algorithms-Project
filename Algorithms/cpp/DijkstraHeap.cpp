#include "../headers/DijkstraHeap.h"

DijkstraHeap::DijkstraHeap(int i_Size, int i_StartIndex) : m_Pq(i_Size)
{
	m_Size = i_Size;
	m_pathWeightArr = new int[m_Size + 1];
	
	for(int i = 1; i <= m_Size; i++)
	{
		m_pathWeightArr[i] = MAX_WEIGHT;
	}
	
	for(int i = 0; i < m_Size; i++)
	{
		MinHeap<int>::Node temp;
		
		temp.data = i + 1;
		temp.key = m_pathWeightArr[i];
		m_Pq.Insert(temp);
	}
	
	m_pathWeightArr[0] = m_pathWeightArr[i_StartIndex] = 0;
}

void DijkstraHeap::relax(int i_U, int i_V, int i_Weight)
{
	// d as mention at the algorithm
	int *d = m_pathWeightArr;
	
	if(d[i_U] != MAX_WEIGHT && d[i_V] > d[i_U] + i_Weight)
	{
		d[i_V] = d[i_U] + i_Weight;
		m_Pq.DecreaseKey(i_V, d[i_V]);
	}
}

DijkstraHeap::~DijkstraHeap()
{
	delete[] m_pathWeightArr;
}

int DijkstraHeap::Execute(const Graph &i_Graph, int i_Start, int i_Target)
{
	DijkstraHeap dijkstraHeap(i_Graph.GetSize(), i_Start);
	
	while(!dijkstraHeap.m_Pq.IsEmpty())
	{
		int vertexU = dijkstraHeap.m_Pq.DeleteMin();
		auto currList = i_Graph.GetAdjList(vertexU);
		auto currEdge = currList.Front();
		
		while(currEdge != nullptr)
		{
			dijkstraHeap.relax(vertexU, currEdge->vertex, currEdge->weight);
			currEdge = currEdge->next;
		}
	}
	
	return dijkstraHeap.m_pathWeightArr[i_Target];
}

bool DijkstraHeap::isThereImprovingEdge(const Graph &i_Graph)
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
