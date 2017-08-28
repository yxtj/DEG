#pragma once
#include <vector>
//#include <utility>
#include <iostream>
#include "libcommon/Subject.h"

typedef int label_t;

/**
  Only nodes have label.
*/
struct TemporalEdgeGraph
{
	std::vector<label_t> nodes; // nodes[idx]=label
	std::vector<std::vector<int>> edges; // adjcent list
private:
	size_t nEdges;
public:
	TemporalEdgeGraph();
	TemporalEdgeGraph(Subject& sub, const bool selfpoint = true);

	size_t getnNode() const { return nodes.size(); }
	size_t getnEdge() const { return nEdges; }

	void setNodes(const std::vector<label_t>& vec);
	void setNodes(std::vector<label_t>&& vec);
	void setNodesUnique(const int n, const int start);
	void setNodesIdentical(const int n, const int lbl);
	
	int addNode(const label_t lbl);
	int addNodes(const std::vector<label_t>& vec);
	void addEdge(const int s, const int d);
	void addEdges(const int s, const std::vector<int>& ds);
};

