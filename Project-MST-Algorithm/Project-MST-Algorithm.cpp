//Project Minimum Spanning Tree
//Axel Houdayer - IATIC4
#include <iostream> 
#include "Edge.h"
#include "Graph.h"
#include "Kruskal.h"
#include "UnionFind.h"
#include <random>
#include <time.h>
#include "Boruvska.h"


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
	cout << "nbr E : " << g.E << endl;
	////print :
	//for (unsigned int j = 0; j < g.listEdge.size(); j++) {
	//	cout << g.listEdge[j].src << " -- " << g.listEdge[j].dest << "==" << g.listEdge[j].weight << endl;
	//}

	return g;

}
int main()
{
	//
	//int V = 5, E = 7;
	Graph g;
	//g.V = V;
	//g.E = E;

	//Edge e;

	// //add edge P-NP 

	//e.src = 0;
	//e.dest = 1;
	//e.weight = 18;
	//g.listEdge.push_back(e);

	////add edge NP-M
	//e.src = 1;
	//e.dest = 2;
	//e.weight = 442;
	//g.listEdge.push_back(e);

	////add edge M-C
	//e.src = 2;
	//e.dest = 3;
	//e.weight = 490;
	//g.listEdge.push_back(e);
	//
	////add edge C-V
	//e.src = 3;
	//e.dest = 4;
	//e.weight = 80;
	//g.listEdge.push_back(e);

	////add edge V-P
	//e.src = 4;
	//e.dest = 0;
	//e.weight = 21;
	//g.listEdge.push_back(e);

	////add edge P-C
	//e.src = 0;
	//e.dest = 3;
	//e.weight = 91;
	//g.listEdge.push_back(e);

	////add edge P-M
	//e.src = 0;
	//e.dest = 2;
	//e.weight = 450;
	//g.listEdge.push_back(e);


	g = generatorGraph(100, 0.2);
	Kruskal test;
	Boruvska test2;
	//test.print(g);
	test.kruskalMST(g);
	test.kruskalMSTv2(g);
	test2.Boruvska2(g);

	return 0;
}

