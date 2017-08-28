#pragma once
#include <utility>

// require j<=i
int seqUD(const int i, const int j, const bool selfloop = false);
std::pair<int, int> deseqUD(const int v, const bool selfloop = false);

int seqD(const int N, const int i, const int j, const bool selfloop = false);
std::pair<int, int> deseqD(const int N, const int v, const bool selfloop = false);


class IndexMapper2D
{
protected:
    bool selfloop;
public:
    IndexMapper2D() = default;
    IndexMapper2D(const bool selfloop) : selfloop(selfloop) {}

    void setLoop(const bool loop){
        selfloop = loop;
    }
    bool getLoop() const{
        return selfloop;
    }
    virtual int seq(const int i, const int j) = 0;
    virtual int seq(const std::pair<int, int>& p) = 0;
    virtual std::pair<int, int> deseq(const int v) = 0;
};

class IndexMapper2DUndirected : public IndexMapper2D
{
public:
    IndexMapper2DUndirected() = default;
    IndexMapper2DUndirected(const bool selfloop): IndexMapper2D(selfloop) {}

    // j<=i
    virtual int seq(const int i, const int j);
    virtual int seq(const std::pair<int, int>& p){
        return seq(p.first, p.second);
    }
    virtual std::pair<int, int> deseq(const int v);
};

class IndexMapper2DDirected : public IndexMapper2D
{
    int N;
public:
    IndexMapper2DDirected() = default;
    IndexMapper2DDirected(const bool selfloop, const int n): IndexMapper2D(selfloop), N(n) {}

    void setN(const int n){
        N = n;
    }
    int getN() const{
        return N;
    }
    virtual int seq(const int i, const int j);
    virtual int seq(const std::pair<int, int>& p){
        return seq(p.first, p.second);
    }
    virtual std::pair<int, int> deseq(const int v);
};
