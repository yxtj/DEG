#pragma once
#include "libcommon/SubjectInfo.h"
#include "libcommon/Graph.h"
#include <vector>

struct Subject : public SubjectInfo
{
	std::vector<Graph> graphs;

	Subject(const SubjectInfo &oth) : SubjectInfo(oth) {}

	size_t getnNode() const{
		return graphs.front().getnNode();
	}
	size_t getnSnapshot() const{
		return graphs.size();
	}
};
