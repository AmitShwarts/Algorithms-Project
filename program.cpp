#include "program.h"

using namespace std;

void executeProgram(const string &i_InputFileName, const string &i_OutputFileName)
{
	int startVertexIndex = 0, targetVertexIndex = 0;
	Graph *matGraph, *listsGraph;
	
	// graphs init
	readGraphFromFile(i_InputFileName, matGraph, listsGraph, startVertexIndex, targetVertexIndex);
	
	bool matIsSimple = matGraph->IsGraphSimple();
	bool listIsSimple = listsGraph->IsGraphSimple();
	
	if(listIsSimple == false || matIsSimple == false)
	{
		delete matGraph;
		delete listsGraph;
		throw std::invalid_argument(Error::INVALID_INPUT);
	}
	
	// execute algorithms and measured times
	executeAlgorithms(*matGraph, *listsGraph, startVertexIndex, targetVertexIndex, i_OutputFileName);
	
	// free memory
	delete matGraph;
	delete listsGraph;
}

void readGraphFromFile(const std::string &i_InputFileName, Graph *&io_MatGraph, Graph *&io_ListsGraph,
					   int &io_startVertexIndex, int &io_targetVertexIndex)
{
	ifstream data(i_InputFileName);
	int amountOfVertices;
	
	try
	{
		data >> amountOfVertices >> io_startVertexIndex >> io_targetVertexIndex;
	}
	catch(std::exception &error)
	{
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}
	
	if(amountOfVertices < 0 || io_startVertexIndex < 0 || io_targetVertexIndex < 0)
	{
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}
	
	io_MatGraph = new GraphByMat::WeightedGraph(amountOfVertices);
	io_ListsGraph = new GraphByLists::WeightedGraph(amountOfVertices);
	
	try
	{
		readEdgesFromFile(data, io_MatGraph, io_ListsGraph);
	}
	catch(std::exception &error)
	{
		delete io_MatGraph;
		delete io_ListsGraph;
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}
	
	data.close();
}

void readEdgesFromFile(ifstream &i_Data, Graph *&o_MatGraph, Graph *&o_ListsGraph)
{
	while(i_Data.eof() == false)
	{
		float u = -1, v = -1, weight = -1;
		
		// read edge
		try
		{
			i_Data >> u >> v >> weight;
		}
		catch(std::exception &error)
		{
			throw std::invalid_argument(Error::INVALID_INPUT);
		}
		
		// check if edge is valid
		if(u != -1 && v != -1 && weight != -1)
		{
			if(u < 0 || v < 0 || weight < 0)
			{
				throw std::invalid_argument(Error::INVALID_INPUT);
			}
			
			o_MatGraph->AddEdge(u, v, weight);
			o_ListsGraph->AddEdge(u, v, weight);
		}
	}
}

void executeAlgorithms(const Graph &i_MatGraph, const Graph &i_ListsGraph, int i_Start, int i_Target,
					   const std::string &i_OutputFileName)
{
	float result;
	string noPath = "There is no path", currAlgo;
	ofstream outputFile(i_OutputFileName);
	
	currAlgo = "Adjacency Dijkstra heap";
	result = executeAndMeasureTime(Dijkstra<MinHeap<float>>::Execute, i_ListsGraph, i_Start, i_Target, outputFile,
								   currAlgo);
	printRes(result, currAlgo);
	
	currAlgo = "Adjacency Dijkstra array";
	result = executeAndMeasureTime(Dijkstra<ArrayPriorityQueue<float>>::Execute, i_ListsGraph, i_Start, i_Target,
								   outputFile, currAlgo);
	printRes(result, currAlgo);
	
	currAlgo = "Adjacency Bellman Ford";
	result = executeAndMeasureTime(BellmanFord::Execute, i_ListsGraph, i_Start, i_Target, outputFile, currAlgo);
	printRes(result, currAlgo);
	
	currAlgo = "Matrix Dijkstra heap";
	result = executeAndMeasureTime(Dijkstra<MinHeap<float>>::Execute, i_MatGraph, i_Start, i_Target, outputFile,
								   currAlgo);
	printRes(result, currAlgo);
	
	currAlgo = "Matrix Dijkstra array";
	result = executeAndMeasureTime(Dijkstra<ArrayPriorityQueue<float>>::Execute, i_MatGraph, i_Start, i_Target,
								   outputFile, currAlgo);
	printRes(result, currAlgo);
	
	currAlgo = "Matrix Bellman Ford";
	result = executeAndMeasureTime(BellmanFord::Execute, i_MatGraph, i_Start, i_Target, outputFile, currAlgo);
	printRes(result, currAlgo);
	
	outputFile.close();
}

void printRes(float i_Result, std::string i_Str)
{
	cout << i_Str << " ";
	if(i_Result == MAX_WEIGHT)
	{
		cout << "There is no path" << endl;
	}
	else
	{
		cout << i_Result << endl;
	}
}