#pragma once
#include <vector>
#include "Edge.h"
using namespace std;
// a structure to represent a graph 
class Graph
{
public:
	// V-> Number of vertices, E-> Number of edges 
	int V=0, E=0;

	// graph is represented as an vector of edges 
	vector<Edge>listEdge;

};