#pragma once
#include <iostream>
#include "AdjacentList.h"

namespace DataStructure2
{
  class WeightedGraphByLists
  {
	private:
	  int m_Size;
	  AdjacentList *m_Vertices;
	  bool isValidVertex(int i_U){ return i_U > 0 && i_U <= m_Size; }
	
	public:
	  WeightedGraphByLists(int i_Size);
	  WeightedGraphByLists() = delete;
	  WeightedGraphByLists(const WeightedGraphByLists &org);
	  ~WeightedGraphByLists();
	  const WeightedGraphByLists &operator=(const WeightedGraphByLists &org);
	  //
	  // Methods
	  static WeightedGraphByLists MakeEmptyGraph(int i_Size);
	  bool IsAdjacent(int i_U, int i_V);
	  AdjacentList GetAdjList(int i_U);
	  void AddEdge(int i_U, int i_V, int i_Weight);
	  void RemoveEdge(int i_U, int i_V);
  };
}
