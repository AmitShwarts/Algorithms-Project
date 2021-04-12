#pragma once
#include "configs.h"
#include "Algorithms/headers/MinWeightAlgorithms.h"
#include "DataStructures/header/WeightedGraphByLists.h"
#include "DataStructures/header/WeightedGraphByMat.h"

void executeProgram(const std::string &i_InputFileName, const std::string &i_OutputFileName);
void readEdgesFromFile(std::ifstream &i_Data, Graph *&o_MatGraph, Graph *&o_ListsGraph);
void executeAlgorithms(const Graph &i_MatGraph, const Graph &i_ListsGraph, int i_Start, int i_Target);
