#include "tg-io.h"
#include <fstream>
#include <functional>
#include <limits>
#include <boost/filesystem.hpp>

using namespace std;

Graph loadGraph(istream& is) {
	Graph res;
	res.readFromStream(is);
	return res;
}

std::vector<Subject> loadSubject(const std::string& folder, const std::vector<int>& types,
	int nSub, int nSkip, int nGraph)
{
	using namespace boost::filesystem;
	path root(folder);
	if(!exists(root)) {
		throw invalid_argument("cannot open graph folder: " + folder);
	}
	function<bool(const int)> fn_skip_type;
	if(types.empty())
		fn_skip_type = [](const int) {return false; };
	else
		fn_skip_type = [&](const int t) {return find(types.begin(), types.end(), t) == types.end(); };
	vector<string> fns;
	for(auto it = directory_iterator(root); it != directory_iterator(); ++it) {
		string fn = it->path().filename().string();
		SubjectInfo sub;
		if(!sub.parseFromFilename(fn) || fn_skip_type(sub.type))
			continue;
		fns.emplace_back(move(fn));
	}
	vector<pair<SubjectInfo, vector<string>>> maps = SubjectInfo::groupBySubjectID(fns);
	if(nSub > 0)
		maps.erase(maps.begin() + nSkip + nSub, maps.end());
	if(nSkip > 0)
		maps.erase(maps.begin(), maps.begin() + nSkip);
	
	size_t limit = nGraph > 0 ? static_cast<size_t>(nGraph) : numeric_limits<size_t>::max();
	vector<Subject> res;
	for(auto& p : maps) {
		Subject sub(p.first);
		size_t end = min(limit, p.second.size());
		for(size_t i = 0; i < end; ++i) {
			ifstream fin(folder + p.second[i]);
			sub.graphs.push_back(move(loadGraph(fin)));
		}
		res.push_back(move(sub));
	}
	return res;
}

bool outputTemporalEdgeGraph(std::ostream& os, const TemporalEdgeGraph& g)
{
	for(size_t i = 0; i < g.nodes.size(); ++i) {
		os << "v " << i << " " << g.nodes[i] + 2 << "\n";
	}
	for(size_t i = 0; i < g.edges.size(); ++i) {
		auto& list = g.edges[i];
		for(size_t j = 0; j < list.size(); ++j)
			os << "e " << i << " " << list[j] << " " << 2 << "\n";
	}
	return true;
}

bool outputTEGs(const std::string & folder, const std::vector<std::pair<SubjectInfo, TemporalEdgeGraph>>& vec)
{
	using namespace boost::filesystem;
	path root(folder);
	if(!exists(root)) {
		create_directories(root);
	}
	/*
	for(auto& p : vec) {
		ofstream fout(folder + p.first.genFilename());
		if(!fout)
			return false;
		if(!outputTemporalEdgeGraph(fout, p.second))
			return false;
	} */
	ofstream fout(folder + "teg.txt");
	if(!fout)
		return false;
	for(size_t i = 0; i < vec.size(); ++i) {
		auto& p = vec[i];
		fout << "t # " << i << "\n";
		if(!outputTemporalEdgeGraph(fout, p.second))
			return false;
	}
	fout << "t # -1" << "\n";
	return true;
}
