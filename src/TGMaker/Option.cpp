#include "Option.h"
#include <iostream>
#include "libutil/Util.h"
#include <boost/program_options.hpp>

using namespace std;

struct Option::implDesc {
	boost::program_options::options_description desc;
};

Option::Option()
	:pimpl(new implDesc{ boost::program_options::options_description("Options", getScreenSize().first) })
{
	// define
	using boost::program_options::value;
	pimpl->desc.add_options()
		("help,h", "Print help messages")
		("showInfo", value<bool>(&show)->default_value(true), "Print the initializing information")
		("gPath,i", value<string>(&gPath)->required(), "The folder for original graph (input).")
		("tgPath,o", value<string>(&tgPath)->required(), "The folder for temporal edge-based graphs (output).")
		("nSubject,n", value<int>(&nSubject)->default_value(0), 
			"# of subjects to load (non-positive means load all).")
		("nSkip,s",value<int>(&nSkip)->default_value(0),"Skip the first <s> subjects (used for restart from failure).")
		("nGraph,g",value<int>(&nGraph)->default_value(0), "The number of graphs for each subject (0 means all)")
		("types,t",value<vector<int>>(&types)->multitoken()->default_value(vector<int>(),"{}"),
			"Accepted subject types. Left empty for all types.")
		("selfpoint,p",value<bool>(&show)->default_value(true),
			"Whether to allow a temporal motif with identical edges in consecutive snapshots")
		;
}
Option::~Option(){
	delete pimpl;
}

bool Option::parseInput(int argc, char* argv[]) {
	//parse
	bool flag_help = false;
	boost::program_options::variables_map var_map;
	try {
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, pimpl->desc), var_map);
		boost::program_options::notify(var_map);

		if(var_map.count("help")) {
			flag_help = true;
		}
	} catch(std::exception& excep) {
		cerr << "Error: " << excep.what() << "\n";
		flag_help = true;
	} catch(...) {
		cerr << "Exception of unknown type!\n";
		flag_help = true;
	}
	while(!flag_help) { // technique for condition checking
		flag_help = true;
		if(nSkip<0){
			cerr<<"Error: nSkip should be 0 or positive"<< "\n";
			break;
		}

		sortUpPath(gPath);
		sortUpPath(tgPath);
		flag_help = false;
		break;
	}

	if(true == flag_help) {
		cerr << pimpl->desc << endl;
		return false;
	}
	return true;
}


std::string& Option::sortUpPath(std::string & path)
{
	if(!path.empty() && path.back() != '/')
		path.push_back('/');
	return path;
}
