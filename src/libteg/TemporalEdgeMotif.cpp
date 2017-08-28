#include "TemporalEdgeMotif.h"
#include <algorithm>
#include <set>

using namespace std;

int TemporalEdgeMotif::addNode(const int label)
{
	nodes[nodes.size()] = label;
	return static_cast<int>(nodes.size());
}

int TemporalEdgeMotif::addNode(const int idx, const int label)
{
	nodes[idx] = label;
	return static_cast<int>(nodes.size());
}

void TemporalEdgeMotif::addEdge(const int src_idx, const int dst_idx, const int label)
{
	int s = min(src_idx, dst_idx);
	int d = max(src_idx, dst_idx);
//	edges[make_pair(s, d)] = label;
//	edges.emplace(s, d);
	edges[s].push_back(d);
	edges_r[d].push_back(s);
}

static int UF_find(unordered_map<int, int>& color, int p) {
	vector<int> stack;
	while(color[p] != p) {
		p = color[p];
		stack.push_back(p);
	}
	for(int v : stack)
		color[v] = p;
	return p;
}
static void UF_set(unordered_map<int, int>& color, int p, const int v) {
	while(color[p] != v) {
		int pn = color[p];
		color[p] = v;
		p = pn;
	}
}
static void UF_go(unordered_map<int, int>& color, const map<int, vector<int>>& elist) {
	for(auto& line : elist) {
		int src = line.first;
		for(int dst : line.second) {
			int nc = min(UF_find(color, src), UF_find(color, dst));
			UF_set(color, src, nc);
			UF_set(color, dst, nc);
		}
	}
}


bool TemporalEdgeMotif::check() const
{
	if(edges.empty() || nodes.empty())
		return edges.empty() && nodes.empty();
	unordered_map<int, int> color(nodes.size());
	for(pair<int, int> nc : nodes)
		color[nc.first] = nc.first;
	UF_go(color, edges);
	int v = color.begin()->second;
	for(auto& nc : nodes) {
		if(UF_find(color, nc.first) != v)
			return false;
	}
	return true;
}

bool TemporalEdgeMotif::sortup()
{
	for(auto& line : edges)
		sort(line.second.begin(), line.second.end());
	for(auto& line : edges_r)
		sort(line.second.begin(), line.second.end());
	return true;
}
