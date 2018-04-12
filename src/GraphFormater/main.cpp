#include "Option.h"
#include "dump.h"
#include "libcommon/Subject.h"
#include "libio/io.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	Option opt;
	if(!opt.parseInput(argc, argv)) {
		cerr << "Error in parsing options." << endl;
		return 1;
	}
	if(opt.show) {
		cout << "Input information:\n"
		 	<< "\tFolder:  " << opt.iPath << "\n"
			<< "\t# of subjects: " << opt.nSubject << "\n"
			<< "\t# of skipped: " << opt.nSkip << "\n"
			<< "\t# of graphs: " << opt.nGraph << "\n"
			<< "Output information:\n"
			<< "\tFormat: " << opt.format_str << "\n"
			<< "\tFolder/File: " << opt.oPath << "\n"
			<< "\tSeparated output: " << opt.separated << "\n"
			<< endl;
	}

	cout << "Preparing output folder/file" << endl;
	try{
		if(opt.separated){
			prepareFolder(opt.oPath);
		}else{
			prepareFile(opt.oPath);
		}
	}catch(exception& e){
		cerr<<"Error in preparing output folder/file:\n"<<e.what()<<endl;
		return 2;
	}

	cout << "Loading original graphs..." << endl;
	vector<Subject> subs;
	try{
		subs = loadSubject(opt.iPath, opt.types, opt.nSubject, opt.nSkip, opt.nGraph);
	}catch(exception& e){
		cerr<<"Error: "<<e.what()<<endl;
		return 3;
	}
	cout << "# of loaded subjects: " << subs.size() << endl;

	cout << "Converting to " << opt.format_str << " format..." << endl;
	if(opt.format == Option::Format::GSPAN){
		dump_gSpan(subs, opt.oPath, opt.separated);
	}else if(opt.format == Option::Format::APRIORI){
		dump_apriori(subs, opt.oPath, opt.separated);
	}

	return 0;
}
