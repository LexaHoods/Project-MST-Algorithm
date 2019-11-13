#pragma warning(disable : 4996)
#include "Boruvska.h"
using namespace std;
void Boruvska::Boruvska2(Graph g)
{
	UnionFind uf;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	vector<Edge> edge = g.listEdge;

	// Allocate memory for creating V subsets.

	Subset* subs = new Subset[g.V*sizeof(Subset)];

	// An array to store index of the cheapest edge of
	// subset.
	int* cheapest = new int[g.V];

		// Create V subsets with single elements
		for (int v = 0; v < g.V; ++v)
		{
			subs[v].parent = v;
			subs[v].rank = 0;
			cheapest[v] = -1;
		}

		// Initially there are V different trees.
		// Finally there will be one tree that will be MST
		int numTrees = g.V;
		int MSTweight = 0;

		// Keep combining components (or sets) until all
		// compnentes are not combined into single MST.
		while (numTrees > 1)
		{
			// Everytime initialize cheapest array
			for (int v = 0; v < g.V; ++v)
			{
				cheapest[v] = -1;
			}

			// Traverse through all edges and update
			// cheapest of every component
			for (int i = 0; i < g.E; i++)
			{
				// Find components (or sets) of two corners
				// of current edge
				int set1 = uf.find2(subs, edge[i].src);
				int set2 = uf.find2(subs, edge[i].dest);

				// If two corners of current edge belong to
				// same set, ignore current edge
				if (set1 == set2)
					continue;

				// Else check if current edge is closer to previous
				// cheapest edges of set1 and set2
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

			// Consider the above picked cheapest edges and add them
			// to MST
			for (int i = 0; i < g.V; i++)
			{

				// Check if cheapest for current set exists
				if (cheapest[i] != -1)
				{
					int set1 = uf.find2(subs, edge[cheapest[i]].src);
					int set2 = uf.find2(subs, edge[cheapest[i]].dest);

					if (set1 == set2)
						continue;
					MSTweight += edge[cheapest[i]].weight;
					/*printf("Edge %d-%d included in MST\n",
						edge[cheapest[i]].src, edge[cheapest[i]].dest);*/

					// Do a union of set1 and set2 and decrease number
					// of trees
					uf.Union2(subs, set1, set2);
					numTrees--;
				}
			}
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = std::chrono::system_clock::to_time_t(end);
		//Print
		cout << "Boruvska Version 2 :" << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time: " << elapsed_seconds.count() << " s\n";
		printf("Weight of MST is %d\n", MSTweight);
		delete[]cheapest;
		delete[] subs;
		return;

}

void Boruvska::Boruvska1(Graph g)
{
	UnionFind uf;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	vector<Edge> edge = g.listEdge;

	// Allocate memory for creating V subsets
	int* arr = new int[g.V * sizeof(int)];
	// An array to store index of the cheapest .
	int* cheapest = new int[g.V];
	// Initialize all subsets as single element sets
	memset(arr, -1, sizeof(int) * g.V);
		// Create V subsets with single elements
		for (int v = 0; v < g.V; ++v)
		{
			cheapest[v] = -1;
		}

		// Initially there are V different trees.
		// Finally there will be one tree that will be MST
		int numTrees = g.V;
		int MSTweight = 0;

		// Keep combining components (or sets) until all
		// compnentes are not combined into single MST.
		while (numTrees > 1)
		{
			// Everytime initialize cheapest array
			for (int v = 0; v < g.V; ++v)
			{
				cheapest[v] = -1;
			}

			// Traverse through all edges and update
			// cheapest of every component
			for (int i = 0; i < g.E; i++)
			{
				// Find components (or sets) of two corners
				// of current edge
				int set1 = uf.find(arr, edge[i].src);
				int set2 = uf.find(arr, edge[i].dest);

				// If two corners of current edge belong to
				// same set, ignore current edge
				if (set1 == set2)
					continue;

				// Else check if current edge is closer to previous
				// cheapest edges of set1 and set2
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

			// Consider the above picked cheapest edges and add them
			// to MST
			for (int i = 0; i < g.V; i++)
			{

				// Check if cheapest for current set exists
				if (cheapest[i] != -1)
				{
					int set1 = uf.find(arr, edge[cheapest[i]].src);
					int set2 = uf.find(arr, edge[cheapest[i]].dest);

					if (set1 == set2)
						continue;
					MSTweight += edge[cheapest[i]].weight;
					/*printf("Edge %d-%d included in MST\n",
						edge[cheapest[i]].src, edge[cheapest[i]].dest);*/

					// Do a union of set1 and set2 and decrease number
					// of trees
					uf.Union(arr, set1, set2);
					numTrees--;
				}
			}
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		time_t end_time = std::chrono::system_clock::to_time_t(end);
		//Print
		cout << "Boruvska Version 1 :" << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time: " << elapsed_seconds.count() << " s\n";
		printf("Weight of MST is %d\n", MSTweight);
		delete[]cheapest;
		delete[] arr;
		return;
}
