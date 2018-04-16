#pragma once
#include <vector>
#include <string>

void prepareFolder(const std::string& folder);
void prepareFile(const std::string& fpath);

bool canWriteToFile(const std::string& fpath);

std::vector<std::string> listFile(
    const std::string& folder, const std::string& prefix = "");

std::vector<std::string> listFilePattern(
    const std::string& folder, const std::string& pattern);
