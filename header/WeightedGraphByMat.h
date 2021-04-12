#pragma once
#include <iostream>
#include "AdjacentList.h"

namespace DataStructure1
{
  class WeightedGraphByMat
  {
	private:
	  static const int r_MaxWeight = INT_MAX;
	  int m_Size;
	  int **m_AdjMat;
	  bool isValidVertex(int i_U){ return i_U > 0 && i_U <= m_Size; }
	
	public:
	  WeightedGraphByMat(int i_Size);
	  WeightedGraphByMat() = delete;
	  WeightedGraphByMat(const WeightedGraphByMat &org);
	  ~WeightedGraphByMat();
	  const WeightedGraphByMat &operator=(const WeightedGraphByMat &org);
	  //
	  // Methods
	  static WeightedGraphByMat MakeEmptyGraph(int i_Size);
	  bool IsAdjacent(int i_U, int i_V){ return m_AdjMat[i_U][i_V] != r_MaxWeight; }
	  AdjacentList GetAdjList(int i_U);
	  void AddEdge(int i_U, int i_V, int i_Weight);
	  void RemoveEdge(int i_U, int i_V);
  };
}
