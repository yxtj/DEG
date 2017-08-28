#include <iostream>
#include <vector>
#include <string>
#include "Option.h"
#include "tg-io.h"
#include "libutil/IndexMapper.h"
#include "libcommon/Subject.h"
#include "libteg/TemporalEdgeGraph.h"

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

int main(int argc, char* argv[]) {
	Option opt;
	if(!opt.parseInput(argc, argv)) {
		cerr << "Error in parsing options." << endl;
		return 1;
	}
	if(opt.show) {
		cout << "Input folder:  " << opt.gPath << "\n"
			<< "Output folder: " << opt.tgPath << "\n"
			<< "# of subjects: " << opt.nSubject << ", "
			<< "# of skipped: " << opt.nSkip << ", "
			<< "# of graphs: " << opt.nGraph << "\n"
			<< "Allow self-pointing: " << (opt.selfpoint?1:0)
			<< endl;
	}

	vector<pair<SubjectInfo, TemporalEdgeGraph>> tgs;
	try {
		cout << "Loading original graphs..." << endl;
		vector<Subject> subs = loadSubject(opt.gPath, opt.types, opt.nSubject, opt.nSkip, opt.nGraph);
		cout << "# of loaded subjects: " << subs.size() << endl;
		cout << "Converting to temporal edge graphs..." << endl;
		tgs.reserve(subs.size());
		for(auto& sub : subs)
			tgs.emplace_back(sub, transSubject2TEG(sub, opt.selfpoint));
	} catch(exception& e) {
		cerr << e.what() << endl;
		return 2;
	}
	cout << "Outputing temporal edge graphs..." << endl;
	outputTEGs(opt.tgPath, tgs);

	return 0;
}
