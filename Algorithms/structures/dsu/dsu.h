#ifndef ALGO_DSU_H_
#define ALGO_DSU_H_

#include <vector>

class dsu
{
public:
	dsu(int n);
	void reinit_dsu(int n);
	void make(int r);
	int find(int elem);
	int unite(int s1, int s2);
private:
	std::vector<int> parent;
	std::vector<int> rank;
};


#endif
