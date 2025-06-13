#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

class Projectile {
private:
    // --- VARIABLES D'ANIMACIÓ I ESTAT ---
    int sprite_num_ = 0;
    static const int frame_target_ = 8;
    bool is_active_ = true;
    bool looking_left_;

    // --- VARIABLES DE POSICIÓ I GRÀFICS ---
    pro2::Pt pos_;
    pro2::Pt speed_;
    static const std::vector<std::vector<std::vector<int>>> sprites_;

public:
    // --- CONSTRUCTOR ---
    Projectile(pro2::Pt pos, bool looking_left) : pos_(pos), looking_left_(looking_left) {
        speed_.x = looking_left ? -8 : 8;
        speed_.y = 0;
    }        

    // --- GETTERS ---
    pro2::Rect get_rect() const;
    bool is_active() const {return is_active_;}

    // --- SETTERS ---
    void deactivate() {is_active_ = false;}
    
    // --- LÒGICA PRINCIPAL ---
    void update();
    void paint(pro2::Window& window) const;
};

#endif