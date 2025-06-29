#include "jiren.hh"
#include "spike.hh"
#include "utils.hh"

using namespace std;

// --- SPRITES ---
const int _ = -1;
const int a = 0xffffff;
const int b = 0x000000;
const int c = 0xa39da4;
const int d = 0xdedbe4;
const int e = 0x5c5456;
const int f = 0x32292d;
const int g = 0x812324;
const int h = 0x171415;
const int i = 0xdb2319;
const int j = 0x4f0b0c;
const int k = 0xfbe92b;
const int l = 0xcc2552;
const int m = 0xba4e84;

// clang-format off
const vector<vector<int>> Jiren::jiren_default_ = {
    {_,_,_,_,_,_,_,b,b,b,b,b,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,b,c,d,d,d,c,b,b,_,_,_,_,_,_},
    {_,_,_,_,b,c,c,d,d,d,d,d,d,d,b,_,_,_,_,_},
    {_,_,_,b,c,c,c,d,d,d,d,d,d,d,c,b,_,_,_,_},
    {_,_,_,b,c,c,c,d,d,d,d,d,d,d,d,b,_,_,_,_},
    {_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_,_,_},
    {_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_,_,_},
    {_,_,b,e,e,c,c,d,d,d,d,d,d,d,d,d,b,_,_,_},
    {_,_,b,c,d,c,c,c,d,d,d,c,d,d,d,d,b,_,_,_},
    {_,_,b,b,e,d,c,e,b,b,d,d,e,d,d,c,b,_,_,_},
    {_,_,_,b,e,d,c,e,b,b,a,d,c,d,d,b,_,_,_,_},
    {_,_,_,b,d,c,c,c,e,b,b,c,d,d,d,b,_,_,_,_},
    {_,_,_,_,b,b,c,c,c,d,d,d,d,d,c,b,_,_,_,_},
    {_,_,_,_,_,b,e,c,c,d,d,d,d,d,b,_,_,_,_,_},
    {_,_,_,b,b,b,f,e,c,c,d,d,c,b,b,b,_,_,_,_},
    {_,_,b,i,g,i,i,h,e,e,b,b,b,f,f,b,b,_,_,_},
    {_,b,j,i,i,g,g,f,e,e,b,b,e,f,i,g,b,_,_,_},
    {_,b,i,g,g,b,i,i,f,b,c,a,b,b,b,i,i,b,_,_},
    {_,b,j,j,i,j,b,b,b,e,e,a,a,b,e,b,i,i,b,_},
    {_,_,b,j,i,j,i,i,j,i,e,e,a,e,e,i,b,g,b,_},
    {_,_,_,b,i,i,j,j,i,i,i,e,b,e,i,i,b,g,b,_},
    {_,_,_,_,b,b,b,i,g,g,b,b,b,b,g,i,g,b,_,_},
    {_,_,_,_,_,_,b,b,b,b,i,i,i,b,b,b,b,_,_,_},
    {_,_,_,_,_,_,_,b,i,i,i,i,i,i,b,_,_,_,_,_},
    {_,_,_,_,_,_,b,e,f,f,i,i,i,i,f,b,_,_,_,_},
    {_,_,_,_,_,_,b,e,f,e,e,f,g,h,f,b,_,_,_,_},
    {_,_,_,_,_,b,f,e,e,e,e,f,e,h,f,h,b,_,_,_},
    {_,_,_,_,_,b,e,e,e,e,f,f,e,h,f,f,b,_,_,_},
    {_,_,_,_,b,f,e,e,e,e,f,b,b,f,f,f,b,_,_,_},
    {_,_,_,_,b,e,e,e,e,f,e,b,h,f,f,f,b,b,_,_},
    {_,_,_,b,h,e,e,e,e,e,b,b,h,f,f,f,h,b,_,_},
    {_,_,_,b,h,f,e,e,e,f,b,h,h,f,f,f,h,b,_,_},
    {_,_,_,b,f,f,f,f,h,b,_,b,f,h,h,h,f,b,_,_},
    {_,_,b,e,f,f,h,h,e,b,_,b,f,f,h,f,f,b,_,_},
    {_,_,b,f,e,e,f,f,b,_,_,_,b,h,f,f,b,_,_,_},
    {_,_,b,c,a,e,e,f,b,_,_,_,b,c,a,a,b,_,_,_},
    {_,_,b,c,a,a,b,b,_,_,_,_,_,b,c,a,b,_,_,_},
    {_,b,c,a,a,b,_,_,_,_,_,_,_,b,c,a,a,b,_,_},
    {_,b,c,a,a,b,_,_,_,_,_,_,_,b,c,a,a,a,b,_},
    {_,b,c,a,b,_,_,_,_,_,_,_,_,b,c,c,c,c,c,b},
    {b,b,b,b,b,_,_,_,_,_,_,_,_,b,b,b,b,b,b,b},
};
const vector<vector<int>> Jiren::walk_1_ = {
    {_,_,_,_,_,_,_,_,b,b,b,b,b,b,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,b,b,b,c,d,d,d,c,b,b,b,_,_,_,_},
    {_,_,_,_,_,b,b,c,c,d,d,d,d,d,d,d,b,b,_,_,_},
    {_,_,_,_,_,b,c,c,c,d,d,d,d,d,d,d,c,b,_,_,_},
    {_,_,_,_,b,b,c,c,c,d,d,d,d,d,d,d,d,b,b,_,_},
    {_,_,_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_,_},
    {_,_,_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_,_},
    {_,_,_,_,b,e,e,c,c,d,d,d,d,d,d,d,d,d,b,_,_},
    {_,_,_,_,b,c,d,c,c,c,d,d,d,c,d,d,d,d,b,_,_},
    {_,_,_,_,b,b,e,d,c,e,b,b,d,d,e,d,d,c,b,_,_},
    {_,_,_,_,b,b,e,d,c,e,b,b,a,d,c,d,d,b,_,_,_},
    {_,_,_,_,_,b,d,c,c,c,e,b,b,c,d,d,d,b,_,_,_},
    {_,_,_,_,_,b,b,b,c,c,c,d,d,d,d,d,c,b,_,_,_},
    {_,_,_,_,b,j,j,j,e,c,c,d,d,d,d,d,b,_,_,_,_},
    {_,_,_,_,b,j,g,g,j,h,c,c,d,d,c,b,j,b,_,_,_},
    {_,_,_,b,j,g,g,i,g,j,h,h,b,b,b,f,i,j,b,_,_},
    {_,_,_,b,g,g,i,i,g,j,f,e,f,f,f,e,g,g,b,_,_},
    {_,_,_,b,g,g,g,g,g,j,j,f,e,e,e,e,g,j,b,_,_},
    {_,_,b,j,j,g,g,b,j,i,g,f,e,e,f,e,j,b,_,_,_},
    {_,_,b,g,j,j,j,b,g,j,g,i,f,f,f,f,j,b,_,_,_},
    {_,_,b,g,i,i,j,b,g,i,j,j,j,e,f,j,j,g,b,_,_},
    {_,_,_,b,g,i,i,j,b,j,i,i,j,i,i,g,b,j,b,_,_},
    {_,_,_,b,g,g,g,j,b,e,j,g,i,j,i,j,b,j,b,_,_},
    {_,_,_,b,g,c,a,a,b,e,e,e,g,g,g,j,b,c,_,_,_},
    {_,_,_,_,c,c,a,a,c,a,b,e,e,g,g,f,f,b,_,_,_},
    {_,_,_,_,b,c,a,a,c,c,d,e,e,e,f,f,f,b,_,_,_},
    {_,_,_,_,b,a,a,a,c,c,b,e,e,e,f,f,f,b,_,_,_},
    {_,_,_,_,b,c,a,a,a,e,b,e,e,f,b,f,f,f,b,_,_},
    {_,_,_,_,b,b,c,a,a,b,e,e,e,b,b,f,f,f,b,_,_},
    {_,_,_,_,b,f,b,b,b,e,e,e,f,b,f,f,f,f,f,b,_},
    {_,_,_,b,e,f,f,f,e,e,e,e,b,b,f,f,f,f,f,b,_},
    {_,_,b,e,e,f,f,f,f,f,f,f,b,f,f,f,f,f,f,b,_},
    {_,_,b,e,e,e,f,f,f,f,f,b,b,f,f,f,f,f,f,b,_},
    {_,b,c,f,e,e,e,e,e,f,b,_,b,f,f,f,f,f,f,b,_},
    {_,b,c,a,f,e,e,e,b,b,_,_,_,b,f,f,f,a,b,_,_},
    {b,c,a,a,a,b,b,b,b,_,_,_,_,b,c,a,a,a,b,_,_},
    {b,c,a,a,a,a,b,_,_,_,_,_,_,b,c,a,a,a,b,_,_},
    {b,c,a,a,a,b,_,_,_,_,_,_,_,b,c,a,a,a,a,b,_},
    {b,c,c,c,c,c,b,_,_,_,_,_,_,b,c,c,c,c,c,c,b},
    {_,b,b,b,b,b,b,_,_,_,_,_,_,_,_,b,b,b,b,b,b},
};
const vector<vector<int>> Jiren::walk_2_ = {
    {_,_,_,_,_,_,b,b,b,b,b,b,b,_,_,_,_,_},
    {_,_,_,_,b,b,b,c,d,d,d,c,b,b,b,_,_,_},
    {_,_,_,b,b,c,c,d,d,d,d,d,d,d,b,b,_,_},
    {_,_,_,b,c,c,c,d,d,d,d,d,d,d,c,b,_,_},
    {_,_,b,b,c,c,c,d,d,d,d,d,d,d,d,b,b,_},
    {_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_},
    {_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_},
    {_,_,b,e,e,c,c,d,d,d,d,d,d,d,d,d,b,_},
    {_,_,b,c,d,c,c,c,d,d,d,c,d,d,d,d,b,_},
    {_,_,b,b,e,d,c,e,b,b,d,d,e,d,d,c,b,_},
    {_,_,b,b,e,d,c,e,b,b,a,d,c,d,d,b,_,_},
    {_,_,_,b,d,c,c,c,e,b,b,c,d,d,d,b,_,_},
    {_,_,_,_,b,b,c,c,c,d,d,d,d,d,c,b,_,_},
    {_,_,_,b,j,j,e,c,c,d,d,d,d,d,b,_,_,_},
    {_,_,b,j,g,g,g,h,c,c,d,d,c,b,j,b,_,_},
    {_,b,j,g,g,i,i,g,h,h,b,b,b,f,i,j,b,_},
    {_,b,j,g,i,i,g,g,f,e,f,f,f,e,i,g,j,b},
    {_,b,j,i,g,g,g,g,g,f,e,e,e,e,j,b,j,b},
    {_,b,j,i,j,b,j,i,g,f,f,e,f,f,j,b,g,b},
    {b,j,i,g,j,b,g,j,i,i,g,f,f,j,b,i,g,b},
    {b,j,g,i,j,b,j,g,j,j,j,j,f,j,b,g,i,b},
    {b,j,g,i,b,b,j,j,g,i,i,i,g,b,b,g,j,b},
    {b,j,g,g,b,b,e,g,i,i,g,j,i,g,b,g,j,b},
    {b,c,a,a,b,b,e,e,e,j,j,g,i,j,b,j,j,b},
    {b,c,c,b,b,b,f,e,e,e,f,g,g,f,b,j,b,_},
    {b,c,c,a,c,b,b,e,e,e,e,f,f,f,b,c,b,_},
    {_,b,a,a,c,c,b,e,e,e,f,f,f,f,f,e,b,_},
    {_,b,a,a,c,c,b,e,e,e,e,b,f,f,f,b,_,_},
    {_,_,c,a,a,e,f,e,e,e,e,b,f,f,f,b,_,_},
    {_,_,_,b,b,f,f,e,e,e,e,b,f,f,f,b,_,_},
    {_,_,_,_,b,f,f,f,f,f,f,b,f,f,f,b,_,_},
    {_,_,_,b,f,e,f,f,f,f,f,b,f,f,f,b,_,_},
    {_,_,_,b,c,e,e,e,e,e,f,f,f,f,f,b,_,_},
    {_,_,_,b,c,a,f,e,e,e,b,f,f,f,b,_,_,_},
    {_,_,_,c,a,a,a,a,a,b,f,f,f,b,_,_,_,_},
    {_,_,b,c,a,a,a,a,b,c,a,a,b,_,_,_,_,_},
    {_,_,b,c,a,a,a,b,c,a,a,a,b,_,_,_,_,_},
    {_,_,b,c,c,c,b,b,c,a,a,b,b,_,_,_,_,_},
    {_,_,b,b,b,b,_,b,c,c,c,c,c,b,_,_,_,_},
    {_,_,_,_,_,_,_,_,b,b,b,b,b,b,_,_,_,_},
};
const vector<vector<int>> Jiren::walk_3_ = {
    {_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,b,b,b,c,d,d,d,c,b,b,b,_,_,_,_},
    {_,_,_,_,_,_,_,b,b,c,c,d,d,d,d,d,d,d,b,b,_,_,_},
    {_,_,_,_,_,_,_,b,c,c,c,d,d,d,d,d,d,d,c,b,_,_,_},
    {_,_,_,_,_,_,b,b,c,c,c,d,d,d,d,d,d,d,d,b,b,_,_},
    {_,_,_,_,_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_,_},
    {_,_,_,_,_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_,_},
    {_,_,_,_,_,_,b,e,e,c,c,d,d,d,d,d,d,d,d,d,b,_,_},
    {_,_,_,_,_,_,b,c,d,c,c,c,d,d,d,c,d,d,d,d,b,_,_},
    {_,_,_,_,_,_,b,b,e,d,c,e,b,b,d,d,e,d,d,c,b,_,_},
    {_,_,_,_,_,_,b,b,e,d,c,e,b,b,a,d,c,d,c,b,_,_,_},
    {_,_,_,_,_,_,_,b,d,c,c,c,e,b,b,c,d,d,d,b,_,_,_},
    {_,_,_,_,_,_,_,b,b,b,c,c,c,d,d,d,d,d,c,b,_,_,_},
    {_,_,_,_,_,_,_,b,j,b,e,c,c,d,d,d,d,d,b,_,_,_,_},
    {_,_,_,_,_,_,b,j,h,j,j,e,c,c,d,d,c,b,h,b,_,_,_},
    {_,_,_,_,_,b,j,h,i,h,j,j,e,e,b,b,b,b,h,b,_,_,_},
    {_,_,_,_,b,h,h,i,i,i,h,j,b,e,b,b,b,b,i,b,_,_,_},
    {_,_,_,b,j,h,i,i,i,h,i,i,b,b,e,e,e,b,j,b,_,_,_},
    {_,_,_,b,j,i,h,h,b,j,i,i,i,i,b,e,b,e,j,j,b,_,_},
    {_,_,b,h,h,i,i,j,b,h,j,j,i,i,i,b,b,j,b,h,b,_,_},
    {_,_,b,h,i,i,j,b,b,j,h,h,j,j,j,j,b,b,h,h,b,_,_},
    {_,b,j,h,i,j,b,_,_,b,j,h,h,h,i,i,i,b,j,i,j,b,_},
    {_,b,j,h,j,j,_,_,_,b,e,e,e,j,j,h,h,b,j,j,j,b,_},
    {_,b,a,a,a,b,_,_,_,b,e,e,e,e,e,j,h,b,b,c,e,b,_},
    {_,b,c,c,b,b,_,_,_,b,b,e,b,e,e,b,j,b,b,e,c,b,_},
    {b,c,c,c,c,e,_,_,_,b,e,e,b,e,e,b,b,b,b,e,c,e,b},
    {b,a,a,a,c,c,b,_,_,b,e,e,e,e,e,e,e,b,e,e,c,c,b},
    {b,a,a,a,c,c,b,_,_,b,e,e,e,e,e,e,e,b,e,e,c,c,b},
    {_,c,a,a,a,b,_,_,_,b,e,e,e,e,e,e,e,b,b,e,c,e,b},
    {_,_,b,b,b,_,_,_,_,b,e,e,e,e,e,e,e,b,b,b,b,b,_},
    {_,_,_,_,_,_,_,_,b,b,f,e,e,e,e,e,e,b,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,b,b,f,e,e,e,e,e,b,e,b,_,_,_,_},
    {_,_,_,_,_,_,_,b,b,b,e,e,e,e,e,e,e,e,b,_,_,_,_},
    {_,_,_,_,_,_,_,b,f,b,f,e,e,e,e,e,e,b,b,_,_,_,_},
    {_,_,_,_,_,_,b,f,f,b,f,b,e,e,e,b,b,b,_,_,_,_,_},
    {_,_,_,_,_,b,c,a,a,b,b,b,c,a,a,a,a,b,_,_,_,_,_},
    {_,_,_,_,b,c,a,a,a,a,a,b,b,c,a,a,a,a,_,_,_,_,_},
    {_,_,_,_,b,c,a,a,a,b,b,_,b,c,a,a,a,a,b,b,_,_,_},
    {_,_,_,_,b,c,c,c,c,b,_,_,_,b,c,c,c,c,c,c,b,_,_},
    {_,_,_,_,b,b,b,b,b,_,_,_,_,b,b,b,b,b,b,b,b,_,_},
};
const vector<vector<int>> Jiren::walk_4_ = {
    {_,_,_,_,_,_,b,b,b,b,b,b,b,_,_,_,_,_},
    {_,_,_,_,b,b,b,c,d,d,d,c,b,b,b,_,_,_},
    {_,_,_,b,b,c,c,d,d,d,d,d,d,d,b,b,_,_},
    {_,_,_,b,c,c,c,d,d,d,d,d,d,d,c,b,_,_},
    {_,_,b,b,c,c,c,d,d,d,d,d,d,d,d,b,b,_},
    {_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_},
    {_,_,b,c,c,c,c,d,d,d,d,d,d,d,d,d,b,_},
    {_,_,b,e,e,c,c,d,d,d,d,d,d,d,d,d,b,_},
    {_,_,b,c,d,c,c,c,d,d,d,c,d,d,d,d,b,_},
    {_,_,b,b,e,d,c,e,b,b,d,d,e,d,d,c,b,_},
    {_,_,b,b,e,d,c,e,b,b,a,d,c,d,d,b,_,_},
    {_,_,_,b,d,c,c,c,e,b,b,c,d,d,d,b,_,_},
    {_,_,_,_,b,b,c,c,c,d,d,d,d,d,c,b,_,_},
    {_,_,_,b,j,j,e,c,c,d,d,d,d,d,b,_,_,_},
    {_,_,b,j,g,g,i,h,c,c,d,d,c,b,j,b,_,_},
    {_,_,b,g,i,b,j,j,h,h,b,b,b,b,g,b,_,_},
    {_,b,j,g,i,g,b,j,f,e,f,f,f,f,g,b,_,_},
    {_,b,j,g,i,g,b,i,i,f,e,e,e,f,i,b,b,_},
    {_,b,i,g,g,i,b,g,i,i,f,e,f,e,g,g,j,b},
    {b,g,i,i,j,b,g,j,g,g,i,f,f,g,j,b,g,b},
    {b,g,i,g,j,b,j,i,j,j,j,j,f,j,j,b,g,b},
    {b,j,g,i,j,b,b,j,g,g,g,i,i,i,b,g,i,b},
    {b,j,g,j,b,b,b,e,e,f,j,g,g,i,b,g,i,b},
    {b,j,g,j,b,b,b,e,f,e,e,f,g,g,b,e,c,b},
    {b,j,g,a,c,b,b,b,f,e,e,f,b,j,f,b,c,b},
    {b,c,c,a,a,c,b,f,e,e,e,e,f,f,f,f,c,b},
    {_,b,c,c,a,c,e,e,e,e,e,e,b,f,f,f,b,b},
    {_,b,a,a,a,a,c,e,e,e,e,e,b,f,f,f,f,b},
    {_,_,c,a,a,a,b,e,e,e,e,e,b,f,f,f,f,b},
    {_,_,_,b,b,b,f,e,e,e,e,e,b,f,f,f,f,b},
    {_,_,_,_,b,b,f,f,e,e,e,e,b,f,f,f,b,_},
    {_,_,_,b,c,f,f,f,f,f,f,f,b,f,b,b,_,_},
    {_,_,b,c,b,e,f,f,f,f,f,f,b,b,_,_,_,_},
    {_,_,b,c,b,e,e,f,f,f,f,b,_,_,_,_,_,_},
    {_,_,b,c,b,f,e,e,e,e,f,b,_,_,_,_,_,_},
    {_,_,b,b,b,c,f,e,e,e,b,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,c,a,a,a,b,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,c,a,a,a,a,b,_,_,_,_,_,_},
    {_,_,_,_,_,b,c,c,c,c,c,c,b,_,_,_,_,_},
    {_,_,_,_,_,_,b,b,b,b,b,b,b,_,_,_,_,_},
};
const vector<vector<int>> Jiren::jiren_jump_ = {
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,c,e,d,d,e,b,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,d,d,d,d,d,e,b,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,d,d,d,d,d,d,d,e,b,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,e,e,e,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,d,d,d,e,b,_,_,_,_,_,_},
    {_,_,b,b,b,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_},
    {_,b,a,a,e,b,_,_,_,_,_,_,b,c,c,e,e,d,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_},
    {_,b,e,a,b,a,b,_,_,_,_,_,b,c,d,c,e,e,d,d,d,d,e,d,d,d,b,_,_,_,_,_,_},
    {b,a,a,e,b,b,b,_,_,_,_,b,b,b,e,d,e,e,c,f,f,d,d,c,d,e,b,_,_,_,_,_,_},
    {b,a,e,b,a,b,b,_,_,_,b,b,g,b,e,d,e,e,c,b,b,a,d,e,d,b,_,_,_,_,_,_,_},
    {b,e,a,b,b,e,b,_,_,b,j,g,g,b,d,c,e,e,d,c,f,f,e,d,b,b,_,_,_,_,_,_,_},
    {_,b,b,b,e,g,j,b,b,i,j,i,g,i,b,b,e,e,d,d,d,d,d,d,e,b,_,_,b,b,b,b,_},
    {_,_,_,b,g,g,i,i,i,j,i,i,g,i,g,f,b,e,e,d,d,d,d,d,b,_,_,b,e,b,e,e,b},
    {_,_,_,_,b,i,g,j,j,g,g,g,b,g,i,f,h,b,b,e,d,d,d,b,b,_,_,b,e,c,c,c,b},
    {_,_,_,_,_,b,b,i,i,j,b,b,j,g,g,f,h,h,h,b,b,b,b,g,g,b,b,c,b,e,e,e,b},
    {_,_,_,_,_,_,_,b,b,b,b,i,j,g,g,i,f,h,f,f,h,j,b,j,j,g,i,c,c,c,c,b,_},
    {_,_,_,_,_,_,_,_,_,_,b,g,i,j,g,g,i,f,f,f,j,b,b,b,b,j,g,c,c,e,e,b,_},
    {_,_,_,_,_,_,_,_,_,_,b,b,g,i,j,j,i,i,f,j,b,c,h,h,h,b,b,b,b,b,b,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,g,i,i,i,j,i,g,b,f,h,h,h,h,f,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,f,g,g,g,g,i,b,b,h,h,h,h,h,h,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,f,h,f,f,j,g,b,f,f,h,h,h,h,h,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,f,h,f,h,h,j,b,f,f,f,f,h,h,f,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,f,h,h,h,h,f,b,f,f,f,f,f,f,b,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,h,h,h,h,f,b,e,f,f,f,f,b,b,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,h,h,h,h,h,b,e,a,a,b,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,h,h,h,h,h,b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,h,h,h,h,h,b,b,e,a,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,f,f,h,h,h,f,b,b,e,a,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,f,f,f,f,f,b,_,b,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,h,f,f,f,h,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,h,h,h,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,e,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,e,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,e,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
};
const vector<vector<int>> Jiren::fire_1_ = {
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,c,e,e,d,d,e,b,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,c,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,e,e,e,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,d,d,e,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,c,c,e,e,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,c,c,d,e,e,d,d,d,d,d,g,d,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,c,b,e,d,e,e,c,f,f,d,d,c,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,b,e,d,e,e,c,b,b,a,d,g,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,b,d,c,e,e,d,c,f,f,g,b,g,g,g,g,g,g,g,g,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,e,e,d,d,d,d,d,b,g,g,g,_,_,_,_,_,_,_},
    {_,_,h,i,h,h,_,_,_,g,g,g,g,g,b,e,e,e,d,d,d,d,d,d,b,c,c,g,g,g,g,g,g,g},
    {_,_,_,_,_,i,_,i,h,i,i,i,i,i,i,i,i,e,d,d,d,d,d,b,g,g,g,_,_,_,_,_,_,_},
    {h,j,j,j,i,i,i,c,c,g,g,g,g,d,c,c,b,b,e,d,d,e,b,g,g,g,g,g,g,g,_,_,_,_},
    {_,_,_,j,c,c,c,g,g,g,g,g,g,g,g,g,g,c,b,b,b,b,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,h,i,i,j,g,g,g,h,h,h,h,h,h,h,h,g,c,i,b,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,g,g,g,g,d,d,g,f,f,f,j,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,g,g,g,g,g,g,b,g,g,d,d,g,f,i,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,i,i,h,h,h,i,j,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,b,c,c,j,i,i,i,j,j,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,b,f,c,c,c,c,c,j,c,f,f,f,b,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,b,f,c,c,c,c,c,c,f,c,f,f,f,f,b,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,b,f,c,c,c,c,c,c,f,f,c,f,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,b,c,c,c,c,c,f,f,b,b,b,f,f,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,f,c,c,c,c,f,c,b,b,b,b,f,f,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,c,f,f,f,c,c,c,b,_,_,_,_,b,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,c,f,f,f,f,b,b,_,_,_,_,_,b,b,f,f,f,b,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,c,c,c,f,f,f,b,_,_,_,_,_,_,_,b,c,a,a,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,c,c,f,c,c,b,_,_,_,_,_,_,_,_,_,b,c,a,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,b,b,c,a,a,b,b,_,_,_,_,_,_,_,_,_,_,b,c,a,a,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,b,c,a,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,c,a,a,a,b,_,_,_,_,_,_,_,_,_},
    {_,_,b,c,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,_,_,_,_,_,_,_,_},
    {_,b,c,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,b,b,b,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
};
const vector<vector<int>> Jiren::fire_2_ = {
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,b,c,e,e,d,d,e,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,c,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,e,e,e,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,d,d,e,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,c,e,e,e,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,c,c,e,e,d,d,d,d,d,d,d,d,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,c,c,d,e,e,d,d,d,d,d,e,d,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,c,b,e,d,e,e,c,f,f,d,d,c,b,_,_,_,_,_,_,_,b,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,c,b,e,d,e,e,c,b,b,a,d,e,b,_,_,_,_,_,_,b,e,b,_,b,b},
    {_,_,_,_,_,_,_,_,_,_,_,b,b,d,c,e,e,d,c,f,f,e,b,_,_,_,_,_,_,_,b,e,b,b,e,b},
    {_,_,_,_,_,_,_,_,_,b,b,b,b,b,b,e,e,d,d,d,d,d,b,b,b,b,b,b,b,b,e,c,b,e,b,_},
    {_,_,_,_,_,_,_,b,b,g,g,g,h,b,e,e,e,d,d,d,d,d,d,b,g,i,i,c,c,e,e,b,b,b,b,_},
    {_,_,_,_,_,_,b,j,i,i,j,g,g,h,b,e,e,d,d,d,d,d,b,g,g,g,i,c,c,c,e,b,c,b,b,b},
    {_,_,_,_,_,b,g,j,i,j,i,j,g,c,h,b,b,e,d,d,e,b,b,b,b,b,b,b,b,b,e,b,b,_,_,_},
    {_,_,_,_,b,b,g,i,i,b,b,b,i,g,c,h,h,b,b,b,b,b,_,_,_,_,_,_,_,_,b,e,b,_,_,_},
    {_,_,_,_,b,g,g,j,b,a,a,b,j,g,h,c,h,h,i,b,b,_,_,_,_,_,_,_,_,_,_,b,b,_,_,_},
    {_,_,_,b,g,g,j,b,b,a,c,b,b,b,g,h,h,h,i,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,g,j,i,c,e,a,a,a,a,b,j,j,h,i,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,g,i,e,e,a,a,a,b,i,g,i,j,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,b,b,e,a,a,e,b,g,g,g,g,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,b,b,b,b,b,b,c,c,h,g,f,h,f,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,b,h,c,c,c,c,c,c,h,c,f,h,h,h,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,h,c,c,c,c,c,c,h,h,c,f,h,h,h,h,h,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,b,c,c,c,c,c,h,h,b,b,b,f,f,h,h,f,f,f,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,f,c,c,c,c,h,c,b,b,b,b,h,h,f,f,f,f,h,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,c,f,h,h,c,c,c,b,_,_,_,_,b,f,f,f,f,h,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,c,h,h,f,f,b,b,_,_,_,_,_,b,b,h,h,h,b,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,b,c,c,c,h,h,h,b,_,_,_,_,_,_,_,b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,b,e,c,h,c,c,b,_,_,_,_,_,_,_,_,_,b,e,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,b,b,e,a,a,b,b,_,_,_,_,_,_,_,_,_,_,b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,b,e,a,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,e,a,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,e,e,e,e,e,b,_,_,_,_,_,_,_,_,_,_,_},
    {b,e,a,a,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {b,e,e,e,b,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},    
};
// clang-format on

