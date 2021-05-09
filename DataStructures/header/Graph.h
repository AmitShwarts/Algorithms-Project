#pragma once
#include "../../configs.h"

class Graph
{
  public:
	virtual bool IsAdjacent(int i_U, int i_V) const = 0;
	virtual AdjacentList GetAdjList(int i_U) const = 0;
	virtual void AddEdge(int i_U, int i_V, int i_Weight = MAX_WEIGHT) = 0;
	virtual void RemoveEdge(int i_U, int i_V) = 0;
	
	virtual ~Graph(){};
	virtual int GetSize() const = 0;
	
	bool IsGraphSimple() const
	{
		bool isSimple = true;
		
		for(int vertexU = 1; vertexU < GetSize(); vertexU++)
		{
			auto currAdjs = GetAdjList(vertexU);
			auto currEdge = currAdjs.Front();
			bool *visited = new bool[GetSize() + 1];
			
			for(int i = 0; i < GetSize() + 1; i++)
			{
				visited[i] = false;
			}
			
			while(currEdge != nullptr && isSimple == true)
			{
				isSimple = visited[currEdge->vertex] == false || currEdge->vertex == vertexU;
				visited[currEdge->vertex] = true;
				currEdge = currEdge->next;
			}
			
			delete[] visited;
			
			if(isSimple == false)
			{
				break;
			}
		}
		
		return isSimple;
	}
};
