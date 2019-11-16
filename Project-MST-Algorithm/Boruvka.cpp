#pragma warning(disable : 4996)
#include "Boruvka.h"
using namespace std;
void Boruvka::Boruvka2(Graph g)
{
	UnionFind uf;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	vector<Edge> edge = g.listEdge;



	Subset* subs = new Subset[g.V*sizeof(Subset)];

	int* cheapest = new int[g.V];

		for (int v = 0; v < g.V; ++v)
		{
			subs[v].parent = v;
			subs[v].rank = 0;
			cheapest[v] = -1;
		}

		int numTrees = g.V;
		int MSTweight = 0;


		while (numTrees > 1)
		{

			for (int v = 0; v < g.V; ++v)
			{
				cheapest[v] = -1;
			}


			for (int i = 0; i < g.E; i++)
			{

				int set1 = uf.find2(subs, edge[i].src);
				int set2 = uf.find2(subs, edge[i].dest);


				if (set1 == set2)
					continue;

				else
				{
					if (cheapest[set1] == -1 ||
						edge[cheapest[set1]].weight > edge[i].weight)
						cheapest[set1] = i;

					if (cheapest[set2] == -1 ||
						edge[cheapest[set2]].weight > edge[i].weight)
						cheapest[set2] = i;
				}
			}


			for (int i = 0; i < g.V; i++)
			{

				if (cheapest[i] != -1)
				{
					int set1 = uf.find2(subs, edge[cheapest[i]].src);
					int set2 = uf.find2(subs, edge[cheapest[i]].dest);

					if (set1 == set2)
						continue;
					MSTweight += edge[cheapest[i]].weight;

					uf.Union2(subs, set1, set2);
					numTrees--;
				}
			}
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = std::chrono::system_clock::to_time_t(end);
		//Print
		cout << "Boruvka Version 2 :" << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time: " << elapsed_seconds.count() << " s\n";
		printf("Weight of MST is %d\n", MSTweight);
		delete[]cheapest;
		delete[] subs;
		return;

}

void Boruvka::Boruvka1(Graph g)
{
	UnionFind uf;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	vector<Edge> edge = g.listEdge;


	int* arr = new int[g.V * sizeof(int)];

	int* cheapest = new int[g.V];

	memset(arr, -1, sizeof(int) * g.V);

		for (int v = 0; v < g.V; ++v)
		{
			cheapest[v] = -1;
		}

		// initialisation
		int numTrees = g.V;
		int MSTweight = 0;

		// Tant que G n'est pas réduit à un sommet faire :
		while (numTrees > 1)
		{
			// Initialise le tableau cheapset
			for (int v = 0; v < g.V; ++v)
			{
				cheapest[v] = -1;
			}

			// Parcours toutes les arêtes et met à jour le tableau cheapset
			for (int i = 0; i < g.E; i++)
			{

				int set1 = uf.find(arr, edge[i].src);
				int set2 = uf.find(arr, edge[i].dest);

				if (set1 == set2)
					continue;

				else
				{
					if (cheapest[set1] == -1 ||
						edge[cheapest[set1]].weight > edge[i].weight)
						cheapest[set1] = i;

					if (cheapest[set2] == -1 ||
						edge[cheapest[set2]].weight > edge[i].weight)
						cheapest[set2] = i;
				}
			}

			for (int i = 0; i < g.V; i++)
			{

				if (cheapest[i] != -1)
				{
					int set1 = uf.find(arr, edge[cheapest[i]].src);
					int set2 = uf.find(arr, edge[cheapest[i]].dest);

					if (set1 == set2)
						continue;
					MSTweight += edge[cheapest[i]].weight;

					uf.Union(arr, set1, set2);
					numTrees--;
				}
			}
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = std::chrono::system_clock::to_time_t(end);
		//Print
		cout << "Boruvka Version 1 :" << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time: " << elapsed_seconds.count() << " s\n";
		printf("Weight of MST is %d\n", MSTweight);
		delete[]cheapest;
		delete[] arr;
		return;
}
