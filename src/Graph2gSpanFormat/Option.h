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

	std::string iPath; // the input graph folder
	std::string oPath; // the gSpan format graph output folder or file (depend on oneFile)
	bool oneFile; // output all the output graphs into one file


	int nSubject; // number of subjects need to be loaded from the dataset
	int nSkip; // skip some of the first subject, to efficiently restart after failure
	int nGraph; // number of graphs for each subject
	std::vector<int> types; // accepted subject types

	//int comGraphLevel; // the compression level for graph outputing

public:
	Option();
	~Option();

	bool parseInput(int argc, char *argv[]);
private:
	std::string& sortUpPath(std::string& path);
	void sortUpOutputPath();
};

