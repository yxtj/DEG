#pragma once
#include <vector>
#include <string>
#include "libcommon/Subject.h"

void prepareFolder(const std::string& folder);
void prepareFile(const std::string& fpath);

bool canWriteToFile(const std::string& fpath);

std::vector<std::pair<SubjectInfo, std::vector<std::string>>> getSubjectFilenames(
	const std::string& folder, const std::vector<int>& types, int nSub, int nSkip, int nGraph);

std::vector<Subject> loadSubject(const std::string& folder,
	 const std::vector<int>& types, int nSub, int nSkip, int nGraph);

std::vector<Subject> loadSubject(const std::string& folder,
	const std::vector<std::pair<SubjectInfo, std::vector<std::string>>>& subs);
