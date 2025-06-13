#include "enemy.hh"
#include "utils.hh"
using namespace std;

// --- SPRITES ---
const int _ = -1;
const int a = 0xeaa844;
const int b = 0x5f0315;
const int c = 0xac042d;
const int d = 0xee3354;
const int e = 0xde9d84;
const int f = 0xf7dab3;
const int g = 0xf8fafa;
const int h = 0x666871;
const int i = 0x3f404d;
const int j = 0xa5b5b6;

// clang-format off
const vector<vector<int>> Enemy::sprite_ = {
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,b,b,b,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,b,_,_,_,_,b,b,b,c,d,d,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,b,b,_,_,b,b,c,d,d,d,d,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,d,b,_,b,c,d,d,d,d,d,d,b,_,b,b,b,_,_,_,_,_,_,_},
    {_,_,_,_,b,c,d,b,b,d,d,d,d,d,d,d,b,b,b,d,b,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,d,d,b,c,d,d,d,d,d,d,c,b,c,d,d,b,_,_,_,_,_,_,_,_},
    {_,b,_,b,c,d,d,b,c,d,d,d,d,d,c,c,c,d,d,c,b,_,_,_,_,_,_,_,_},
    {_,b,b,b,d,d,d,d,c,d,d,d,d,d,c,d,d,d,d,b,b,b,b,b,_,_,_,_,_},
    {_,b,c,b,d,d,d,d,c,c,d,d,d,c,d,d,d,d,d,b,b,c,b,_,_,_,_,_,_},
    {_,b,c,b,c,d,d,d,d,c,c,d,d,d,d,d,d,d,c,b,c,b,_,_,_,_,_,_,_},
    {_,b,c,c,b,d,d,d,d,c,c,d,d,d,d,d,d,d,b,c,b,_,_,_,_,_,_,_,_},
    {_,b,c,c,c,b,c,d,d,b,c,c,d,c,d,d,d,c,b,c,b,_,_,_,_,_,_,_,_},
    {_,_,b,c,c,b,b,c,b,e,e,b,d,c,d,d,d,b,c,b,_,_,_,_,_,_,_,_,_},
    {b,b,b,b,c,c,b,b,e,e,f,f,f,c,c,d,b,e,c,b,_,_,_,_,_,_,_,_,_},
    {_,b,c,c,b,b,b,c,e,a,f,f,f,f,b,d,b,f,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,b,c,c,b,b,c,e,a,e,f,f,f,f,b,f,f,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,b,b,e,b,e,e,b,b,f,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,b,e,a,e,e,a,g,b,b,f,e,f,e,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,b,e,e,e,e,e,g,g,d,c,e,f,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,b,b,e,e,e,f,f,f,f,f,f,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,_,b,b,b,b,e,e,f,f,f,f,f,b,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,_,b,h,h,a,a,b,b,e,f,f,f,b,a,b,_,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,h,h,h,h,a,a,i,b,b,b,b,i,a,i,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,_,b,h,i,i,h,a,a,j,i,i,a,a,i,g,g,b,_,_,_,_,_,_,_,_,_,_},
    {_,_,b,h,h,i,b,b,h,j,j,g,g,g,j,j,g,g,b,_,_,_,b,b,_,_,_,_,_},
    {_,b,i,h,h,b,b,g,b,g,g,g,g,g,g,j,g,j,b,_,_,b,j,j,b,_,_,_,_},
    {b,h,i,h,b,g,g,_,b,a,a,g,a,a,a,a,a,b,i,b,b,a,a,j,b,b,_,_,_},
    {b,h,h,g,g,g,j,_,b,b,g,a,a,a,a,a,a,b,i,j,j,a,a,a,j,b,_,_,_},
    {b,i,h,g,g,j,g,g,j,b,g,a,a,g,g,g,b,b,b,b,b,j,j,j,j,b,_,_,_},
    {_,b,b,j,g,g,g,g,g,b,j,g,g,i,b,b,h,h,h,i,i,b,j,j,b,_,_,_,_},
    {_,_,_,b,b,b,g,g,b,b,g,h,h,h,h,h,h,h,i,h,h,h,b,b,_,_,_,_,_},
    {_,_,_,_,_,_,b,b,_,b,i,h,h,h,h,h,h,h,h,h,h,h,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,b,h,h,h,h,h,h,b,h,h,h,i,i,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,b,i,h,i,i,b,a,h,h,h,i,b,_,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,b,i,b,b,i,i,i,i,b,i,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,b,g,i,i,i,b,i,a,b,_,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,b,j,g,i,i,b,i,i,i,i,b,_,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,b,j,j,g,g,b,_,b,a,i,i,j,b,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,b,g,g,j,j,b,_,_,b,j,j,j,j,b,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,g,g,g,j,b,_,_,_,_,b,j,j,j,b,_,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,g,g,g,b,_,_,_,_,_,_,b,b,b,j,b,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,g,g,b,_,_,_,_,_,_,_,b,j,b,b,_,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,_,_,_,_,_,_,_,b,j,j,j,b,_,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,b,_,_,_,_,_,_,_,_,j,j,j,j,b,_},
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,j,_,_,b},
};
// clang-format on

// --- IMPLEMENTACIONS ---
pro2::Rect Enemy::get_rect() const {
    if (!is_alive_) return {0,0,0,0};
    int width = sprite_[0].size(); 
    int height = sprite_.size();
    return {pos_.x, pos_.y - height, pos_.x + width, pos_.y};
}

void Enemy::paint(pro2::Window& window) const {
    if (!is_alive_) return;
    int height = sprite_.size();
    pro2::Pt top_left = {pos_.x, pos_.y - (height-1)};
    paint_sprite(window, top_left, sprite_, !looking_left_);
}

void Enemy::update() {
    if (!is_alive_) return;
    
    if (looking_left_) {
        pos_.x -= speed_;
        if (pos_.x <= platform_associated_.left) looking_left_ = false;
    }
    else {
        pos_.x += speed_;
        if (pos_.x >= platform_associated_.right - sprite_[0].size()) looking_left_ = true;
    }
}