// --- IMPLEMENTACIONS ---

// --- CONSTRUCTOR ---
Jiren::Jiren(pro2::Pt pos, int jump_key, int left_key, int right_key, int down_key)
    : initial_pos_(pos),
      pos_(pos),
      last_pos_(pos),
      magazine_(3),
      current_animation_frame_(0),
      jump_key_(jump_key),
      left_key_(left_key),
      right_key_(right_key),
      down_key_(down_key),
      animation_frame_(0) {
    walk_frames_.push_back(&walk_1_);
    walk_frames_.push_back(&walk_2_);
    walk_frames_.push_back(&walk_3_);
    walk_frames_.push_back(&walk_4_);

    fire_frames_.push_back(&fire_1_);
    fire_frames_.push_back(&fire_2_);
}

// --- GETTERS ---
pro2::Pt Jiren::pos() const {
    return pos_;
}

pro2::Pt Jiren::shoot_pos() const {
    return {pos_.x, pos_.y - 17};
}

pro2::Rect Jiren::get_rect() const {
    int height = jiren_default_.size();
    int width = jiren_default_[0].size();
    int half_width = width / 2;
    return {pos_.x - half_width, pos_.y - (height - 1), pos_.x + (width - 1) / 2, pos_.y};
}

pro2::Rect Jiren::get_last_rect() const {
    int height = jiren_default_.size();
    int width = jiren_default_[0].size();
    int half_width = width / 2;
    return {last_pos_.x - half_width, last_pos_.y - (height - 1), last_pos_.x + (width - 1) / 2,
            last_pos_.y};
}

