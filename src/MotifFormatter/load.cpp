#include "load.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// -------- gSpan --------

std::vector<Motif> load_gSpan_result(const std::string& ifn, const bool check, const size_t n)
{
	std::vector<Motif> res;
	ifstream fin(ifn);
	string line;
	while(res.size()<n && getline(fin, line)){
		if(line.empty() || line[0] != 't')
			throw runtime_error("Error: the input file format is not correct");
		getline(fin, line);
		if(line.empty() || line[0] != 'p')
			throw runtime_error("Error: the input file format is not correct");
		Motif m;
		vector<int> nodes;
		getline(fin, line);
		while(!line.empty() && line[0] == 'v'){
			nodes.push_back(stoi(line.substr(line.rfind(' '))));
			getline(fin, line);
		}
		while(!line.empty() && line[0] == 'e'){
			size_t p1 = line.find(' ', 2);
			int s = stoi(line.substr(2, p1-2));
			size_t p2 = line.find(' ', p1+2);
			int d = stoi(line.substr(p1+1, p2-p1-1));
			m.addEdge(s, d);
			getline(fin, line);
		}
		if(m.connected())
			res.push_back(move(m));
	}
	return res;
}

std::vector<Motif> load_gSpan_result(std::function<std::string()> ifFun, const bool check, const size_t n)
{
	std::vector<Motif> res;
	for(string fn = ifFun(); !fn.empty(); fn = ifFun()){
		std::vector<Motif>&& tmp = load_apriori_result(fn, check, n - res.size());
		for(auto& t : tmp)
			res.push_back(move(t));
	}
	return res;
}

// -------- apriori --------

std::vector<Motif> load_apriori_result(const std::string& ifn, const bool check, const size_t n)
{
	std::vector<Motif> res;
	ifstream fin(ifn);
	string line;
	while(res.size()<n && getline(fin, line)){
		if(line.empty())
			continue;
		Motif m;
		size_t pend = line.rfind('(') - 1;
		size_t pf = 0;
		size_t pl = line.find(' ', pf+1);
		while(pl < pend){
			size_t pm = line.find('-', pf+1);
			int s = stoi(line.substr(pf, pm-pf));
			int d = stoi(line.substr(pm, pl-pm));
			m.addEdge(s, d);
		}
		if(m.connected())
			res.push_back(move(m));
	}
	return res;
}

std::vector<Motif> load_apriori_result(std::function<std::string()> ifFun, const bool check, const size_t n)
{
	std::vector<Motif> res;
	for(string fn = ifFun(); !fn.empty(); fn = ifFun()){
		std::vector<Motif>&& tmp = load_apriori_result(fn, check, n - res.size());
		for(auto& t : tmp)
			res.push_back(move(t));
	}
	return res;
}

