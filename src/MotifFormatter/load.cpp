#include "load.h"
#include <iostream>
#include <fstream>

using namespace std;

// -------- gSpan --------

std::vector<Motif> load_gSpan_result(const std::string& ifn, const bool check, const int n)
{
	std::vector<Motif> res;

	return res;
}

std::vector<Motif> load_gSpan_result(std::function<std::string()> ifFun, const bool check, const int n)
{
	std::vector<Motif> res;
	for(string fn = ifFun(); !fn.empty(); fn = ifFun()){
		std::vector<Motif>&& tmp = load_apriori_result(fn, check, n);
		for(auto& t : tmp)
			res.push_back(move(t));
	}
	return res;
}

// -------- apriori --------

std::vector<Motif> load_apriori_result(const std::string& ifn, const bool check, const int n)
{
	std::vector<Motif> res;
	
	return res;
}

std::vector<Motif> load_apriori_result(std::function<std::string()> ifFun, const bool check, const int n)
{
	std::vector<Motif> res;
	for(string fn = ifFun(); !fn.empty(); fn = ifFun()){
		std::vector<Motif>&& tmp = load_apriori_result(fn, check, n);
		for(auto& t : tmp)
			res.push_back(move(t));
	}
	return res;
}

