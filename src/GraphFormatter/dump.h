#pragma once
#include "libcommon/Subject.h"
#include <string>
#include <vector>

void dump_gSpan(const std::vector<Subject>& subs, const std::string& oPath, const bool separated);
void dump_apriori(const std::vector<Subject>& subs, const std::string& oPath, const bool separated);
