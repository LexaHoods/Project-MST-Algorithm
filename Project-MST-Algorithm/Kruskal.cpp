#pragma warning(disable : 4996)
#include "Kruskal.h"
#include "Graph.h"
#include "Subset.h"
#include<iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
///Timer stuff
#include <ctime>
#include <chrono>
#include "UnionFind.h"
//fonction de comparaison pour qsort
int comp(const void* a, const void* b) {
	Edge* e1 = (Edge*)a;
	Edge* e2 = (Edge*)b;
	return e1->weight > e2->weight;
}

//Kruskal v1 by Union Find
UnionFind uf;
void Kruskal::kruskalMST(Graph g) {

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	Graph result;
	int e = 0;
	int i = 0;
	int MSTweight = 0;
	//1ère étape : trier les arêtes
	qsort(&g.listEdge[0], g.E, sizeof(g.listEdge[0]),comp);


	int* arr = new int[g.V * sizeof(int)];

	// Initialisation de tous les sous ensembles
	memset(arr, -1, sizeof(int) * g.V);
	//Etape 2 :
	while (e < (g.V) - 1 && i < g.E) {
		Edge next_e = g.listEdge[i++];
		int x = uf.find(arr, next_e.src);
		int y = uf.find(arr, next_e.dest);
		if (x != y) {
			result.listEdge.push_back(next_e);
			e++;
			uf.Union(arr, x, y);
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);

	for (int k = 0; k < result.listEdge.size(); k++) {
		MSTweight += result.listEdge[k].weight;
	}
	//Print

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "Kruskalv1 elapsed time: " << elapsed_seconds.count() << " s\n"
		<< " Weight MST : "<<MSTweight<<endl;

	/*cout << "Print result Kruskal v1 : " << endl;
	for (unsigned int j = 0; j < result.listEdge.size(); j++) {
		cout << result.listEdge[j].src << " -- " << result.listEdge[j].dest << "==" << result.listEdge[j].weight<<endl;
	}*/
	delete[] arr;
	return;
}


//Kruskalv2 by Union Find optimize
void Kruskal::kruskalMSTv2(Graph g) {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Graph result;
	int e = 0;
	int i = 0;

	qsort(&g.listEdge[0], g.E, sizeof(g.listEdge[0]), comp);


	Subset* sub = new Subset[g.V * sizeof(Subset)];
	// Creation de V sous ensembles
	for (int v = 0; v < g.V; ++v) {
		sub[v].parent = v;
		sub[v].rank = 0;
		}
	//Etape 2 :
	while (e < (g.V) - 1 && i < g.E) {
		Edge next_e = g.listEdge[i++];
		int x = uf.find2(sub, next_e.src);
		int y = uf.find2(sub, next_e.dest);
		if (x != y) {
			result.listEdge.push_back(next_e);
			e++;
			uf.Union2(sub, x, y);
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);
	//Print
	cout <<"Kruskal Version 2 :"<< "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << " s\n";
	/*cout << "Print result Kruskal v2 : " << endl;
	for (unsigned int j = 0; j < result.listEdge.size(); j++) {
		cout << result.listEdge[j].src << " -- " << result.listEdge[j].dest << "==" << result.listEdge[j].weight << endl;
	}*/
	delete[]sub;
	return;
}
