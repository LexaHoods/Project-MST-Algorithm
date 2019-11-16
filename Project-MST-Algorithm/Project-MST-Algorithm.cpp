//Project Arbre Couvrant Minimal / Minimum Spanning Tree
//Axel Houdayer - IATIC4

#include "Edge.h"
#include "Graph.h"
#include "UnionFind.h"
#include "Kruskal.h"
#include "Boruvka.h"
#include "Prim.h"
#include <iostream>
#include <random>
#include <time.h>

using namespace std;
Graph generatorGraph(int v, float p) {
	Graph g;
	g.V=v;
	//initializes the matrix with 0
	g.matrix.resize(v, std::vector<int>(v, 0));
	float r = 0; // random
	srand(time(NULL));
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			r = (float)rand() / RAND_MAX;
			if (r >= p) {
				//List edge representation
				Edge e;
				int weight = (int)rand() % v + 1;
				e.src = i;
				e.dest = j;
				e.weight = weight;
				g.listEdge.push_back(e);
				//Adjacency matrix representation
				g.matrix[i][j]=weight;
				g.matrix[j][i]=weight;
			}
		}
	}

	g.E = g.listEdge.size();
	cout << "nbr E : " << g.E << endl;
	////print :
	//for (unsigned int j = 0; j < g.listEdge.size(); j++) {
	//	cout << g.listEdge[j].src << " -- " << g.listEdge[j].dest << "==" << g.listEdge[j].weight << endl;
	//}

	return g;

}
//Debug matrix :
// void print(Graph g) {
// 	for(int i=0; i<g.matrix.size();i++){
// 		for(int j=0;j<g.matrix[i].size();j++){
// 			printf(" %d\t",g.matrix[i][j]);
// 		}
// 		printf("\n");
// 	}
// }
int main()
{

	Graph g;

	g = generatorGraph(9000, 0.2);
	Kruskal test;
	Boruvka test2;
	Prim test3;
	//print(g);
	test3.prim1(g);
	test.kruskalMST(g);
	test.kruskalMSTv2(g);
	test2.Boruvka2(g);
	test2.Boruvka1(g);


	return 0;
}
