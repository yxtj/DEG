#include "fs.h"
#include <boost/filesystem.hpp>
#include <regex>

using namespace std;
using namespace boost::filesystem;

void prepareFolder(const std::string& folder){
	path root(folder);
	if(exists(root))
		return;
	create_directories(root);
}

void prepareFile(const std::string& fpath){
	path fp(fpath);
	if(exists(fp))
		return;
	create_directories(fp.parent_path());
}

bool canWriteToFile(const std::string& fpath){
	path fp(fpath);
	if(exists(fp))
		return true;
	return exists(fp.parent_path());
}

std::vector<std::string> listFile(const std::string& folder, const std::string& prefix){
    std::vector<std::string> res;
	path p(folder);
	if(!exists(p) || !is_directory(p))
		return res;
	directory_iterator end;
	for(auto it = directory_iterator(p); it != end; ++it){
		if(!is_regular_file(*it))
			continue;
		string fn = it->path().filename().string();
		if(prefix.empty() || prefix == fn.substr(0, prefix.size()))
			res.push_back(move(fn));
	}
	return res;
}

std::vector<std::string> listFilePattern(const std::string& folder, const std::string& pattern){
    std::vector<std::string> res;
	path p(folder);
	if(!exists(p) || !is_directory(p))
		return res;
    regex reg(pattern);
	directory_iterator end;
	for(auto it = directory_iterator(p); it != end; ++it){
		if(!is_regular_file(*it))
			continue;
		string fn = it->path().filename().string();
        if(regex_match(fn, reg))
			res.push_back(move(fn));
	}
	return res;
}
