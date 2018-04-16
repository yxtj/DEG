#pragma once
#include <vector>
#include <string>
#include "libcommon/Subject.h"
#include "libcommon/Motif.h"

// Subjects

std::vector<std::pair<SubjectInfo, std::vector<std::string>>> getSubjectFilenames(
	const std::string& folder, const std::vector<int>& types, int nSub, int nSkip, int nGraph);

std::vector<Subject> loadSubject(const std::string& folder,
	 const std::vector<int>& types, int nSub, int nSkip, int nGraph);

std::vector<Subject> loadSubject(const std::string& folder,
	const std::vector<std::pair<SubjectInfo, std::vector<std::string>>>& subs);

// Motifs

Motif parseMotif(const std::string& line);

std::vector<Motif> loadMotif(const std::string& filename, int nMotif);

bool dumpMotifs(const std::vector<Motif>& ms, const std::string& fn);