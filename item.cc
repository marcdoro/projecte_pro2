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
const vector<vector<vector<int>>> Item::sprites_ = {
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
        {b,b,a,a,d,d,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
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
    {
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,c,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
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
    {
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,c,c},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,c,_},
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
    {
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,c,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,c,c,c},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,c,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
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
    {
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,c,c},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,c,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {_,_,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {_,c,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
    },
    {
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,c,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,_,_,b,b,a,a,a,a,a,a,d,d,d,d,b,b,_,_,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {_,_,b,b,a,a,a,a,d,d,d,d,d,d,d,d,d,d,b,b,_,_},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,a,a,c,c,f,f,d,d,f,f,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {_,c,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {c,c,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,_,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
    },
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
        {b,b,a,a,c,c,f,f,d,d,f,f,d,d,f,f,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,d,d,d,d,d,d,d,d,d,d,e,e,b,b},
        {b,b,a,a,c,c,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {b,b,a,a,d,d,d,d,f,f,d,d,f,f,d,d,e,e,e,e,b,b},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,b,b,d,d,d,d,d,d,d,d,d,d,e,e,e,e,b,b,_,_},
        {_,_,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {_,c,_,_,b,b,e,e,e,e,e,e,e,e,e,e,b,b,_,_,_,_},
        {c,c,c,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
        {_,c,_,_,_,_,b,b,b,b,b,b,b,b,b,b,_,_,_,_,_,_},
    },
};

// --- IMPLEMENTACIONS ---
const vector<vector<int>>& Item::get_current_sprite_() const {
    return sprites_[sprite_num_];
}

pro2::Rect Item::get_rect() const  {
    if (collected_) return {0,0,0,0};
    const auto& current_sprite = get_current_sprite_();
    int height = current_sprite.size();
    int width = current_sprite[0].size();
    int half_width = width / 2;
    return {pos_.x - half_width, pos_.y - (height - 1), pos_.x + (width - 1) / 2, pos_.y };                 
}

void Item::animate_() {
    double dy = amplitude_ * sin(static_cast<float>(counter) * angular_speed_);
    pos_.y = ini_pos_y + static_cast<int>(dy);
    counter++;

    curr_frame_++;
    if (curr_frame_ >= frame_target_) {
        sprite_num_ = (sprite_num_+1) % sprites_.size();
        curr_frame_ = 0;
    }
}

void Item::paint(pro2::Window& window) const {
    if (collected_) return;
    const auto& curr_sprite = get_current_sprite_();
    int height = curr_sprite.size();
    int width = curr_sprite[0].size();
    pro2::Pt top_left = {pos_.x - (width / 2), pos_.y - (height - 1)};
    paint_sprite(window, top_left, curr_sprite, false);
}

void Item::update() {
    if (collected_) return;
    animate_();
}