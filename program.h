#pragma once
#include "configs.h"
#include "DataStructures/header/WeightedGraphByLists.h"
#include "DataStructures/header/WeightedGraphByMat.h"
#include "Algorithms/headers/BellmanFord.h"
#include "Algorithms/headers/Dijkstra.h"
#include <chrono>
#include <iomanip>

void readGraphFromFile(const std::string &i_InputFileName, Graph *&io_MatGraph, Graph *&io_ListsGraph,
					   int &io_startVertexIndex, int &io_targetVertexIndex);
void executeProgram(const std::string &i_InputFileName, const std::string &i_OutputFileName);
void readEdgesFromFile(std::ifstream &i_Data, Graph *&o_MatGraph, Graph *&o_ListsGraph);
void
executeAlgorithms(const Graph &i_MatGraph, const Graph &i_ListsGraph, int i_Start, int i_Target, std::string *o_Output);
void printRes(float i_Result, std::string i_Str);

template<typename F>
float executeAndMeasureTime(F i_Func, const Graph &i_ListsGraph, int i_Start, int i_Target, std::string &o_Output)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::ios_base::sync_with_stdio(false);
	
	float res = i_Func(i_ListsGraph, i_Start, i_Target);
	auto end = std::chrono::high_resolution_clock::now();
	double timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	timeTaken *= 1e-9;
	
	// write the measured time
	char buffer[100], format[] = "%0.9f";
	sprintf(buffer, format, timeTaken);
	o_Output = buffer;
	
	return res;
}
