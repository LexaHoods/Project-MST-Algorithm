#pragma once
#include "Subset.h"
class UnionFind
{
public:
	int find(int arr[], int i);
	void Union(int arr[], int x, int y);
	int find2(Subset sub[], int i);
	void Union2(Subset sub[], int x, int y);
};

