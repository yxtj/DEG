#include "io.h"
#include <fstream>
#include <limits>
#include <boost/filesystem.hpp>

using namespace std;

Graph loadGraph(istream& is) {
	Graph res;
	res.readFromStream(is);
	return res;
}

std::vector<std::pair<SubjectInfo, std::vector<std::string>>> getSubjectFilenames(
	const std::string & folder, const std::vector<int>& types, int nSub, int nSkip, int nGraph)
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

	if(nGraph > 0) {
		size_t limit = nGraph;
		for(auto& unit : maps) {
			if(unit.second.size() > limit)
				unit.second.resize(nGraph);
		}
	}
	
	return maps;
}

std::vector<Subject> loadSubject(const std::string& folder, const std::vector<int>& types,
	int nSub, int nSkip, int nGraph)
{
	vector<pair<SubjectInfo, vector<string>>> subs = getSubjectFilenames(
		folder, types, nSub, nSkip, nGraph);
	return loadSubject(folder, subs);
}

std::vector<Subject> loadSubject(const std::string & folder,
	const std::vector<std::pair<SubjectInfo, std::vector<std::string>>>& subs)
{
	vector<Subject> res;
	for(auto& p : subs) {
		Subject sub(p.first);
		for(auto& fn : p.second) {
			ifstream fin(folder + fn);
			sub.graphs.push_back(move(loadGraph(fin)));
		}
		res.push_back(move(sub));
	}
	return res;
}
