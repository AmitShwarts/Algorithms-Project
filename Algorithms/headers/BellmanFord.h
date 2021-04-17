#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

class BellmanFord
{
  private:
	int m_Size = 0;
	int *m_pathWeightArr = nullptr;
	int *m_lastVertexArr = nullptr;
	BellmanFord(int i_Size, int i_StartIndex);
	void relax(int i_U, int i_V, int i_Weight);
	bool isThereImprovingEdge(const Graph &i_Graph);
  
  public:
	BellmanFord() = delete;
	BellmanFord(const BellmanFord &org) = delete;
	~BellmanFord();
	const BellmanFord &operator=(const BellmanFord &org) = delete;
	static int Execute(const Graph &i_Graph, int i_Start, int i_Target);
};
