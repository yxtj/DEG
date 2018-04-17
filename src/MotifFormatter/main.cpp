#include "Option.h"
#include "load.h"
#include "libcommon/Motif.h"
#include "libio/fs.h"
#include "libio/io.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	Option opt;
	if(!opt.parseInput(argc, argv)) {
		cerr << "Error in parsing options." << endl;
		return 1;
	}
	if(opt.show) {
		cout << "Input information:\n"
			<< "\tFormat: " << opt.format_str << "\n"
			<< "\tType: " << (opt.isFileInput ? "file" : "folder") << "\n"
			<< "\tFile: "<< opt.iFile << "\n"
		 	<< "\tFolder:  " << opt.iFolder << "\tName-Pattern: " << opt.iPattern << "\n";
		cout << "Output information:\n"
			<< "\tFolder/File: " << opt.oPath << "\n"
			<< "\tCheck: " << opt.checkValid << "\n"
			<< "\t# of Result: " << opt.nRes
			<< endl;
	}

	cout << "Preparing output folder/file" << endl;
	try{
		prepareFile(opt.oPath);
	}catch(exception& e){
		cerr<<"Error in preparing output file:\n"<<e.what()<<endl;
		return 2;
	}

	cout << "Loading original motifs..." << endl;
	vector<Motif> ms;
	try{
		vector<string> fns;
		if(opt.isFileInput){
			fns.push_back(opt.iFile);
		}else{
			vector<string> fns = listFilePattern(opt.iFile, opt.iPattern);
		}
		function<string()> fun = [&]()->string{
			static auto it = fns.begin();
			if(it!=fns.end()){
				return *it++;
			}else
				return string("");
		};
		if(opt.format == Option::Format::GSPAN)
			ms = load_gSpan_result(fun, opt.checkValid, opt.nRes);
		else if (opt.format == Option::Format::APRIORI)
			ms = load_apriori_result(fun, opt.checkValid, opt.nRes);
	}catch(exception& e){
		cerr<<"Error: "<<e.what()<<endl;
		return 3;
	}
	cout << "# of loaded motifs: " << ms.size() << endl;

	cout << "Dump with our motif format..." << endl;
	dumpMotifs(ms, opt.oPath);

	return 0;
}
