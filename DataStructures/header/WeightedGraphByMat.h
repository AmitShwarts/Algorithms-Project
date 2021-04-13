#pragma once
#include "../../configs.h"
#include "Graph.h"

namespace GraphByMat
{
  class WeightedGraph : public Graph
  {
	private:
	  int m_Size;
	  int **m_AdjMat;
	  bool isValidVertex(int i_U) const{ return i_U > 0 && i_U <= m_Size; }
  
	public:
	  WeightedGraph(int i_Size);
	  WeightedGraph() = delete;
	  WeightedGraph(const WeightedGraph &org);
	  virtual ~WeightedGraph();
	  const WeightedGraph &operator=(const WeightedGraph &org);
	  //
	  // Methods
	  static WeightedGraph MakeEmptyGraph(int i_Size);
	  virtual bool IsAdjacent(int i_U, int i_V) const;
	  virtual AdjacentList GetAdjList(int i_U) const;
	  virtual void AddEdge(int i_U, int i_V, int i_Weight = MAX_WEIGHT);
	  virtual void RemoveEdge(int i_U, int i_V);
	  virtual int GetSize() const{ return m_Size; }
  };
}
