#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

class DijkstraHeap
{
  private:
  
  public:
	DijkstraHeap() = delete;
	DijkstraHeap(const DijkstraHeap &org) = delete;
	~DijkstraHeap() = delete;
	const DijkstraHeap &operator=(const DijkstraHeap &org) = delete;
	static int Execute(const Graph &i_Graph, int i_Start, int i_Target);
};

