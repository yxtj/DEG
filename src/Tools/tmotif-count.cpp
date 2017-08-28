#include "libutil/IndexMapper.h"
#include "libutil/Util.h"
#include "libcommon/Subject.h"
#include "libio/io.h"
#include "libteg/TemporalEdgeGraph.h"
#include "libteg/TemporalEdgeMotif.h"
#include "libteg/util-teg.h"
#include <boost/program_options.hpp>
#include <iostream>

using namespace std;

TemporalEdgeMotif parse2TEM(const string& line) {
	TemporalEdgeMotif res;
	size_t psep_old = 0;
	size_t psep = line.find(";", psep_old + 1);
	while(line[psep] == ' ')
		++psep;
	string temp = line.substr(psep_old, psep-psep_old);
	if(temp[0] == 'v') {
		size_t p0 = temp.find(' ', 2);
		while(temp[p0] == ' ')
			++p0;
		size_t p1 = temp.find(' ', p0 + 1);
		while(temp[p1] == ' ')
			++p1;
		res.addNode(stoi(temp.substr(p0, p1 - p0)), stoi(temp.substr(p1)));
	} else if(temp[0] == 'e') {
		size_t p0 = temp.find(' ', 2);
		while(temp[p0] == ' ')
			++p0;
		size_t p1 = temp.find(' ', p0 + 1);
		while(temp[p1] == ' ')
			++p1;
		size_t p2 = temp.find(' ', p1 + 1);
		while(temp[p2] == ' ')
			++p2;
		res.addEdge(stoi(temp.substr(p0, p1 - p0)), stoi(temp.substr(p1, p2 - p1)), stoi(temp.substr(p2)));
	}

	return res;
}

int main(int argc, char* argv[]){
	boost::program_options::variables_map vm;
	boost::program_options::options_description desc("Options", getScreenSize().first);
	try {
		using boost::program_options::value;
		desc.add_options()
			("help,h", "Print help messages")
			("gPath,i", value<string>()->required(), "The folder for original graphs (input).")
			("nSubject,n", value<int>()->default_value(0),
				"# of subjects to load (non-positive means load all).")
			("nSkip,s", value<int>()->default_value(0), "Skip the first <s> subjects (used for restart from failure).")
			("nGraph,g", value<int>()->default_value(0), "The number of graphs for each subject (0 means all)")
			("types,t", value<vector<int>>()->multitoken()->default_value(vector<int>(), "{}"),
				"Accepted subject types. Left empty for all types.")
			("directed,d", value<bool>()->default_value(false), "Whether the graph is directed (default undirected)")
			("selfpoint,p", value<bool>()->default_value(true),
				"Whether to allow a temporal motif with identical edges in consecutive snapshots")
			;
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);
	} catch(std::exception& excep) {
		cerr << "Error: " << excep.what() << "\n";
		cerr << desc << endl;
		return 1;
	}

	cout << "Load subjects..." << endl;
	vector<Subject> subs = loadSubject(vm["gPath"].as<string>(),
		vm["types"].as<vector<int>>(), vm["nSubject"].as<int>(),
		vm["nSkip"].as<int>(), vm["nGraph"].as<int>());
	cout << "  # subject loaded: " << subs.size() << endl;
	vector<TemporalEdgeGraph> tegs;
	tegs.reserve(subs.size());
	for(auto& sub : subs)
		tegs.emplace_back(sub, vm["selfpoint"].as<bool>());
	subs.clear();
	cout << "  Translated to temporal edge graphs." << endl;

	cout << "Input tempopral motifs (one per line).\n"
		"Format: v <id> <type>; ...; e <nidx-1> <nidx-2> <etype> ...;" << endl;
	string line;
	while(getline(cin, line)) {
		TemporalEdgeMotif m = parse2TEM(line);
		if(!m.check()) {
			cout << "not a valid (connected) subgraph." << endl;
			continue;
		}
		m.sortup();
		int c = 0;
		for(auto&g : tegs) {
			if(contains(g, m))
				++c;
		}
		cout << c << "\t" << double(c) / tegs.size() << endl;
	}

	return 0;
}
