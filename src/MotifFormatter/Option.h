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
	
	std::string format_str; // the format string
	enum class Format{
		NONE,
		GSPAN,
		APRIORI
	};
	Format format; // will be set automatically

	std::string iFolder; // the input motif folder (i-1)
	std::string iPattern; // the name pattern of the input files (i-1)
	std::string iFile; // the input motif file (i-2)
	bool isFileInput; // helper variable for type of input (i-1 or i-2)

	std::string oPath; // the gSpan format graph output folder or file (depend on separated)

	bool checkValid; // remove the invalid (unconnected) results

	int nRes; // the number of valid output

public:
	Option();
	~Option();

	bool parseInput(int argc, char *argv[]);
private:
	std::string& sortUpPath(std::string& path);
	bool sortUpInputPath();
	void setFormat();
};

