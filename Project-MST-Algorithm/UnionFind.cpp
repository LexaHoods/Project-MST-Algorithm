#include "UnionFind.h"
#include "Subset.h"
#include "Kruskal.h"
#include "Graph.h"
#include "Subset.h"
#include<iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
//---- Union find simple----
// function find is data structure manipulation function
int UnionFind::find(int arr[], int i)
{
	if (arr[i] == -1)
		return i;
	return find(arr, arr[i]);
}

// function Union is data structure manipulation fonction
void UnionFind::Union(int arr[], int x, int y)
{
	int xset = find(arr, x);
	int yset = find(arr, y);
	if (xset != yset)
	{
		arr[xset] = yset;
	}
}

//---- Union find optimize / Union By Rank and Path Compression ----

int UnionFind::find2(Subset sub[], int i) {
	if (sub[i].parent != i) {
		sub[i].parent = find2(sub, sub[i].parent);
	}
	return sub[i].parent;
}

void UnionFind::Union2(Subset sub[], int x, int y) {
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
