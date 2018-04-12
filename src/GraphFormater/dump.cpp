#include "dump.h"
#include <iostream>
#include <fstream>

using namespace std;

// -------- gSpan --------

void dumpGraph_gSpan(const size_t gid, const Graph& g, ostream& os){
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

void dump_gSpan(const vector<Subject>& subs, const string& oPath, const bool separated){
	if(!separated){
		size_t gid = 0;
		ofstream fout(oPath);
		for(auto& s : subs){
			for(auto& g : s.graphs)
				dumpGraph_gSpan(gid++, g, fout);
		}
	}else{
		for(auto& s : subs){
			SubjectInfo si(s);
			size_t i=0;
			for(auto& g : s.graphs){
				si.seqNum=i++;
				ofstream fout(oPath+si.genFilename());
				dumpGraph_gSpan(0, g, fout);
			}
		}
	}
}

// -------- apriori --------

void dumpGraph_apriori(const Graph& g, ostream& os){
	size_t n = g.getnNode();
	for(size_t i = 0; i < n; ++i) {
		auto& line = g.matrix[i];
		for(size_t j = i + 1; j < n; ++j){
			if(line[j])
				os << i << "-" << j << " ";
		}
	}
    os << "\n";
}

void dump_apriori(const std::vector<Subject>& subs, const std::string& oPath, const bool separated){
    if(!separated){
        ofstream fout(oPath);
		for(auto& s : subs){
			for(auto& g : s.graphs)
				dumpGraph_apriori(g, fout);
		}
    }else{
        for(auto& s : subs){
			SubjectInfo si(s);
			size_t i=0;
			for(auto& g : s.graphs){
				si.seqNum=i++;
				ofstream fout(oPath+si.genFilename());
				dumpGraph_apriori(g, fout);
			}
		}
    }
}
