#pragma once
#include "Edge.h"
#include <vector>
#include <ostream>

class Motif
{
public:
	std::vector<Edge> edges;
public:
	Motif() = default;
	Motif(const std::vector<Edge>& edges);

	// return whether new edge is added by this call
	bool addEdge(const int s, const int d);
	bool addEdgeCheck(const int s, const int d);
	// return whether the edge is deleted by this call
	bool removeEdge(const int s, const int d);

	// make the edges in increasing order
	void sortUpEdges();
	// make edges inorder and additionally remove reduandent edges
	void sortUpEdges(const bool unique);

	bool containNode(const int n) const;
	bool containEdge(const int s, const int d) const;
	const Edge& lastEdge() const;

	bool connected() const;

	int getnNode() const;
	int getnEdge() const;
	size_t size() const; // same as getnEdge()
	bool empty() const;
};

bool operator==(const Motif& lth, const Motif& rth);
bool operator<(const Motif& lth, const Motif& rth);

std::ostream& operator<<(std::ostream& os, const Motif& m);

namespace std {
	template <>
	struct hash<Motif> {
		typedef Motif argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& m) const {
			hash<Edge> fun;
			size_t res = 0;
			int cnt = 0;
			for(auto it = m.edges.begin(); cnt <= 3 && it != m.edges.end(); ++it, ++cnt) {
				res = res * 23 + fun(*it);
			}
			return res;
		}
	};
}

