#pragma once
#include <utility>
#include <functional>

struct Edge {
	int s, d;
	Edge() = default;
	Edge(const int a, const int b) :s(a), d(b) {
		//undirected edge : s<=d
		if(s > d) std::swap(s, d);
	}
	void set(const int a, const int b) {
		s = a <= b ? a : b;
		d = a <= b ? b : a;
	}
};

inline bool operator==(const Edge &lth, const Edge &rth) {
	//also consider the reverse direction
	return (lth.s == rth.s && lth.d == rth.d);
	//		|| (lth.s == rth.d && lth.d == rth.s);
}
inline bool operator!=(const Edge &lth, const Edge &rth) {
	return lth.s != rth.s || lth.d != rth.d;
}
inline bool operator<(const Edge &lth, const Edge &rth) {
	return lth.s < rth.s || lth.s == rth.s && lth.d < rth.d;
}

namespace std {
	template <>
	struct hash<Edge> {
		typedef Edge argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& e) const {
			return hash<int>()(e.s) * 137 + hash<int>()(e.d);
		}
	};
}
