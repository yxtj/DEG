#pragma once
#include "libcommon/Edge.h"
//#include <vector>
#include <map>
//#include <set>
#include <unordered_map>

struct TemporalEdgeMotif {
private:
	int nEdges;
public:
	//std::unordered_map<int, int> nodes; // idx, label
	std::unordered_map<int, int> nodes; // idx, label

	// start both direction without label
	std::map<int, std::vector<int>> edges, edges_r; // src-idx, (dst-idx)*n
	//std::set<Edge> edges; // edge

	int addNode(const int label); // use default idx as current number of nodes.
	int addNode(const int idx, const int label);
	void addEdge(const int src_idx, const int dst_idx, const int label);

	bool check() const; // check whether it is a valid motif (connected and all nodes are used)
	bool sortup(); // sort the edges in dfs order (new edge must be expanded from visted nodes)
};
