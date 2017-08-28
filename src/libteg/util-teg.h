#pragma once
#include "libcommon/Graph.h"
//#include "libcommon/Subject.h"
#include "TemporalEdgeGraph.h"
#include "TemporalEdgeMotif.h"
#include <vector>

std::vector<int> getEdgeSequence(const Graph& g, const bool selfpoint);

//TemporalEdgeGraph transSubject2TEG(Subject& sub, const bool selfpoint = true);

bool contains(const TemporalEdgeGraph& g, const TemporalEdgeMotif& m);
