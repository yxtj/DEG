#include "libutil/IndexMapper.h"
#include "libutil/Util.h"
#include "libcommon/Subject.h"
#include "libio/io.h"
#include <iostream>
#include <boost/program_options.hpp>

using namespace std;

int main(int argc, char* argv[]){
	boost::program_options::variables_map vm;
	boost::program_options::options_description desc("Options", getScreenSize().first);
	try {
		using boost::program_options::value;
		desc.add_options()
			("help,h", "Print help messages.\n"
				"Translate sequential index to pair or the opposite.\n"
				"One per line, \"x y\" will be translated to a sequential index \"s\", \"s\" will be translated to a pair \"x y\"")
			("selfpoint,p", value<bool>()->default_value(true),
				"Whether to allow a temporal motif with identical edges in consecutive snapshots")
			("directed,d", value<bool>()->default_value(false), "Whether the graph is directed (default undirected)")
			("nodes,n", value<int>()->default_value(0), "Number of nodes. Required if it is a directed graph")
			;
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);
		if(vm["directed"].as<bool>() && vm["nodes"].as<int>()<=0) {
			throw invalid_argument("A valid -n option is required for directed graphs.");
		}
	} catch(std::exception& excep) {
		cerr << "Error: " << excep.what() << "\n";
		cerr << desc << endl;
		return 1;
	}

	IndexMapper2D* mapper = nullptr;
	if(vm["directed"].as<bool>()) {
		mapper = new IndexMapper2DDirected(vm["selfpoint"].as<bool>(), vm["nodes"].as<int>());
	} else {
		mapper = new IndexMapper2DUndirected(vm["selfpoint"].as<bool>());
	}

	cout << "Please input sequential or paired (separated with a space) indexes, one per line." << endl;
	cout << "(Use EOF to quit. Usually EOF can be typed with Ctrl+D or Ctrl+Z.)" << endl;

	string skipchars = " \t\r\n";
	string sepchars = " ,\t";

	string line;
	while(getline(cin, line)) {
		size_t l = line.size();
		size_t f = 0;
		while(f < l && skipchars.find(line[f]) != string::npos)
			++f;
		while(f < l && skipchars.find(line[l-1]) != string::npos)
			--l;
		if(f >= l)
			continue;
		if(f != 0 && l != line.size())
			line = line.substr(f, l - f);
		size_t p = line.find_first_of(sepchars);
		if(p == string::npos) {
			// sequential index
			pair<int, int> res = mapper->deseq(stoi(line));
			cout << res.first << " " << res.second << endl;
		} else {
			// paired index
			pair<int, int> temp;
			temp.first = stoi(line.substr(0, p));
			p = line.find_last_of(sepchars);
			temp.second= stoi(line.substr(p));
			int res = mapper->seq(temp);
			cout << res << endl;
		}
	}

	delete mapper;
	return 0;
}
