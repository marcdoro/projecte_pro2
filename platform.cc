#include "platform.hh"
using namespace std;

// --- SPRITES ---
const int a = 0x606060;
const int b = 0x868686;
const int c = 0x34202b;
const int e = 0x3d3544;

// clang-format off
const vector<vector<int>> Platform::platform_texture_ = {
    {a,b,b,b,b,b,b,b,b,b,a,a,a,b,b,b,b},
    {a,a,b,b,b,b,b,b,a,a,a,a,a,b,b,b,b},
    {a,a,b,b,b,b,b,b,a,a,a,a,a,a,a,b,b},
    {a,a,a,a,b,b,b,b,b,b,a,a,a,a,a,b,b},
    {c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c},
    {c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c},
    {a,a,a,c,c,a,a,a,e,e,e,a,a,c,c,a,a},
    {a,a,a,e,e,a,a,e,e,e,e,a,a,e,e,a,a},
    {a,a,a,e,e,a,a,e,e,e,e,e,a,e,e,a,a},
    {a,a,a,c,c,a,a,a,e,e,e,e,a,c,c,a,a},
    {a,a,a,c,c,a,a,a,e,e,e,a,a,c,c,a,a},
};
// clang-format on

// --- IMPLEMENTACIONS ---
void Platform::paint(pro2::Window& window) const {
    const int xsz = platform_texture_.size();
    const int ysz = platform_texture_[0].size();
    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, platform_texture_[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
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