#pragma once
#include <string>
#include <vector>

class Option
{
	struct implDesc;
	implDesc* pimpl;
//	std::vector<std::function<bool()>> paramParser;
public:
	bool show; // print the initializing information

	std::string gPath; // the input folder
	std::string tgPath; // the output folder
	int nSubject; // number of subjects need to be loaded from the dataset
	int nSkip; // skip some of the first subject, to efficiently restart after failure
	int nGraph; // number of graphs for each subject
	std::vector<int> types; // accepted subject types

	bool selfpoint; // whether to allow edges point to them self in the next snapshot
	//int comGraphLevel; // the compression level for graph outputing

public:
	Option();
	~Option();

	bool parseInput(int argc, char *argv[]);
private:
	std::string& sortUpPath(std::string& path);
};

