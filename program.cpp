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
	
	executeAlgorithms(*matGraph, *listsGraph, startVertexIndex, targetVertexIndex);
	
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
void executeAlgorithms(const Graph &i_MatGraph, const Graph &i_ListsGraph, int i_Start, int i_Target)
{
	
	cout << endl << "Type\t\tAlgorithm\tMin weight" << endl;
	cout << "-------------------------------------------" << endl;
	
	cout << "Adjacency\tDijkstra heap\t" << dijkstraHeap(i_ListsGraph, i_Start, i_Target) << endl;
	cout << "Adjacency\tDijkstra array\t" << dijkstraArray(i_ListsGraph, i_Start, i_Target) << endl;
	cout << "Adjacency\tBellman Ford\t" << bellmanFord(i_ListsGraph, i_Start, i_Target) << endl;
	
	cout << "-------------------------------------------" << endl;
	
	cout << "Matrix\t\tDijkstra heap\t" << dijkstraHeap(i_MatGraph, i_Start, i_Target) << endl;
	cout << "Matrix\t\tDijkstra array\t" << dijkstraArray(i_MatGraph, i_Start, i_Target) << endl;
	cout << "Matrix\t\tBellman Ford\t" << bellmanFord(i_MatGraph, i_Start, i_Target) << endl;
}
