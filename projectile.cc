#include "projectile.hh"
#include "utils.hh"
using namespace std;

//  --- SPRITES ---
const int _ = -1;
const int a = 0xffffff;
const int b = 0xff0000;
const int c = 0xff7373;
const int d = 0xff9595;

// clang-format off
const vector<vector<vector<int>>> Projectile::sprites_ = {
    {
        {_,_,_,b,b,_,_,_,b,_,_,_,_,_},
        {_,_,_,_,b,b,b,b,c,b,_,_,_,_},
        {_,_,_,_,b,b,c,c,c,d,c,_,_,_},
        {_,_,b,b,b,c,d,d,d,d,d,c,_,_},
        {_,b,b,b,c,c,c,d,d,a,a,a,c,_},
        {b,b,b,c,c,d,d,d,a,a,a,a,a,c},
        {a,a,a,a,a,a,a,a,a,a,a,a,a,d},
        {c,c,c,c,c,d,d,a,a,a,a,a,a,d},
        {b,b,b,c,c,c,d,d,d,a,a,a,c,_},
        {b,b,b,b,b,c,d,d,a,d,a,c,_,_},
        {_,_,_,b,b,b,c,c,c,d,c,_,_,_},
        {_,_,_,_,b,b,b,b,b,b,_,_,_,_},
        {_,_,_,b,b,_,_,_,b,_,_,_,_,_},
    }, 
};
// clang-format on

// --- IMPLEMENTACIONS ---

// --- CONSTRUCTOR ---
Projectile::Projectile(pro2::Pt pos, bool looking_left)
    : pos_(pos), looking_left_(looking_left), sprite_num_(0), is_active_(true) {
    speed_.x = looking_left ? -8 : 8;
    speed_.y = 0;
}

// --- GETTERS ---
pro2::Rect Projectile::get_rect() const {
    if (!is_active_) {
        return {0, 0, 0, 0};
    }
    const auto& current_sprite = sprites_[sprite_num_];
    int         height = current_sprite.size();
    int         width = current_sprite[0].size();
    return {pos_.x + 13, pos_.y - height, pos_.x + width - 13, pos_.y};
}

bool Projectile::is_active() const {
    return is_active_;
}

// --- SETTERS ---
void Projectile::deactivate() {
    is_active_ = false;
}

// --- MÈTODES PÚBLICS ---
void Projectile::update() {
    if (!is_active_) {
        return;
    }
    pos_.x += speed_.x;
}

void Projectile::paint(pro2::Window& window) const {
    if (!is_active_) {
        return;
    }
    const auto& current_sprite = sprites_[sprite_num_];
    int         height = current_sprite.size();
    pro2::Pt    top_left = {pos_.x, pos_.y - (height - 1)};
    paint_sprite(window, top_left, current_sprite, looking_left_);
}