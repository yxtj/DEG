#include "util-teg.h"
#include "libutil/IndexMapper.h"
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getEdgeSequence(const Graph& g, const bool selfpoint) {
	IndexMapper2DUndirected mapper(selfpoint);
	vector<int> res;
	int n = g.getnNode();
	for(int i = 0; i < n; ++i) {
		int end = i + (selfpoint ? 1 : 0);
		for(int j = 0; j < end; ++j)
			if(g.matrix[i][j])
				res.push_back(mapper.seq(i, j));
	}
	return res;
}

// pre-condition: label of pm and pg matches i.e., m.nodes[pm] == g.nodes[pg]
static bool dfsCheck(const TemporalEdgeGraph & g, const TemporalEdgeMotif & m, int pg, int pm, vector<bool>& used)
{
	if(static_cast<int>(m.edges.size()) >= pm)
		return true;
	for(int oth_idx_m : m.edges.at(pm)) {
		if(used[oth_idx_m])
			continue;
		int lbl_m = m.nodes.at(oth_idx_m);
		for(auto& oth_g : g.edges.at(pg)) {
			int lbl_g = g.nodes.at(oth_g);
			if(lbl_m == lbl_g) {
				
			}
		}

	}
	return false;
}

// return a list of matching list (idx-m -> idx-g)
vector<vector<int>> _one_node_match(const TemporalEdgeMotif & m, const TemporalEdgeGraph & g,
	map<int, int>& matched, set<int>& unchecked, const int pm)
{
	vector<vector<int>> res;

	return res;
}

// pre-condition: pm is in unchecked
static bool _level_contian_check(const TemporalEdgeMotif & m, const TemporalEdgeGraph & g,
	map<int, int>& matched, set<int>& unchecked, const int pm)
{
	if(unchecked.empty())
		return true;
	vector<int> out_nodes = m.edges.at(pm);
	for(auto& p : matched)
		out_nodes.erase(lower_bound(out_nodes.begin(), out_nodes.end(), p.first));
	{
		size_t i = 0;
		while(i < out_nodes.size()) {
			if(unchecked.find(out_nodes[i]) == unchecked.end())
				out_nodes.erase(out_nodes.begin() + i);
		}
	}
		
	auto X = _one_node_match(m, g, matched, unchecked, pm);
	for(auto& x : X) {
		// matched_x <- match + x
		for(size_t i = 0;i<out_nodes.size();++i) {
			matched.emplace(out_nodes[i], x[i]);
		}
		bool flag = true;
		for(auto& on : out_nodes) {
			if(!_level_contian_check(m, g, matched, unchecked, on)) {
				flag = false;
				break;
			}
			unchecked.erase(on);
		}
		if(!flag) {
			unchecked.insert(out_nodes.begin(), out_nodes.end());
		}
		// clear matched
		for(const int& on : out_nodes) {
			matched.erase(on);
		}
	}
	return unchecked.empty();
}

bool contains(const TemporalEdgeGraph & g, const TemporalEdgeMotif & m)
{
	if(m.nodes.empty())
		return true;
	int first_node = m.edges.begin()->first;
	int first_type = m.nodes.at(first_node);
	int n = g.getnNode();

	map<int, int> matched;
	set<int> unchecked;
	for(auto& p : m.nodes)
		unchecked.insert(p.first);
	return _level_contian_check(m, g, matched, unchecked, first_node);
	return false;
}

/*
TemporalEdgeGraph transSubject2TEG(Subject& sub, const bool selfpoint) {
	vector<vector<int>> snapshots;
	snapshots.reserve(sub.graphs.size());
	for(Graph& g : sub.graphs) {
		snapshots.push_back(move(getEdgeSequence(g, selfpoint)));
	}
	int nNodes = sub.getnNode();
	int nEdges = selfpoint ? nNodes*(nNodes + 1) / 2 : (nNodes - 1)*nNodes / 2;

	TemporalEdgeGraph res;
	res.addNodes(snapshots[0]);
	int last_off = 0;
	for(size_t i = 1; i < snapshots.size(); ++i) {
		vector<int>& last = snapshots[i - 1];
		vector<int>& curr = snapshots[i];
		int curr_off = res.getnNode();
		res.addNodes(curr);
		vector<int> nowID(curr.size());
		for(size_t j = 0; j < curr.size(); ++j)
			nowID[j] = curr_off + j;	// index is node id, content is node label
		for(size_t j = 0; j < last.size(); ++j)
			res.addEdges(last_off + j, nowID);
		last_off = curr_off;
	}
	return res;
}
*/
