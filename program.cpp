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
	const int k_NumOfAlgorithms = 6;
	string dataToWrite[k_NumOfAlgorithms];
	
	executeAlgorithms(*matGraph, *listsGraph, startVertexIndex, targetVertexIndex, dataToWrite);
	
	// write measured times to file
	ofstream outputFile(i_OutputFileName);
	
	for(int i = 0; i < k_NumOfAlgorithms; i++)
	{
		outputFile << dataToWrite[i] << endl;
	}
	
	outputFile.close();
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

void executeAlgorithms(const Graph &i_MatGraph, const Graph &i_ListsGraph, int i_Start, int i_Target, string *o_Output)
{
	float result;
	string noPath = "There is no path";
	
	result = executeAndMeasureTime(Dijkstra<MinHeap<float>>::Execute, i_ListsGraph, i_Start, i_Target, o_Output[0]);
	printRes(result, "Adjacency Dijkstra heap");
	
	result = executeAndMeasureTime(Dijkstra<ArrayPriorityQueue<float>>::Execute, i_ListsGraph, i_Start, i_Target,
								   o_Output[1]);
	printRes(result, "Adjacency Dijkstra array");
	
	result = executeAndMeasureTime(BellmanFord::Execute, i_ListsGraph, i_Start, i_Target, o_Output[2]);
	printRes(result, "Adjacency Bellman Ford");
	
	result = executeAndMeasureTime(Dijkstra<MinHeap<float>>::Execute, i_MatGraph, i_Start, i_Target, o_Output[3]);
	printRes(result, "Matrix Dijkstra heap");
	
	result = executeAndMeasureTime(Dijkstra<ArrayPriorityQueue<float>>::Execute, i_MatGraph, i_Start, i_Target,
								   o_Output[4]);
	printRes(result, "Matrix Dijkstra array");
	
	result = executeAndMeasureTime(BellmanFord::Execute, i_MatGraph, i_Start, i_Target, o_Output[5]);
	printRes(result, "Matrix Bellman Ford");
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