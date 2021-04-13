#pragma once
#include "../../configs.h"
#include "../../DataStructures/header/Graph.h"

class DijkstraArray
{
  private:
  
  public:
	DijkstraArray() = delete;
	DijkstraArray(const DijkstraArray &org) = delete;
	~DijkstraArray() = delete;
	const DijkstraArray &operator=(const DijkstraArray &org) = delete;
	static int Execute(const Graph &i_Graph, int i_Start, int i_Target);
};

