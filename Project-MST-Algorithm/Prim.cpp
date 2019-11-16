#pragma warning(disable : 4996)
#include "Prim.h"
#include "Graph.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
///Timer stuff
#include <ctime>
#include <chrono>
/*Fonction qui permet de trouver le sommet avec la valeur de clé minimale,
à partir de l'ensemble des sommets qui ne sont pas encore inclus dans ACM */
int minKey(int key[], bool acmSet[],int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (acmSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

//Algorithme Prim avec la représentation de graphe en matrice d'adjacence (Version 1)

void Prim::prim1(Graph g)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
  int MSTweight = 0;
	int parent[g.V];
	int key[g.V];
	bool acmSet[g.V];

	for (int i = 0; i < g.V; i++){
    key[i] = INT_MAX;
    acmSet[i] = false;
  }

	key[0] = 0;
	parent[0] = -1;

	for (int j = 0; j < (g.V - 1); j++)
	{
		int u = minKey(key, acmSet,g.V);
		acmSet[u] = true;
		for (int v = 0; v < g.V; v++){
      if (g.matrix[u][v] && acmSet[v] == false && g.matrix[u][v]< key[v]){
        	parent[v] = u;
          key[v] = g.matrix[u][v];
      }
    }
	}
  end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = std::chrono::system_clock::to_time_t(end);


  for (int i = 0; i <g.V; i++)
        MSTweight+=g.matrix[i][parent[i]];


  std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time Prim version 1 : " << elapsed_seconds.count() << " s\n"
		<< " Weight MST : "<<MSTweight<<endl;
return;
}
