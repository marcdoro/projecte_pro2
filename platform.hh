#ifndef PLATFORM_HH
#define PLATFORM_HH

#include <vector>
#include "window.hh"

enum class PlatformType{STATIC, FALLING, MOVING};

class Platform {
protected:
    // --- VARIABLES ---
    int left_, right_, top_, bottom_;
    pro2::Rect last_rect_;
    PlatformType type_;

public:
    // --- CONSTRUCTORS ---
    Platform(int left, int right, int top, int bottom, PlatformType type) 
    : left_(left), right_(right), top_(top), bottom_(bottom), type_(type) {}

    virtual ~Platform() = default;

    // --- GETTERS ---
    int top() const {return top_;}
    int bot() const {return bottom_;}
    int left() const {return left_;}
    int right() const {return right_;}
    PlatformType type() const {return type_;}
    pro2::Rect get_rect() const {return {left_, top_, right_, bottom_};}
    pro2::Rect get_last_rect() const {return last_rect_;}
    pro2::Pt get_increment() const;

    // --- COL·LISIONS ---
    bool has_crossed_floor_downwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool has_crossed_floor_upwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool is_hit_from_left_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool is_hit_from_right_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;
    bool is_pt_inside(pro2::Pt pt) const {return left_ <= pt.x and pt.x <= right_ and top_ <= pt.y and pt.y <= bottom_;}

    virtual const std::vector<std::vector<int>>& get_texture() const = 0;
    virtual void trigger() {}
    virtual void update() {}

    void update_last_rect() {last_rect_ = get_rect();}

    // --- PINTAR ---
    void paint(pro2::Window& window) const;
};

class StaticPlatform : public Platform {
private:
    static const std::vector<std::vector<int>> texture_;

public:
    StaticPlatform(int left, int right, int top, int bottom);
    virtual const std::vector<std::vector<int>>& get_texture() const override;
};

class FallingPlatform : public Platform {
private:
    static const std::vector<std::vector<int>> texture_;
    bool falling_ = false;
    int speed_ = 2;

public:
    FallingPlatform(int left, int right, int top, int bottom);
    virtual void trigger() override {falling_ = true;}
    virtual void update() override;
    virtual const std::vector<std::vector<int>>& get_texture() const override;
};

class MovingPlatform : public Platform {
public:
    enum class Axis {X, Y};
private:
    static const std::vector<std::vector<int>> texture_;
    Axis axis_;
    int min_;
    int max_;
    int speed_;

public:
    MovingPlatform(int left, int right, int top, int bottom, Axis axis, int min, int max, int speed);
    MovingPlatform::Axis axis() const {return axis_;}
    virtual void update() override;
    virtual const std::vector<std::vector<int>>& get_texture() const override;
};

#endif