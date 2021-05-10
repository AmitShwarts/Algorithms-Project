#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

class BellmanFord
{
  private:
	struct Node
	{
		float weight;
		bool isInfinity;
	};
	
	int m_Size = 0;
	Node *m_pathWeightArr = nullptr;
	
	BellmanFord(int i_Size, int i_StartIndex);
	void relax(int i_U, int i_V, float i_Weight);
	bool isThereImprovingEdge(const Graph &i_Graph);
  
  public:
	BellmanFord() = delete;
	BellmanFord(const BellmanFord &org) = delete;
	~BellmanFord();
	const BellmanFord &operator=(const BellmanFord &org) = delete;
	static float Execute(const Graph &i_Graph, int i_Start, int i_Target);
};
