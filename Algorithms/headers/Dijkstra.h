#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

template<class T>
class Dijkstra
{
  private:
	int m_Size = 0;
	int *m_pathWeightArr = nullptr;
	T m_Pq;
	
	Dijkstra(int i_Size, int i_StartIndex) : m_Pq(i_Size)
	{
		m_Size = i_Size;
		m_pathWeightArr = new int[m_Size + 1];
		
		for(int i = 1; i <= m_Size; i++)
		{
			m_pathWeightArr[i] = MAX_WEIGHT;
		}
		
		for(int i = 0; i < m_Size; i++)
		{
			T::Node temp;
			
			temp.data = i + 1;
			temp.key = m_pathWeightArr[i];
			m_Pq.Insert(temp);
		}
		
		m_pathWeightArr[0] = m_pathWeightArr[i_StartIndex] = 0;
	}
	
	void relax(int i_U, int i_V, int i_Weight)
	{
		// d as mention at the algorithm
		int *d = m_pathWeightArr;
		
		if(d[i_U] != MAX_WEIGHT && d[i_V] > d[i_U] + i_Weight)
		{
			d[i_V] = d[i_U] + i_Weight;
			m_Pq.DecreaseKey(i_V, d[i_V]);
		}
	}
  
  public:
	Dijkstra() = delete;
	Dijkstra(const Dijkstra &org) = delete;
	const Dijkstra &operator=(const Dijkstra &org) = delete;
	
	~Dijkstra()
	{
		delete[] m_pathWeightArr;
	}
	
	static int Execute(const Graph &i_Graph, int i_Start, int i_Target)
	{
		Dijkstra dijkstraHeap(i_Graph.GetSize(), i_Start);
		
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
};
