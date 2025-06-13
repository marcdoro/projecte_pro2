#ifndef PLATFORM_HH
#define PLATFORM_HH

#include <vector>
#include "window.hh"

class Platform {
private:
    // --- VARIABLES ---
    int left_, right_, top_, bottom_;
    static const std::vector<std::vector<int>> platform_texture_;

public:
    // --- CONSTRUCTORS ---
    Platform() : left_(0), right_(0), top_(0), bottom_(0) {}
    Platform(const Platform& other) : left_(other.left_), right_(other.right_), top_(other.top_), bottom_(other.bottom_) {}
    Platform(int left, int right, int top, int bottom) : left_(left), right_(right), top_(top), bottom_(bottom) {}

    // --- GETTERS ---
    int top() const {return top_;}
    int bot() const {return bottom_;}
    int left() const {return left_;}
    int right() const {return right_;}
    pro2::Rect get_rect() const {return {left_, top_, right_, bottom_};}

    // --- COL·LISIONS ---
    bool has_crossed_floor_downwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool has_crossed_floor_upwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool is_hit_from_left_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool is_hit_from_right_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool is_pt_inside(pro2::Pt pt) const {return left_ <= pt.x and pt.x <= right_ and top_ <= pt.y and pt.y <= bottom_;}

    // --- PINTAR ---
    void paint(pro2::Window& window) const;
};

#endif