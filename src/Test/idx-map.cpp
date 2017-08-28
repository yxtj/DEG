#include "libutil/IndexMapper.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_ud(){
    IndexMapper2DUndirected mp0(false), mp1(true);
    for(int i=0;i<100;++i){
        auto v0 = deseqUD(i, false), v1 = deseqUD(i, true);
        int r0 = seqUD(v0.first, v0.second, false), r1 = seqUD(v1.first, v1.second, true);
        assert(i==r0);
        assert(i==r1);
        auto p0=mp0.deseq(i), p1=mp1.deseq(i);
        int d0=mp0.seq(p0), d1=mp1.seq(p1);
        assert(i==d0);
        assert(i==d1);
    }
}

void test_d(int N){
    IndexMapper2DDirected mp0(false, N), mp1(true, N);
    int up = 100 < N*N ? 100 : N*N;
    for(int i=0;i<up;++i){
        auto v0= deseqD(N, i, false), v1 = deseqD(N, i, true);
        int r0 = seqD(N, v0.first, v0.second, false), r1 = seqD(N, v1.first, v1.second, true);
        assert(i==r0);
        assert(i==r1);
        auto p0=mp0.deseq(i), p1=mp1.deseq(i);
        int d0=mp0.seq(p0), d1=mp1.seq(p1);
        assert(i==d0);
        assert(i==d1);
    }
}

int main(){
    cout<<"testing undirected mapping."<<endl;
    test_ud();
    for(int n : {2,3,4,10,20}){
        cout<<"testing directed mapping with N="<<n<<"."<<endl;
        test_d(n);          
    }
    return 0;
}
