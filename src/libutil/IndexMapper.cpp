#include "IndexMapper.h"
#include <cmath>

using namespace std;

// require j<=i
int seqUD(const int i, const int j, const bool selfloop){
    int res=j;
    if(selfloop){
        res += i*(i+1)/2;
    }else{
        res += i*(i-1)/2;
    }
    return res;
}
std::pair<int, int> deseqUD(const int v, const bool selfloop){
    int i, j;
    if(selfloop){
        // v = i*(i+1)/2 + j <= i*(i+1)/2 + i
        // i*i + 3i - 2v >= 0
        // because i>=0, i >= (-3+sqrt(9+8v))/2
        i = static_cast<int>(ceil((sqrt(9+8*v) - 3)/2));
        j = v - i*(i+1)/2;
    }else{
        // v = i*(i-1)/2 + j < i*(i-1)/2 + i
        // i*i + i - 2v > 0
        // because i>0, i > (-1+sqrt(1+8v))/2
        i = static_cast<int>(ceil((sqrt(1+8*v) - 1)/2));
        j = v - i*(i-1)/2;
    }
    return make_pair(i, j);
}

int seqD(const int N, const int i, const int j, const bool selfloop){
    int res;
    if(selfloop){
        res=i*N + j;
    }else{
        res=i*(N - 1) + j - (j>i ? 1 : 0);
    }
    return res;
}
std::pair<int, int> deseqD(const int N, const int v, const bool selfloop){
    int i,j;
    if(selfloop){
        i = v/N;
        j = v%N;
    }else{
        i = v/(N-1);
        j = v%(N-1);
        j += (j>=i ? 1 : 0);
    }
    return make_pair(i, j);
}

// member functions: 

int IndexMapper2DUndirected::seq(const int i, const int j){
    return seqUD(i,j,selfloop);
}

std::pair<int, int> IndexMapper2DUndirected::deseq(const int v){
    return deseqUD(v,selfloop);
}

int IndexMapper2DDirected::seq(const int i, const int j){
    return seqD(N,i,j,selfloop);
}

std::pair<int, int> IndexMapper2DDirected::deseq(const int v){
    return deseqD(N,v,selfloop);
}
