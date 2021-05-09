#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

class DijkstraHeap
{
  private:
	int m_Size = 0;
	int *m_pathWeightArr = nullptr;
	MinHeap<int> m_Pq;
	
	DijkstraHeap(int i_Size, int i_StartIndex);
	void relax(int i_U, int i_V, int i_Weight);
	bool isThereImprovingEdge(const Graph &i_Graph);
  
  public:
	DijkstraHeap() = delete;
	DijkstraHeap(const DijkstraHeap &org) = delete;
	~DijkstraHeap();
	const DijkstraHeap &operator=(const DijkstraHeap &org) = delete;
	static int Execute(const Graph &i_Graph, int i_Start, int i_Target);
};
