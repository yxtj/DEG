#include "TemporalEdgeGraph.h"
#include "util-teg.h"

using namespace std;

TemporalEdgeGraph::TemporalEdgeGraph():nEdges(0)
{
}

TemporalEdgeGraph::TemporalEdgeGraph(Subject& sub, const bool selfpoint){
	vector<vector<int>> snapshots;
	snapshots.reserve(sub.graphs.size());
	for(Graph& g : sub.graphs) {
		snapshots.push_back(move(getEdgeSequence(g, selfpoint)));
	}
	int nNodes = sub.getnNode();
	int nEdges = selfpoint ? nNodes*(nNodes + 1) / 2 : (nNodes - 1)*nNodes / 2;

	addNodes(snapshots[0]);
	int last_off = 0;
	for(size_t i = 1; i < snapshots.size(); ++i) {
		vector<int>& last = snapshots[i - 1];
		vector<int>& curr = snapshots[i];
		int curr_off = getnNode();
		addNodes(curr);
		vector<int> nowID(curr.size());
		for(size_t j = 0; j < curr.size(); ++j)
			nowID[j] = curr_off + j;	// index is node id, content is node label
		for(size_t j = 0; j < last.size(); ++j)
			addEdges(last_off + j, nowID);
		last_off = curr_off;
	}
}

void TemporalEdgeGraph::setNodes(const std::vector<label_t>& vec){
	nodes=vec;
	edges.assign(nodes.size(), {});
	nEdges=0;
}

void TemporalEdgeGraph::setNodes(std::vector<label_t>&& vec){
	nodes=move(vec);
	edges.assign(nodes.size(), {});
	nEdges=0;
}

void TemporalEdgeGraph::setNodesUnique(const int n, const int start){
	nodes.clear();
	nodes.reserve(n);
	int end=start+n;
	for(int i=start;i<end;++i){
		nodes.push_back(i);
	}
	edges.assign(nodes.size(), {});
	nEdges=0;
}
void TemporalEdgeGraph::setNodesIdentical(const int n, const int lbl){
	nodes.assign(n, lbl);
	edges.assign(nodes.size(), {});
	nEdges=0;
}

int TemporalEdgeGraph::addNode(const label_t lbl){
	nodes.push_back(lbl);
	edges.push_back({});
	return static_cast<int>(nodes.size()-1);
}
int TemporalEdgeGraph::addNodes(const std::vector<label_t>& vec){
	nodes.insert(nodes.end(), vec.begin(), vec.end());
	edges.resize(nodes.size());
	return static_cast<int>(nodes.size()-1);
}
void TemporalEdgeGraph::addEdge(const int s, const int d){
	edges[s].push_back(d);
	++nEdges;
}
void TemporalEdgeGraph::addEdges(const int s, const std::vector<int>& ds){
	edges[s].insert(edges[s].end(), ds.begin(), ds.end());
	nEdges+=ds.size();
}