bool Jiren::is_grounded() const {
    return grounded_;
}

bool Jiren::is_dead() const {
    return is_dead_;
}

bool Jiren::is_looking_left() const {
    return looking_left_;
}

Magazine& Jiren::get_magazine() {
    return magazine_;
}

// --- SETTERS ---
void Jiren::set_y(int y) {
    pos_.y = y;
}

void Jiren::revive() {
    is_dead_ = false;
    magazine_.empty_mag();
}

void Jiren::set_grounded(bool grounded, Platform *p) {
    grounded_ = grounded;
    if (grounded) {
        speed_.y = 0;
        on_platform = p;
    } else {
        on_platform = nullptr;
    }
}

void Jiren::toggle_grounded() {
    grounded_ = !grounded_;
}

void Jiren::reload() {
    magazine_.reload(5);
}

// --- MÈTODES PÚBLICS ---
void Jiren::jump() {
    if (grounded_) {
        accel_.y = -7;
        grounded_ = false;
        accel_time_ = 2;
    }
}

void Jiren::update(pro2::Window&               window,
                   const std::set<Platform *>& nearby_platforms,
                   const std::set<Enemy *>&    nearby_enemies,
                   const std::set<Spike *>&    nearby_spikes) {
    last_pos_ = pos_;

    if (window.was_key_pressed(pro2::Keys::F)) {
        fire();
    }

    speed_.x = 0;
    if (window.is_key_down(left_key_)) {
        speed_.x = -3;
    } else if (window.is_key_down(right_key_)) {
        speed_.x = 3;
    }

    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    if (window.is_key_down(jump_key_)) {
        jump();
    }

    bool is_moving_horizontally = (speed_.x != 0);
    if (is_firing_) {
        animation_frame_++;
        if (animation_frame_ >= fire_animation_speed_) {
            animation_frame_ = 0;
            current_animation_frame_++;
            if (current_animation_frame_ >= fire_frames_.size()) {
                is_firing_ = false;
                current_animation_frame_ = 0;
            }
        }
    } else if (is_moving_horizontally and grounded_) {
        animation_frame_++;
        if (animation_frame_ >= walking_speed_) {
            animation_frame_ = 0;
            current_animation_frame_ = (current_animation_frame_ + 1) % walk_frames_.size();
        }
    } else {
        current_animation_frame_ = 0;
        animation_frame_ = 0;
    }

    default_physics_();
    set_grounded(false, nullptr);

    pro2::Rect current_rect = get_rect();
    pro2::Rect last_rect = get_last_rect();
    int        dx = pos_.x - last_pos_.x;
    int        dy = pos_.y - last_pos_.y;

    for (Platform *p : nearby_platforms) {
        if (dy > 0) {
            if (p->has_crossed_floor_downwards(last_rect, current_rect)) {
                if (p->type() == PlatformType::FALLING) {
                    p->trigger();
                }
                set_grounded(true, p);
                set_y(p->top());
                accel_time_ = 0;
                speed_.y = 0;
            }
        } else if (dy < 0) {
            if (p->has_crossed_floor_upwards(last_rect, current_rect)) {
                speed_.y = 0;
                accel_time_ = 0;
            }
        }
        if (dx > 0) {
            if (p->is_hit_from_left_(last_rect, current_rect)) {
                pos_.x = p->left() - (get_rect().right - pos_.x);
                speed_.x = 0;
            }
        } else if (dx < 0) {
            if (p->is_hit_from_right_(last_rect, current_rect)) {
                pos_.x = p->right() + (pos_.x - get_rect().left);
                speed_.x = 0;
            }
        }
        if (!grounded_ and p->type() != PlatformType::STATIC) {
            pro2::Rect r = get_rect();
            bool       horizontally_aligned = r.right > p->left() and r.left < p->right();
            bool       vertically_aligned = abs(r.bottom - p->top()) <= 15;
            if (horizontally_aligned and vertically_aligned and speed_.y >= -2) {
                set_grounded(true, p);
                set_y(p->top());
                accel_time_ = 0;
                speed_.y = 0;
            }
        }
    }

    if (grounded_ and on_platform != nullptr and on_platform->type() != PlatformType::STATIC) {
        pro2::Pt platform_increment = on_platform->get_increment();
        pos_.x += platform_increment.x;
        pos_.y += platform_increment.y;
        pro2::Rect r = get_rect();
        int        exces = r.bottom - on_platform->top();
        if (exces != 0) {
            pos_.y -= exces;
        }
    }

    for (Enemy *enemy_ptr : nearby_enemies) {
        if (enemy_ptr->is_alive() and collision(enemy_ptr->get_rect(), current_rect)) {
            is_dead_ = true;
            break;
        }
    }

    if (!is_dead_) {
        for (Spike *spike_ptr : nearby_spikes) {
            if (collision(spike_ptr->get_rect(), current_rect)) {
                is_dead_ = true;
                break;
            }
        }
    }

    if (pos_.y > 1500) {
        is_dead_ = true;
    }

    if (is_dead_) {
        pos_ = initial_pos_;
        speed_ = {0, 0};
        accel_ = {0, 0};
        accel_time_ = 0;
        grounded_ = false;
        on_platform = nullptr;
        current_animation_frame_ = 0;
        animation_frame_ = 0;
        int camera_new_topleft_x = initial_pos_.x - window.width() / 2;
        int camera_new_topleft_y = initial_pos_.y - window.height() / 2;
        window.set_camera_topleft({camera_new_topleft_x, camera_new_topleft_y});
    }
}

