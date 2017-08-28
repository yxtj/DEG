#pragma once
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include "libcommon/Subject.h"
#include "libteg/TemporalEdgeGraph.h"

std::vector<Subject> loadSubject(const std::string& folder,
	 const std::vector<int>& types, int nSub, int nSkip, int nGraph);

bool outputTemporalEdgeGraph(std::ostream& os, const TemporalEdgeGraph& g);

bool outputTEGs(const std::string& folder, const std::vector<std::pair<SubjectInfo, TemporalEdgeGraph>>& vec);
