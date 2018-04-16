#pragma once
#include "libcommon/Motif.h"
#include <string>
#include <vector>
#include <functional>

std::vector<Motif> load_gSpan_result(const std::string& ifn, const bool check, const size_t n);
std::vector<Motif> load_apriori_result(const std::string& ifn, const bool check, const size_t n);

// Use a stateful function to generate input file names. It terminates when ifFun returns an empty string.
std::vector<Motif> load_gSpan_result(std::function<std::string()> ifFun, const bool check, const size_t n);
std::vector<Motif> load_apriori_result(std::function<std::string()> ifFun, const bool check, const size_t n);
