#include "spike.hh"
#include "utils.hh"
using namespace std;

const int _ = -1;
const int a = 0x20272c;
const int b = 0xffffff;
const int c = 0xeeece0;
const int d = 0x55585a;

const vector<vector<int>> Spike::sprite_ = {
    {_, _, _, _, _, a, _, _, _, _, _}, {_, _, _, _, a, c, a, _, _, _, _},
    {_, _, _, _, a, c, a, _, _, _, _}, {_, _, _, a, b, c, b, a, _, _, _},
    {_, _, _, a, b, c, b, a, _, _, _}, {_, _, a, b, c, b, b, b, a, _, _},
    {_, _, a, b, c, b, b, b, a, _, _}, {_, a, b, c, b, b, b, b, b, a, _},
    {_, a, b, c, b, b, b, b, b, a, _}, {_, a, b, c, b, b, b, b, b, a, _},
    {a, b, c, b, b, b, b, b, b, b, a}, {a, b, c, b, b, b, b, b, b, b, a},
    {a, b, c, b, b, b, b, b, b, b, a}, {a, a, a, a, a, a, a, a, a, a, a},
    {a, c, d, c, d, c, d, c, d, c, a}, {a, a, a, a, a, a, a, a, a, a, a}};

// --- IMPLEMENTACIONS ---

// --- CONSTRUCTOR ---
Spike::Spike(pro2::Pt pos) : pos_(pos) {}

// --- GETTER ---
pro2::Rect Spike::get_rect() const {
    int height = sprite_.size();
    int width = sprite_[0].size();
    return {pos_.x, pos_.y - height, pos_.x + width, pos_.y};
}

// --- MÈTODES PÚBLICS ---
void Spike::paint(pro2::Window& window) const {
    int      height = sprite_.size();
    pro2::Pt top_left = {pos_.x, pos_.y - height};
    pro2::paint_sprite(window, top_left, sprite_, false);
}