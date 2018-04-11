#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Option.h"
#include "libcommon/Subject.h"
#include "libio/io.h"

using namespace std;

void dumpGraphIngSpanFormat(const size_t gid, const Graph& g, ostream& os){
	os << "t # " << gid <<"\n";
	size_t n = g.getnNode();
	for(size_t i = 0; i < n; ++i) {
		os << "v " << i << " " << i + 2 << "\n";
	}
	for(size_t i = 0; i < n; ++i) {
		auto& line = g.matrix[i];
		for(size_t j = i + 1; j < n; ++j){
			if(line[j])
				os << "e " << i << " " << j << " " << 2 << "\n";
		}
	}
}

int main(int argc, char* argv[]) {
	Option opt;
	if(!opt.parseInput(argc, argv)) {
		cerr << "Error in parsing options." << endl;
		return 1;
	}
	if(opt.show) {
		cout << "Input folder:  " << opt.iPath << "\n"
			<< "Output folder/file: " << opt.oPath << "\n"
			<< "Output into one file: " << opt.oneFile << "\n"
			<< "# of subjects: " << opt.nSubject << ", "
			<< "# of skipped: " << opt.nSkip << ", "
			<< "# of graphs: " << opt.nGraph
			<< endl;
	}

	cout << "Preparing output folder/file" << endl;
	try{
		if(opt.oneFile){
			prepareFile(opt.oPath);
		}else{
			prepareFolder(opt.oPath);
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

	cout << "Converting to gSpan format..." << endl;
	if(opt.oneFile){
		size_t gid = 0;
		ofstream fout(opt.oPath);
		for(auto& s : subs){
			for(auto& g : s.graphs)
				dumpGraphIngSpanFormat(gid++, g, fout);
		}
	}else{
		for(auto& s : subs){
			SubjectInfo si(s);
			size_t i=0;
			for(auto& g : s.graphs){
				si.seqNum=i++;
				ofstream fout(opt.oPath+si.genFilename());
				dumpGraphIngSpanFormat(0, g, fout);
			}
		}
	}

	return 0;
}
