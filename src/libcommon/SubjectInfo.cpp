#include "stdafx.h"
#include "SubjectInfo.h"
#include <iterator>

using namespace std;

SubjectInfo::SubjectInfo(const std::string & filename)
{
	if(!parseFromFilename(filename))
		throw invalid_argument("given filename: \"" + filename + "\" cannot be parsed.");
}

SubjectInfo::SubjectInfo(const std::string & id, const int type, const int seqNum)
	:id(id), type(type), seqNum(seqNum)
{
}

SubjectInfo::SubjectInfo(std::string && id, const int type, const int seqNum)
	:id(move(id)), type(type), seqNum(seqNum)
{
}

std::string SubjectInfo::genFilename() const
{
	return to_string(type) + "-" + id + "-" + to_string(seqNum) + ".txt";
}

// filename format: <type>-<subject Id>-<scan Id>.txt
static regex subFnPattern("^(\\d+)-([^-]+)-(\\d+)\\.txt$");

bool SubjectInfo::parseFromFilename(const std::string & fn)
{
	// regex-based method:
	smatch res;
	if(regex_match(fn, res, subFnPattern)) {
		type = stoi(res[1].str());
		id = res[2].str();
		seqNum = stoi(res[3].str());
		return true;
	}
	return false;
	// string-based method:
	if(fn.empty())
		return false;
	size_t p1 = fn.find('-');
	size_t p2 = fn.find('-', p1 + 1);
	size_t pend = fn.rfind(".txt", string::npos, 4);
	if(p1 == string::npos || p2 == string::npos || pend == string::npos)
		return false;
	try {
		id = fn.substr(p1 + 1, p2 - p1 - 1);
		type = stoi(fn.substr(0, p1));
		seqNum = stoi(fn.substr(p2 + 1, pend - p2 - 1));
	} catch(...) {
		return false;
	}
	return true;
}

bool SubjectInfo::checkFilename(const std::string & fn)
{
	return regex_match(fn, subFnPattern);
}

std::vector<std::pair<SubjectInfo, std::vector<std::string>>> SubjectInfo::groupBySubjectID(
	const std::vector<std::string>& fns)
{
	vector<pair<SubjectInfo, string>> data; // <sub, filename>
	for(auto& fn : fns) {
		SubjectInfo sub;
		if(!sub.parseFromFilename(fn))
			continue;
		data.emplace_back(move(sub), fn);
	}
	sort(data.begin(), data.end(), [](const pair<SubjectInfo, string>& l, const pair<SubjectInfo, string>& r) {
		if(l.first.id != r.first.id)
			return l.first.id < r.first.id;
		return l.first.seqNum < r.first.seqNum;
	});
	std::vector<std::pair<SubjectInfo, std::vector<std::string>>> res;
	string prev;
	for(auto& p : data) {
		if(p.first.id == prev) {
			res.back().second.push_back(move(p.second));
		} else {
			prev = p.first.id;
			res.emplace_back(move(p.first), vector<string>{ p.second });
			res.back().first.seqNum = 0;
		}
	}
	return res;
}