void Jiren::paint(pro2::Window& window) const {
    const vector<vector<int>> *sprite_to_draw;
    bool                       is_moving_horizontally = (speed_.x != 0);

    if (is_firing_) {
        sprite_to_draw = fire_frames_[current_animation_frame_];

    } else if (!grounded_) {
        sprite_to_draw = &jiren_jump_;
    } else if (is_moving_horizontally and grounded_) {
        sprite_to_draw = walk_frames_[current_animation_frame_];
    } else {
        sprite_to_draw = &jiren_default_;
    }

    const auto& current_sprite = *sprite_to_draw;
    int         jiren_height = current_sprite.size();
    int         jiren_width = current_sprite[0].size();
    pro2::Pt    top_left = {pos_.x - (jiren_width / 2), pos_.y - jiren_height + 1};
    paint_sprite(window, top_left, current_sprite, looking_left_);
}

void Jiren::update_projectiles() {
    for (Projectile& p : magazine_) {
        p.update();
    }
    magazine_.remove_inactive();
}

void Jiren::paint_projectiles(pro2::Window& window) const {
    for (const Projectile& p : magazine_) {
        p.paint(window);
    }
}

// --- FUNCIONS PRIVADES ---
void Jiren::default_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    const int gravity = 1;
    speed_.y += gravity;
    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }
    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Jiren::god_mode_physics_() {
    pos_.x += speed_.x;
    pos_.y += speed_.y;
    speed_.x = 0;
    speed_.y = 0;
}

void Jiren::fire() {
    if (magazine_.can_fire()) {
        magazine_.shoot();
        Projectile new_proj(shoot_pos(), is_looking_left());
        magazine_.spawn_projectile(new_proj);
        is_firing_ = true;
        animation_frame_ = 0;
        current_animation_frame_ = 0;
    }
}
