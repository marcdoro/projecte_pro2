#include "item.hh"
#include <cmath>
#include "utils.hh"
using namespace std;

// ---SPRITES ---
const int _ = -1;
const int a = 0xffd700;
const int b = 0x211f1d;
const int c = 0xfefcfc;
const int d = 0xf7a500;
const int e = 0xff9024;
const int f = 0xff0000;

// clang-format off
const vector<vector<int>> Item::ball_ = {
    {
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,d,d,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,d,d,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {_,_,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
    },
};


// --- IMPLEMENTACIONS ---

// --- CONSTRUCTOR ---
Item::Item(pro2::Pt pos) 
    : pos_(pos), 
      collected_(false),
      counter(0), 
      ini_pos_y(pos.y) {}


// --- GETTERS ---
pro2::Rect Item::get_rect() const {
    if (collected_) {
        return {0, 0, 0, 0};
    }
    int height = ball_.size();
    int width = ball_[0].size();
    int half_width = width / 2;
    return {pos_.x - half_width, pos_.y - (height - 1), pos_.x + (width - 1) / 2, pos_.y};
}

bool Item::is_collected() const {
    return collected_;
}

// --- SETTERS ---
void Item::collected_set_true() {
    collected_ = true;
}

void Item::collected_set_false() {
    collected_ = false;
}

// --- MÈTODES PÚBLICS ---
void Item::update() {
    if (collected_) {
        return;
    }
    animate_();
}

void Item::paint(pro2::Window& window) const {
    if (collected_) {
        return;
    }
    int height = ball_.size();
    int width = ball_[0].size();
    pro2::Pt top_left = {pos_.x - (width / 2), pos_.y - (height - 1)};
    paint_sprite(window, top_left, ball_, false);
}

void Item::animate_() {
    double dy = amplitude_ * sin(static_cast<float>(counter) * angular_speed_);
    pos_.y = ini_pos_y + static_cast<int>(dy);
    counter++;
}
