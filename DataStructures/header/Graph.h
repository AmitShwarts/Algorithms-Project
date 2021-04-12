#pragma once
#include "../../configs.h"

class Graph
{
  public:
	virtual bool IsAdjacent(int i_U, int i_V) = 0;
	virtual AdjacentList GetAdjList(int i_U) = 0;
	virtual void AddEdge(int i_U, int i_V, int i_Weight = MAX_WEIGHT) = 0;
	virtual void RemoveEdge(int i_U, int i_V) = 0;
	virtual ~Graph(){};
	virtual int GetSize() = 0;
};
