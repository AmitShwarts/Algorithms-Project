#include "program.h"

using namespace std;

void executeProgram(const string &i_InputFileName, const string &i_OutputFileName)
{
	ifstream data(i_InputFileName);
	int amountOfVertices, startVertexIndex, targetVertexIndex;
	
	// graphs init
	data >> amountOfVertices >> startVertexIndex >> targetVertexIndex;
	Graph *matGraph = new GraphByMat::WeightedGraph(amountOfVertices);
	Graph *listsGraph = new GraphByLists::WeightedGraph(amountOfVertices);
	
	readEdgesFromFile(data, matGraph, listsGraph);
	data.close();
	
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
void readEdgesFromFile(ifstream &i_Data, Graph *&o_MatGraph, Graph *&o_ListsGraph)
{
	while(!i_Data.eof())
	{
		int u, v, weight;
		
		i_Data >> u >> v >> weight;
		o_MatGraph->AddEdge(u, v, weight);
		o_ListsGraph->AddEdge(u, v, weight);
	}
}
void executeAlgorithms(const Graph &i_MatGraph, const Graph &i_ListsGraph, int i_Start, int i_Target, string *o_Output)
{
	cout << fixed << setprecision(9);
	int result;
	
	result = executeAndMeasureTime(DijkstraHeap::Execute, i_ListsGraph, i_Start, i_Target, o_Output[0]);
	cout << "Adjacency Dijkstra heap " << result << endl;
	
	result = executeAndMeasureTime(DijkstraArray::Execute, i_ListsGraph, i_Start, i_Target, o_Output[1]);
	cout << "Adjacency Dijkstra array " << result << endl;
	
	result = executeAndMeasureTime(BellmanFord::Execute, i_ListsGraph, i_Start, i_Target, o_Output[2]);
	cout << "Adjacency Bellman Ford " << result << endl;
	
	result = executeAndMeasureTime(DijkstraHeap::Execute, i_MatGraph, i_Start, i_Target, o_Output[3]);
	cout << "Matrix Dijkstra heap " << result << endl;
	
	result = executeAndMeasureTime(DijkstraArray::Execute, i_MatGraph, i_Start, i_Target, o_Output[4]);
	cout << "Matrix Dijkstra array " << result << endl;
	
	result = executeAndMeasureTime(BellmanFord::Execute, i_MatGraph, i_Start, i_Target, o_Output[5]);
	cout << "Matrix Bellman Ford " << result << endl;
}
