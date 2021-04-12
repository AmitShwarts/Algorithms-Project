#pragma once
#include "../configs.h"

namespace GraphByMat
{
  class WeightedGraph
  {
	private:
	  int m_Size;
	  int **m_AdjMat;
	  bool isValidVertex(int i_U){ return i_U > 0 && i_U <= m_Size; }
	
	public:
	  WeightedGraph(int i_Size);
	  WeightedGraph() = delete;
	  WeightedGraph(const WeightedGraph &org);
	  ~WeightedGraph();
	  const WeightedGraph &operator=(const WeightedGraph &org);
	  //
	  // Methods
	  static WeightedGraph MakeEmptyGraph(int i_Size);
	  bool IsAdjacent(int i_U, int i_V){ return m_AdjMat[i_U][i_V] != MAX_WEIGHT; }
	  AdjacentList GetAdjList(int i_U);
	  void AddEdge(int i_U, int i_V, int i_Weight);
	  void RemoveEdge(int i_U, int i_V);
  };
}
