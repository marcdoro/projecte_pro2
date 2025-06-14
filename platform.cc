#include "platform.hh"
using namespace std;

// --- SPRITES ---
const int a = 0x606060;
const int b = 0x868686;
const int c = 0x34202b;
const int d = 0x3d3544;

const int e = 0x2e4d32;  
const int f = 0x4f7a52; 
const int g = 0x1a3323;  
const int h = 0x3c5a45;

const int i = 0x1e3b5a;
const int j = 0x3f6a94;
const int k = 0x14283c;
const int l = 0x34526b;

// clang-format off
const vector<vector<int>> StaticPlatform::texture_ = {
    {a,b,b,b,b,b,b,b,b,b,a,a,a,b,b,b,b},
    {a,a,b,b,b,b,b,b,a,a,a,a,a,b,b,b,b},
    {a,a,b,b,b,b,b,b,a,a,a,a,a,a,a,b,b},
    {a,a,a,a,b,b,b,b,b,b,a,a,a,a,a,b,b},
    {c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c},
    {c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c},
    {a,a,a,c,c,a,a,a,d,d,d,a,a,c,c,a,a},
    {a,a,a,d,d,a,a,d,d,d,d,a,a,d,d,a,a},
    {a,a,a,d,d,a,a,d,d,d,d,d,a,d,d,a,a},
    {a,a,a,c,c,a,a,a,d,d,d,d,a,c,c,a,a},
    {a,a,a,c,c,a,a,a,d,d,d,a,a,c,c,a,a},
};
const vector<vector<int>> FallingPlatform::texture_ = {
    {e,f,f,f,f,f,f,f,f,f,e,e,e,f,f,f,f},
    {e,e,f,f,f,f,f,f,e,e,e,e,e,f,f,f,f},
    {e,e,f,f,f,f,f,f,e,e,e,e,e,e,e,f,f},
    {e,e,e,e,f,f,f,f,f,f,e,e,e,e,e,f,f},
    {g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g},
    {g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g},
    {e,e,e,g,g,e,e,e,h,h,h,e,e,g,g,e,e},
    {e,e,e,h,h,e,e,h,h,h,h,e,e,h,h,e,e},
    {e,e,e,h,h,e,e,h,h,h,h,h,e,h,h,e,e},
    {e,e,e,g,g,e,e,e,h,h,h,h,e,g,g,e,e},
    {e,e,e,g,g,e,e,e,h,h,h,e,e,g,g,e,e},
};
const vector<vector<int>> MovingPlatform::texture_ = {
    {i,j,j,j,j,j,j,j,j,j,i,i,i,j,j,j,j},
    {i,i,j,j,j,j,j,j,i,i,i,i,i,j,j,j,j},
    {i,i,j,j,j,j,j,j,i,i,i,i,i,i,i,j,j},
    {i,i,i,i,j,j,j,j,j,j,i,i,i,i,i,j,j},
    {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k},
    {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k},
    {i,i,i,k,k,i,i,i,l,l,l,i,i,k,k,i,i},
    {i,i,i,l,l,i,i,l,l,l,l,i,i,l,l,i,i},
    {i,i,i,l,l,i,i,l,l,l,l,l,i,l,l,i,i},
    {i,i,i,k,k,i,i,i,l,l,l,l,i,k,k,i,i},
    {i,i,i,k,k,i,i,i,l,l,l,i,i,k,k,i,i},
};
// clang-format on

// --- IMPLEMENTACIONS ---
void Platform::paint(pro2::Window& window) const {
    auto platform_texture_ = get_texture();
    const int xsz = platform_texture_.size();
    const int ysz = platform_texture_[0].size();
    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, platform_texture_[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
}

pro2::Pt Platform::get_increment() const {
    pro2::Rect curr_rect = get_rect(); 
    return {curr_rect.left - last_rect_.left, curr_rect.top - last_rect_.top};
}

bool Platform::has_crossed_floor_downwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.left < platform_rect.right and 
            curr_rect.right > platform_rect.left and
            last_rect.bottom <= platform_rect.top and
            curr_rect.bottom >= platform_rect.top);
}

bool Platform::has_crossed_floor_upwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.left < platform_rect.right and 
            curr_rect.right > platform_rect.left and
            last_rect.top >= platform_rect.bottom and
            curr_rect.top <= platform_rect.bottom);
}

bool Platform::is_hit_from_left_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.top < platform_rect.bottom and    
            curr_rect.bottom > platform_rect.top-2 and
            last_rect.right <= platform_rect.left and   
            curr_rect.right >= platform_rect.left);    
}

bool Platform::is_hit_from_right_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.top < platform_rect.bottom and   
            curr_rect.bottom > platform_rect.top-2 and
            last_rect.left >= platform_rect.right and  
            curr_rect.left <= platform_rect.right);   
}

StaticPlatform::StaticPlatform(int left, int right, int top, int bottom)
    : Platform(left, right, top, bottom, PlatformType::STATIC) {}

const std::vector<std::vector<int>>& StaticPlatform::get_texture() const {
    return texture_;
}


// --- SUBCLASSE: FallingPlatform ---
FallingPlatform::FallingPlatform(int left, int right, int top, int bottom)
    : Platform(left, right, top, bottom, PlatformType::FALLING) {}

void FallingPlatform::update() {
    if (falling_) {
        top_ += speed_;
        bottom_ += speed_;
    }
}
const std::vector<std::vector<int>>& FallingPlatform::get_texture() const {
    return texture_;
}

// --- SUBCLASSE: MovingPlatform ---
MovingPlatform::MovingPlatform(int left, int right, int top, int bottom, Axis axis ,int min, int max, int speed)
    : Platform(left, right, top, bottom, PlatformType::MOVING), axis_(axis), min_(min), max_(max), speed_(speed) {}

void MovingPlatform::update() {
    if (axis_ == Axis::X) {
        left_ += speed_;
        right_ += speed_;
        if (left_ <= min_ or right_ >= max_) {
            speed_ = -speed_;
        }
    } 
    else {
        top_ += speed_;
        bottom_ += speed_;
        if (top_ <= min_ or bottom_ >= max_) {
            speed_ = -speed_;
        }
    }
}
const std::vector<std::vector<int>>& MovingPlatform::get_texture() const {
    return texture_;
}