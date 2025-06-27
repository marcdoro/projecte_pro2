#include "enemy.hh"
#include "utils.hh"
using namespace std;

// --- SPRITES ---
const int _ = -1;
const int a = 0xeaf9fc;
const int b = 0x000000;
const int c = 0x20c0d8;
const int d = 0x01707a;
const int e = 0xd38f6e;
const int f = 0xfadab7;
const int g = 0x8c4c43;
const int h = 0xa5b5b6;
const int i = 0xef6029;
const int j = 0x9c2b0c;
const int k = 0x12235b;
const int l = 0x2e4aa4;
const int m = 0x3159eb;
const int n = 0x581a08;
const int o = 0xed1c24;
const int p = 0xffc83e;
const int q = 0xb97231;
const int r = 0xf7dab3;

const int A = 0xfefefe;
const int B = 0x000000;
const int C = 0xce8c60;
const int D = 0xffc49b;
const int E = 0x9f4f37;
const int F = 0x455b70;
const int G = 0x2c2c2c;
const int H = 0xfe551d;
const int I = 0xa72b01;
const int J = 0x193466;
const int K = 0x385c8d;
const int L = 0x251d54;
const int M = 0x6b1414;
const int N = 0xd0252b;
const int O = 0xcf9818;

// clang-format off
const vector<vector<vector<int>>> Enemy::sprites_ = {
        {
        {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,_,_,_,b,b,b,b,b,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,_,b,b,b,b,b,b,b,b,b,_},
        {_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
        {_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_,_},
        {_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_,_,_,_},
        {_,_,_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_},
        {_,b,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_,_},
        {_,_,b,b,b,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_},
        {_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
        {_,_,_,_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_,_,_},
        {b,b,b,b,b,b,b,b,b,b,b,C,b,b,b,C,b,b,b,b,b,b,b,_,_,_,_},
        {_,_,b,b,b,b,b,b,b,b,b,C,C,b,b,D,D,b,b,C,b,b,b,b,_,_,_},
        {_,_,_,_,b,b,b,b,C,b,b,b,b,b,b,C,D,D,b,C,b,b,b,b,_,_,_},
        {_,_,b,b,b,b,b,b,C,E,b,E,A,A,b,b,D,D,D,b,b,_,_,_,b,_,_},
        {_,_,_,_,_,b,b,b,C,C,E,C,A,A,F,G,D,D,C,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,b,b,E,C,C,D,D,D,D,D,E,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,b,E,C,D,D,D,D,D,b,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,b,C,E,C,D,D,D,b,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,b,b,b,b,C,C,E,E,b,b,b,b,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,b,b,H,H,I,H,C,C,C,E,E,C,H,I,b,b,_,_,_,_,_,_},
        {_,_,_,_,b,J,J,K,H,H,I,H,C,C,C,E,C,K,H,I,J,b,_,_,_,_,_},
        {_,_,_,_,b,K,K,J,K,H,H,I,I,K,K,K,K,J,H,I,J,b,_,_,_,_,_},
        {_,_,_,_,b,D,D,K,J,H,H,H,H,H,K,J,J,K,H,I,J,b,_,_,_,_,_},
        {_,_,_,b,E,C,D,C,b,H,H,I,H,H,H,K,K,H,H,b,b,_,_,_,_,_,_},
        {_,_,_,b,D,D,C,b,b,I,H,I,I,I,H,H,H,H,I,b,b,_,_,_,_,_,_},
        {_,_,_,b,D,D,b,_,_,b,b,K,I,I,H,H,H,I,b,C,b,_,_,_,_,_,_},
        {_,_,b,D,C,D,b,_,_,_,_,b,L,L,K,K,K,L,b,C,C,b,_,_,_,_,_},
        {_,_,b,D,C,b,_,_,_,_,_,b,H,K,L,L,L,K,I,b,L,b,_,_,_,_,_},
        {_,_,b,K,K,b,_,_,_,_,b,H,I,I,H,I,I,H,H,b,L,L,b,_,_,_,_},
        {_,_,b,K,K,b,b,_,_,_,b,H,I,H,H,I,I,H,H,b,E,C,b,_,_,_,_},
        {_,_,b,D,D,D,C,b,_,b,H,H,H,H,H,I,I,H,H,I,b,b,C,b,_,_,_},
        {_,_,b,D,D,D,E,D,b,b,H,H,H,H,H,b,b,I,H,H,b,b,C,b,_,_,_},
        {_,_,b,D,C,D,E,b,b,H,H,H,H,H,I,b,I,I,H,H,b,C,C,b,_,_,_},
        {_,_,_,b,b,D,D,b,b,H,H,H,H,H,I,b,M,I,I,H,H,b,b,_,_,_,_},
        {_,_,_,_,_,b,b,b,I,H,H,H,H,I,b,H,M,I,I,H,H,b,_,_,_,_,_},
        {_,_,_,_,_,_,_,b,H,H,H,H,H,b,b,H,I,M,I,I,H,b,_,_,_,_,_},
        {_,_,_,_,_,_,b,I,H,H,I,I,I,b,_,b,H,I,I,I,H,b,_,_,_,_,_},
        {_,_,_,_,_,_,b,H,H,I,I,I,b,_,_,b,I,H,H,H,I,b,_,_,_,_,_},
        {_,_,_,_,_,_,b,H,H,I,I,M,b,_,_,b,b,I,H,H,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,F,H,H,H,b,_,_,_,_,b,J,N,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,N,F,b,b,_,_,_,_,_,b,J,N,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,b,F,N,F,b,_,_,_,_,_,_,b,O,O,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,b,O,O,b,_,_,_,_,_,_,_,b,J,J,N,b,b,_,_,_,_,_},
        {_,_,_,_,_,b,N,F,b,_,_,_,_,_,_,_,b,J,J,J,N,J,b,_,_,_,_},
        {_,_,_,_,b,F,N,F,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    },
    {
        {_,_,_,_,_,_,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,_,_,_,_,_,b,_,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,r,b,_,_,_,_,b,b,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,r,r,b,b,_,_,b,p,b,_,_,_,b,_,_,_,_,_,_},
        {_,_,_,_,_,b,q,r,r,p,r,b,b,b,p,p,b,_,_,b,_,_,_,_,_,_},
        {_,_,_,_,_,b,p,r,r,p,p,r,p,q,q,p,p,b,b,p,b,_,_,_,_,_},
        {_,_,b,_,_,b,p,r,r,p,r,p,r,r,q,q,p,p,q,p,b,_,_,_,_,_},
        {_,_,b,b,_,b,p,r,r,p,r,r,p,r,r,p,p,p,q,p,p,b,_,_,_,_},
        {_,_,b,r,b,b,p,r,r,p,r,r,r,p,r,r,p,p,q,q,q,b,b,b,b,_},
        {_,_,b,r,r,p,q,p,p,p,p,r,r,p,r,r,p,q,p,r,r,r,r,b,_,_},
        {_,_,b,p,r,r,p,q,q,p,p,r,r,r,p,r,p,q,r,r,r,r,b,_,_,_},
        {_,_,_,b,r,r,r,p,p,q,q,p,r,r,p,r,p,r,r,r,p,b,b,_,_,_},
        {_,_,_,b,p,r,r,r,r,r,q,p,r,p,p,p,p,q,q,q,q,p,p,b,_,_},
        {_,_,_,_,b,q,p,r,r,p,p,p,q,r,r,p,q,r,r,p,q,p,p,p,b,_},
        {b,b,b,b,b,q,q,p,q,r,r,q,p,r,r,r,q,r,r,r,p,b,b,b,b,_},
        {_,b,p,p,p,p,q,q,r,r,r,q,r,r,r,p,e,p,r,r,r,b,_,_,_,b},
        {_,_,b,p,p,p,p,q,r,p,p,q,r,r,p,e,f,f,b,r,r,p,b,_,_,_},
        {_,_,_,b,q,q,p,b,r,p,e,q,q,r,p,f,f,f,f,b,r,r,b,_,_,_},
        {_,_,_,_,b,q,b,e,b,r,e,g,h,q,r,f,f,f,e,b,b,r,b,_,_,_},
        {_,_,b,b,p,p,b,e,e,b,e,g,r,r,q,e,f,f,b,_,_,b,b,_,_,_},
        {_,_,_,_,b,b,b,e,e,g,e,e,r,r,p,r,f,f,b,_,_,_,b,_,_,_},
        {_,_,_,_,_,_,_,b,b,g,e,e,e,f,f,f,f,e,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,b,g,e,e,f,f,f,f,b,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,e,g,f,f,f,e,b,b,_,_,_,_,_,_,_,_},
        {_,_,_,_,b,b,i,j,i,e,e,e,g,g,b,b,j,j,b,b,_,_,_,_,_,_},
        {_,_,_,b,k,k,l,i,j,i,f,f,f,e,g,f,e,i,j,k,b,_,_,_,_,_},
        {_,_,_,b,l,l,k,l,i,j,j,f,f,f,e,g,f,l,i,k,b,_,_,_,_,_},
        {_,_,b,f,g,f,l,k,i,i,i,i,l,l,l,l,l,l,i,k,b,_,_,_,_,_},
        {_,_,b,g,f,f,e,b,i,i,j,i,i,l,k,k,k,k,r,b,_,_,_,_,_,_},
        {_,_,b,e,f,f,b,b,j,i,i,j,i,i,l,k,k,k,h,b,_,_,_,_,_,_},
        {_,_,b,f,e,b,_,_,b,i,i,j,j,i,i,l,l,i,b,e,b,_,_,_,_,_},
        {_,b,f,f,b,_,_,_,_,b,b,m,m,j,i,i,i,j,b,e,b,_,_,_,_,_},
        {_,b,f,e,b,_,_,_,_,_,b,k,k,k,k,k,k,b,e,k,k,b,_,_,_,_},
        {_,b,m,m,b,_,_,_,_,b,i,j,j,m,m,m,m,b,b,k,k,b,_,_,_,_},
        {b,k,m,m,b,_,_,_,_,b,i,j,i,i,i,n,j,i,b,e,e,e,b,_,_,_},
        {b,f,f,f,f,b,_,_,b,i,j,i,i,i,i,n,n,i,j,b,g,e,b,_,_,_},
        {b,f,f,f,e,f,b,b,b,i,i,i,i,i,j,n,n,i,i,b,g,e,b,_,_,_},
        {b,f,e,f,e,b,b,b,i,i,i,i,i,i,b,n,i,i,i,b,e,e,b,_,_,_},
        {_,b,b,f,f,b,b,j,i,i,i,i,j,n,b,j,i,i,i,j,b,b,_,_,_,_},
        {_,_,_,b,b,r,b,i,i,i,i,j,j,j,b,i,j,i,i,i,b,_,_,_,_,_},
        {_,_,_,_,_,b,j,i,i,i,j,i,i,b,b,j,i,j,i,i,b,_,_,_,_,_},
        {_,_,_,_,_,b,j,i,i,i,i,j,b,b,n,n,j,i,i,i,j,b,_,_,_,_},
        {_,_,_,_,b,i,j,j,n,n,n,b,_,b,j,j,n,j,j,j,i,b,_,_,_,_},
        {_,_,_,_,b,i,j,n,j,j,i,b,_,_,b,i,j,n,j,i,b,_,_,_,_,_},
        {_,_,_,_,b,j,i,i,i,i,j,b,_,_,_,b,i,i,i,b,_,_,_,_,_,_},
        {_,_,_,_,b,l,o,i,i,b,b,_,_,_,_,b,k,j,b,_,_,_,_,_,_,_},
        {_,_,_,_,b,l,o,b,b,_,_,_,_,_,_,b,k,j,b,_,_,_,_,_,_,_},
        {_,_,_,_,b,r,r,b,_,_,_,_,_,_,_,_,b,r,b,_,_,_,_,_,_,_},
        {_,_,_,b,l,o,b,_,_,_,_,_,_,_,_,_,b,k,j,b,b,_,_,_,_,_},
        {_,_,_,b,o,l,b,_,_,_,_,_,_,_,_,_,b,k,k,j,j,b,_,_,_,_},
        {_,_,b,l,o,l,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    },
    {
        {_,_,_,_,_,_,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,_,_,_,_,_,b,_,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,a,b,_,_,_,_,b,b,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,a,a,b,b,_,_,b,c,b,_,_,_,b,_,_,_,_,_,_},
        {_,_,_,_,_,b,d,a,a,c,a,b,b,b,c,c,b,_,_,b,_,_,_,_,_,_},
        {_,_,_,_,_,b,c,a,a,c,c,a,c,d,d,c,c,b,b,c,b,_,_,_,_,_},
        {_,_,b,_,_,b,c,a,a,c,a,c,a,a,d,d,c,c,d,c,b,_,_,_,_,_},
        {_,_,b,b,_,b,c,a,a,c,a,a,c,a,a,c,c,c,d,c,c,b,_,_,_,_},
        {_,_,b,a,b,b,c,a,a,c,a,a,a,c,a,a,c,c,d,d,d,b,b,b,b,_},
        {_,_,b,a,a,c,d,c,c,c,c,a,a,c,a,a,c,d,c,a,a,a,a,b,_,_},
        {_,_,b,c,a,a,c,d,d,c,c,a,a,a,c,a,c,d,a,a,a,a,b,_,_,_},
        {_,_,_,b,a,a,a,c,c,d,d,c,a,a,c,a,c,a,a,a,c,b,b,_,_,_},
        {_,_,_,b,c,a,a,a,a,a,d,c,a,c,c,c,c,d,d,d,d,c,c,b,_,_},
        {_,_,_,_,b,d,c,a,a,c,c,c,d,a,a,c,d,a,a,c,d,c,c,c,b,_},
        {b,b,b,b,b,d,d,c,d,a,a,d,c,a,a,a,d,a,a,a,c,b,b,b,b,_},
        {_,b,c,c,c,c,d,d,a,a,a,d,a,a,a,c,e,c,a,a,a,b,_,_,_,b},
        {_,_,b,c,c,c,c,d,a,c,c,d,a,a,c,e,f,f,b,a,a,c,b,_,_,_},
        {_,_,_,b,d,d,c,b,a,c,e,d,d,a,c,f,f,f,f,b,a,a,b,_,_,_},
        {_,_,_,_,b,d,b,e,b,a,e,g,h,d,a,f,f,f,e,b,b,a,b,_,_,_},
        {_,_,b,b,c,c,b,e,e,b,e,g,a,a,d,e,f,f,b,_,_,b,b,_,_,_},
        {_,_,_,_,b,b,b,e,e,g,e,e,a,a,c,a,f,f,b,_,_,_,b,_,_,_},
        {_,_,_,_,_,_,_,b,b,g,e,e,e,f,f,f,f,e,b,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,b,g,e,e,f,f,f,f,b,_,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,e,g,f,f,f,e,b,b,_,_,_,_,_,_,_,_},
        {_,_,_,_,b,b,i,j,i,e,e,e,g,g,b,b,j,j,b,b,_,_,_,_,_,_},
        {_,_,_,b,k,k,l,i,j,i,f,f,f,e,g,f,e,i,j,k,b,_,_,_,_,_},
        {_,_,_,b,l,l,k,l,i,j,j,f,f,f,e,g,f,l,i,k,b,_,_,_,_,_},
        {_,_,b,f,g,f,l,k,i,i,i,i,l,l,l,l,l,l,i,k,b,_,_,_,_,_},
        {_,_,b,g,f,f,e,b,i,i,j,i,i,l,k,k,k,k,a,b,_,_,_,_,_,_},
        {_,_,b,e,f,f,b,b,j,i,i,j,i,i,l,k,k,k,h,b,_,_,_,_,_,_},
        {_,_,b,f,e,b,_,_,b,i,i,j,j,i,i,l,l,i,b,e,b,_,_,_,_,_},
        {_,b,f,f,b,_,_,_,_,b,b,m,m,j,i,i,i,j,b,e,b,_,_,_,_,_},
        {_,b,f,e,b,_,_,_,_,_,b,k,k,k,k,k,k,b,e,k,k,b,_,_,_,_},
        {_,b,m,m,b,_,_,_,_,b,i,j,j,m,m,m,m,b,b,k,k,b,_,_,_,_},
        {b,k,m,m,b,_,_,_,_,b,i,j,i,i,i,n,j,i,b,e,e,e,b,_,_,_},
        {b,f,f,f,f,b,_,_,b,i,j,i,i,i,i,n,n,i,j,b,g,e,b,_,_,_},
        {b,f,f,f,e,f,b,b,b,i,i,i,i,i,j,n,n,i,i,b,g,e,b,_,_,_},
        {b,f,e,f,e,b,b,b,i,i,i,i,i,i,b,n,i,i,i,b,e,e,b,_,_,_},
        {_,b,b,f,f,b,b,j,i,i,i,i,j,n,b,j,i,i,i,j,b,b,_,_,_,_},
        {_,_,_,b,b,a,b,i,i,i,i,j,j,j,b,i,j,i,i,i,b,_,_,_,_,_},
        {_,_,_,_,_,b,j,i,i,i,j,i,i,b,b,j,i,j,i,i,b,_,_,_,_,_},
        {_,_,_,_,_,b,j,i,i,i,i,j,b,b,n,n,j,i,i,i,j,b,_,_,_,_},
        {_,_,_,_,b,i,j,j,n,n,n,b,_,b,j,j,n,j,j,j,i,b,_,_,_,_},
        {_,_,_,_,b,i,j,n,j,j,i,b,_,_,b,i,j,n,j,i,b,_,_,_,_,_},
        {_,_,_,_,b,j,i,i,i,i,j,b,_,_,_,b,i,i,i,b,_,_,_,_,_,_},
        {_,_,_,_,b,l,o,i,i,b,b,_,_,_,_,b,k,j,b,_,_,_,_,_,_,_},
        {_,_,_,_,b,l,o,b,b,_,_,_,_,_,_,b,k,j,b,_,_,_,_,_,_,_},
        {_,_,_,_,b,a,a,b,_,_,_,_,_,_,_,_,b,a,b,_,_,_,_,_,_,_},
        {_,_,_,b,l,o,b,_,_,_,_,_,_,_,_,_,b,k,j,b,b,_,_,_,_,_},
        {_,_,_,b,o,l,b,_,_,_,_,_,_,_,_,_,b,k,k,j,j,b,_,_,_,_},
        {_,_,b,l,o,l,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    },


};
// clang-format on

// --- IMPLEMENTACIONS ---
Enemy::Enemy(int a, int b, int c, int speed)
    : x_min_(a),
      x_max_(b),
      pos_({(x_max_ + x_min_) / 2, c}),
      ini_pos_(pos_),
      speed_(speed),
      lives_(3),
      current_sprite_(sprites_[0]),
      looking_left_(true),
      is_alive_(true) {}

// --- CONSTRUCTOR ---

// --- GETTERS ---

int Enemy::lives() const {
    return lives_;
}

bool Enemy::is_alive() const {
    return is_alive_;
}

pro2::Rect Enemy::get_rect() const {
    if (not is_alive_) {
        return {0, 0, 0, 0};
    }

    int height = current_sprite_.size();
    int width = current_sprite_[0].size();
    return {pos_.x, pos_.y - height, pos_.x + width, pos_.y};
}

// --- SETTERS ---

void Enemy::kill() {
    is_alive_ = false;
}

void Enemy::decrement_lives() {
    lives_--;
}

void Enemy::revive() {
    is_alive_ = true;
    pos_ = ini_pos_;
    looking_left_ = true;
    lives_ = 3;
}

// --- MÈTODES PÚBLICS ---

void Enemy::update() {
    if (not is_alive_) {
        return;
    }

    if (looking_left_) {
        pos_.x -= speed_;
        if (pos_.x <= x_min_) {
            looking_left_ = false;
        }
    } else {
        pos_.x += speed_;
        int width = current_sprite_[0].size();
        if (pos_.x >= x_max_ - width) {
            looking_left_ = true;
        }
    }

    // Actualitza l'sprite per si han canviat les vides
    current_sprite_ = sprites_[lives_ - 1];
}

void Enemy::paint(pro2::Window& window) const {
    if (not is_alive_) {
        return;
    }

    int      height = current_sprite_.size();
    pro2::Pt top_left = {pos_.x, pos_.y - (height - 1)};
    paint_sprite(window, top_left, current_sprite_, looking_left_);
}
