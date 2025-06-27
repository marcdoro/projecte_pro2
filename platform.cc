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

// --- CLASSE BASE: Platform ---

// --- CONSTRUCTOR / DESTRUCTOR ---
Platform::Platform(int left, int right, int top, int bottom, PlatformType type)
    : left_(left), right_(right), top_(top), bottom_(bottom), type_(type) {}

// --- GETTERS ---
int Platform::top() const {
    return top_;
}

int Platform::bot() const {
    return bottom_;
}

int Platform::left() const {
    return left_;
}

int Platform::right() const {
    return right_;
}

PlatformType Platform::type() const {
    return type_;
}

pro2::Rect Platform::get_rect() const {
    return {left_, top_, right_, bottom_};
}

pro2::Rect Platform::get_last_rect() const {
    return last_rect_;
}

pro2::Pt Platform::get_increment() const {
    pro2::Rect curr_rect = get_rect();
    return {curr_rect.left - last_rect_.left, curr_rect.top - last_rect_.top};
}

// --- COL·LISIONS ---
bool Platform::has_crossed_floor_downwards(const pro2::Rect& last_rect,
                                           const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.left < platform_rect.right and curr_rect.right > platform_rect.left and
            last_rect.bottom <= platform_rect.top and curr_rect.bottom >= platform_rect.top);
}

bool Platform::has_crossed_floor_upwards(const pro2::Rect& last_rect,
                                         const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.left < platform_rect.right and curr_rect.right > platform_rect.left and
            last_rect.top >= platform_rect.bottom and curr_rect.top <= platform_rect.bottom);
}

bool Platform::is_hit_from_left_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.top < platform_rect.bottom and curr_rect.bottom > platform_rect.top - 2 and
            last_rect.right <= platform_rect.left and curr_rect.right >= platform_rect.left);
}

bool Platform::is_hit_from_right_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const {
    pro2::Rect platform_rect = get_rect();
    return (curr_rect.top < platform_rect.bottom and curr_rect.bottom > platform_rect.top - 2 and
            last_rect.left >= platform_rect.right and curr_rect.left <= platform_rect.right);
}

bool Platform::is_pt_inside(pro2::Pt pt) const {
    return left_ <= pt.x and pt.x <= right_ and top_ <= pt.y and pt.y <= bottom_;
}

// --- MÈTODES VIRTUALS ---
void Platform::trigger() {}

void Platform::reset() {}

void Platform::update() {}

// --- PINTAR ---
void Platform::paint(pro2::Window& window) const {
    auto platform_texture = get_texture();
    if (platform_texture.empty() or platform_texture[0].empty()) {
        return;
    }

    const int xsz = platform_texture.size();
    const int ysz = platform_texture[0].size();
    for (int i = top_; i < bottom_; i++) {
        for (int j = left_; j < right_; j++) {
            window.set_pixel({j, i}, platform_texture[(i - top_) % xsz][(j - left_) % ysz]);
        }
    }
}

// --- SUBCLASSE: StaticPlatform ---

StaticPlatform::StaticPlatform(int left, int right, int top, int bottom)
    : Platform(left, right, top, bottom, PlatformType::STATIC) {}

const std::vector<std::vector<int>>& StaticPlatform::get_texture() const {
    return texture_;
}

// --- SUBCLASSE: FallingPlatform ---

FallingPlatform::FallingPlatform(int left, int right, int top, int bottom)
    : Platform(left, right, top, bottom, PlatformType::FALLING),
      ini_top_(top),
      ini_bottom_(bottom),
      falling_(false),
      speed_(2) {}

void FallingPlatform::trigger() {
    falling_ = true;
}

void FallingPlatform::update() {
    last_rect_ = get_rect();
    if (falling_) {
        top_ += speed_;
        bottom_ += speed_;
    }
}

void FallingPlatform::reset() {
    top_ = ini_top_;
    bottom_ = ini_bottom_;
    falling_ = false;
}

const std::vector<std::vector<int>>& FallingPlatform::get_texture() const {
    return texture_;
}

// --- SUBCLASSE: MovingPlatform ---

MovingPlatform::MovingPlatform(int  left,
                               int  right,
                               int  top,
                               int  bottom,
                               Axis axis,
                               int  min,
                               int  max,
                               int  speed)
    : Platform(left, right, top, bottom, PlatformType::MOVING),
      axis_(axis),
      min_(min),
      max_(max),
      speed_(speed) {}

MovingPlatform::Axis MovingPlatform::axis() const {
    return axis_;
}

void MovingPlatform::update() {
    last_rect_ = get_rect();
    if (axis_ == Axis::X) {
        left_ += speed_;
        right_ += speed_;
        if ((speed_ < 0 and left_ <= min_) or (speed_ > 0 and right_ >= max_)) {
            speed_ = -speed_;
        }
    } else {
        top_ += speed_;
        bottom_ += speed_;
        if ((speed_ < 0 and top_ <= min_) or (speed_ > 0 and bottom_ >= max_)) {
            speed_ = -speed_;
        }
    }
}

const std::vector<std::vector<int>>& MovingPlatform::get_texture() const {
    return texture_;
}
