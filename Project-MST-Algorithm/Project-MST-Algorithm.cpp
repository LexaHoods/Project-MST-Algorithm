//Project Minimum Spanning Tree
//Axel Houdayer - IATIC4
#include <iostream> 
#include "Edge.h"
#include "Graph.h"
#include "Kruskal.h"
#include <random>
#include <time.h>


using namespace std;
Graph generatorGraph(int v, float p) {
	Graph g;
	float r = 0; // random
	srand(time(NULL));
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			r = (float)rand() / RAND_MAX;
			if (r >=p) {
				Edge e;
				e.src = i;
				e.dest = j;
				e.weight = (int)rand() % v + 1;
				g.listEdge.push_back(e);
			}
		}
	}

	g.E = g.listEdge.size();
	g.V = v;
	////print :
	//for (unsigned int j = 0; j < g.listEdge.size(); j++) {
	//	cout << g.listEdge[j].src << " -- " << g.listEdge[j].dest << "==" << g.listEdge[j].weight << endl;
	//}

	return g;

}
int main()
{
	//
	//int V = 4, E = 5;
	Graph g;
	//g.V = V;
	//g.E = E;

	//Edge e;

	//// add edge 0-1 

	//e.src = 0;
	//e.dest = 1;
	//e.weight = 10;
	//g.Edge.push_back(e);


	//// add edge 0-2 

	//e.src = 0;
	//e.dest = 2;
	//e.weight = 6;
	//g.Edge.push_back(e);

	////add edge 0-3 
	//e.src = 0;
	//e.dest = 3;
	//e.weight = 5;
	//g.Edge.push_back(e);
	////add edge 1-3 
	//e.src = 1;
	//e.dest = 3;
	//e.weight = 15;
	//g.Edge.push_back(e);
	////add edge 2-3 
	//e.src = 2;
	//e.dest = 3;
	//e.weight = 4;
	//g.Edge.push_back(e);

	g = generatorGraph(1000, 0.8);
	Kruskal test;
	test.kruskalMST(g);
	test.kruskalMSTv2(g);

	
	
	return 0;
}

