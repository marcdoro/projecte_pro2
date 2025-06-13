#ifndef ENEMY_HH
#define ENEMY_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

class Enemy {
private:
    // --- VARIABLES ---
    int speed_;
    bool looking_left_ = true;
    bool is_alive_ = true;
    pro2::Pt pos_;
    pro2::Rect platform_associated_;
    static const std::vector<std::vector<int>> sprite_;

public:
    // --- CONSTRUCTOR ---
    Enemy(pro2::Rect plat, int speed) : 
    pos_({(plat.right + plat.left + 7)/2, plat.top}), platform_associated_(plat), speed_(speed) {}

    // --- GETTERS ---
    pro2::Pt get_pos() const {return pos_;}
    pro2::Rect get_rect() const;
    bool is_alive() const {return is_alive_;}

    // --- SETTERS ---
    void kill() {is_alive_ = false;}

    // --- LÒGICA PRINCIPAL ---
    void update();
    void paint(pro2::Window& window) const;
};

#endif