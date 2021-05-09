#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

template<class T>
class Dijkstra
{
  private:
	int m_Size = 0;
	float *m_pathWeightArr = nullptr;
	T m_Pq;
	
	Dijkstra(int i_Size, int i_StartIndex) : m_Pq(i_Size)
	{
		m_Size = i_Size;
		m_pathWeightArr = new float[m_Size + 1];
		
		for(int i = 1; i <= m_Size; i++)
		{
			m_pathWeightArr[i] = MAX_WEIGHT;
		}
		
		m_pathWeightArr[i_StartIndex] = 0;
		for(int i = 1; i <= m_Size; i++)
		{
			T::Node temp;
			
			temp.data = i;
			temp.key = m_pathWeightArr[i];
			m_Pq.Insert(temp);
		}
	}
	
	void relax(int i_U, int i_V, float i_Weight)
	{
		// d as mention at the algorithm
		auto *d = m_pathWeightArr;
		
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
	
	static float Execute(const Graph &i_Graph, int i_Start, int i_Target)
	{
		// algorithm init
		Dijkstra dijkstraHeap(i_Graph.GetSize(), i_Start);
		
		// while there is improving edge
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
