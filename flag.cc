#include "flag.hh"
#include "utils.hh"
using namespace std;

const int _ = -1;
const int a = 0x42340c;
const int b = 0xffffff;
const int c = 0x000000;

const vector<vector<int>> Flag::sprite_ = {
    {a, a, _, _, _, _, _, _, _, _, _}, {a, a, b, b, c, c, b, b, c, c, _},
    {a, a, b, b, c, c, b, b, c, c, _}, {a, a, c, c, b, b, c, c, b, b, _},
    {a, a, c, c, b, b, c, c, b, b, _}, {a, a, b, b, c, c, b, b, c, c, _},
    {a, a, b, b, c, c, b, b, c, c, _}, {a, a, c, c, b, b, c, c, b, b, _},
    {a, a, c, c, b, b, c, c, b, b, _}, {a, a, _, _, _, _, _, _, _, _, _},
    {a, a, _, _, _, _, _, _, _, _, _}, {a, a, _, _, _, _, _, _, _, _, _},
    {a, a, _, _, _, _, _, _, _, _, _}, {a, a, _, _, _, _, _, _, _, _, _},
    {a, a, _, _, _, _, _, _, _, _, _}, {a, a, _, _, _, _, _, _, _, _, _}};

// --- IMPLEMENTACIONS ---

// --- CONSTRUCTOR ---
Flag::Flag(pro2::Pt pos) : pos_(pos) {}

// --- GETTER ---
pro2::Rect Flag::get_rect() const {
    int height = sprite_.size();
    int width = sprite_[0].size();
    return {pos_.x, pos_.y - height, pos_.x + width, pos_.y};
}

// --- MÈTODES PÚBLICS ---
void Flag::paint(pro2::Window& window) const {
    int      height = sprite_.size();
    pro2::Pt top_left = {pos_.x, pos_.y - height};
    pro2::paint_sprite(window, top_left, sprite_, false);
}