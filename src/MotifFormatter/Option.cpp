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
		("help,h", "Translate the found motifs of other programs (format) into my motif format. Print help messages.")
		("showInfo", value<bool>(&show)->default_value(true), "Print the initializing information")
		("format,f", value<string>(&format_str)->required(), "The destination format. Support: gSpan, apriori")
		("iFilePath,i", value<string>(&iFile), "The file path for the motifs (input-type-1).")
		("iFolderPath,I", value<string>(&iFolder), "The folder path for the motifs (input-type-2).")
		("iNamePattern,p", value<string>(&iPattern)->default_value("*.txt"), "The name pattern of the input files (input-type-2)")
		("oFile,o", value<string>(&oPath)->required(), "The translated motif file (output).")
		("check,c", value<bool>(&checkValid)->default_value(true), "Whether to remove the invalid (unconnected) results")
		("nRes,n", value<int>(&nRes)->default_value(0), "# of number of valid output (non-positive means all).")
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
	} catch(std::exception& e) {
		cerr << "Error: " << e.what() << "\n";
		flag_help = true;
	} catch(...) {
		cerr << "Exception of unknown type!\n";
		flag_help = true;
	}
	while(!flag_help) { // technique for condition checking
		flag_help = true;

		sortUpInputPath();
		setFormat();
		if(format == Format::NONE){
			cerr<<"Error: format is not supported."<<endl;
			break;
		}
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

bool Option::sortUpInputPath(){
	if(iFile.empty() && (iFolder.empty() || iPattern.empty())){
		cerr<<"Error: no valid input is given."<<endl;
		return false;
	}
	if(!iFile.empty() && !(iFolder.empty() || iPattern.empty())){
		cerr<<"Error: only one input type should be given."<<endl;
		return false;
	}
	if(!iFile.empty()){
		isFileInput = true;
	}else{
		isFileInput = false;
	}
	return true;
}

void Option::setFormat(){
	for(auto& ch : format_str){
		if(ch >= 'A' && ch <='Z')
			ch += 'a'-'A';
	}
	if(format_str == "gspan"){
		format = Format::GSPAN;
	}else if(format_str == "apriori"){
		format = Format::APRIORI;
	}else{
		format = Format::NONE;
	}
}
