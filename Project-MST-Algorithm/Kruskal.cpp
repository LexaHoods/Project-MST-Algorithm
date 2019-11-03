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

//---- Union find simple----
// function find is data structure manipulation function
int find(int arr[], int i)
{
	if (arr[i] == -1)
		return i;
	return find(arr, arr[i]);
}

// function Union is data structure manipulation fonction
void Union(int arr[], int x, int y)
{
	int xset = find(arr, x);
	int yset = find(arr, y);
	if (xset != yset)
	{
		arr[xset] = yset;
	}
}

//---- Union find optimize / Union By Rank and Path Compression ----

int find2(Subset sub[], int i) {
	if (sub[i].parent != i) {
		sub[i].parent = find2(sub, sub[i].parent);
	}
	return sub[i].parent;
}

void Union2(Subset sub[], int x, int y) {
	int xset = find2(sub, x);
	int yset = find2(sub, y);
	if (sub[xset].rank < sub[yset].rank) {
		sub[xset].parent = yset;
	}
	else if (sub[xset].rank > sub[yset].rank) {
		sub[yset].parent = xset;
	}
	else {
		sub[yset].parent = xset;
		sub[xset].rank++;
	}
}



//comparaison function for qsort
int comp(const void* a, const void* b) {
	Edge* e1 = (Edge*)a;
	Edge* e2 = (Edge*)b;
	return e1->weight > e2->weight;
}

//Kruskal v1 by Union Find

void Kruskal::kruskalMST(Graph g) {

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	Graph result;
	int e = 0;
	int i = 0;
	//Step 1 : Sort all the edges, order of their weight :
	qsort(&g.listEdge[0], g.E, sizeof(g.listEdge[0]),comp);

	// Allocate memory for creating V subsets 
	int* arr = new int[g.V * sizeof(int)];

	// Initialize all subsets as single element sets 
	memset(arr, -1, sizeof(int) * g.V);
	//Step 2 : 
	while (e < (g.V) - 1 && i < g.E) {
		Edge next_e = g.listEdge[i++];
		int x = find(arr, next_e.src);
		int y = find(arr, next_e.dest);
		if (x != y) {
			result.listEdge.push_back(next_e);
			e++;
			Union(arr, x, y);
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);


	//Print 

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << " s\n";
	/*cout << "Print result Kruskal v1 : " << endl;
	for (unsigned int j = 0; j < result.listEdge.size(); j++) {
		cout << result.listEdge[j].src << " -- " << result.listEdge[j].dest << "==" << result.listEdge[j].weight<<endl;
	}*/
	return;
}


//Kruskalv2 by Union Find optimize
void Kruskal::kruskalMSTv2(Graph g) {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Graph result;
	int e = 0;
	int i = 0;
	//Step 1 : Sort all the edges, order of their weight :
	qsort(&g.listEdge[0], g.E, sizeof(g.listEdge[0]), comp);

	// Allocate memory for creating V ssubsets 
	Subset* sub = new Subset[g.V * sizeof(Subset)];
	// Create V subsets :
	for (int v = 0; v < g.V; ++v) {
		sub[v].parent = v;
		sub[v].rank = 0;
		}
	//Step 2 : 
	while (e < (g.V) - 1 && i < g.E) {
		Edge next_e = g.listEdge[i++];
		int x = find2(sub, next_e.src);
		int y = find2(sub, next_e.dest);
		if (x != y) {
			result.listEdge.push_back(next_e);
			e++;
			Union2(sub, x, y);
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);
	//Print 
	cout <<"Version 2 :"<< "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << " s\n";
	/*cout << "Print result Kruskal v2 : " << endl;
	for (unsigned int j = 0; j < result.listEdge.size(); j++) {
		cout << result.listEdge[j].src << " -- " << result.listEdge[j].dest << "==" << result.listEdge[j].weight << endl;
	}*/
	return;
}
//Debug function : 
void Kruskal::print(Graph g)
{
	for (unsigned int i = 0; i < g.listEdge.size(); i++) {
		printf("i = %d , valweight= %d\n", i, g.listEdge[i].weight);
	}
}