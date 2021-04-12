#pragma once
#include "../../configs.h"

int dijkstraHeap(const Graph &i_Graph, int i_Start, int i_Target);
int dijkstraArray(const Graph &i_Graph, int i_Start, int i_Target);
int bellmanFord(const Graph &i_Graph, int i_Start, int i_Target);
void init(const Graph &i_Graph, int *&o_pathWeightArr, int *&o_lastVertexArr, int i_StartVertexIndex);
void relax();