#ifndef JIREN_HH
#define JIREN_HH

#include <vector>
#include <set>
#include "platform.hh"
#include "window.hh"
#include "enemy.hh"
#include "magazine.hh"
#include "projectile.hh"

class Jiren {
private:
    // --- VARIABLES D'ESTAT I ANIMACIÓ ---
    int accel_time_ = 0;
    int jump_key_, left_key_, right_key_, down_key_;
    int current_animation_frame_ = 0;
    int animation_frame_= 0;
    static const int walking_speed_ = 10;
    static const int fire_animation_speed_ = 3;

    bool grounded_ = false;
    bool looking_left_ = false;
    bool is_dead_ = false; 
    bool GOD_MODE_ = false;
    bool is_firing_ = false;
    
    // --- VARIABLES DE POSICIÓ I FÍSICA ---
    const pro2::Pt initial_pos_;
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    Platform* on_platform = nullptr;

    // --- VARIABLES DE JOC I GRÀFICS---
    Magazine magazine_;
    static const std::vector<std::vector<int>> jiren_default_;
    static const std::vector<std::vector<int>> walk_1_;
    static const std::vector<std::vector<int>> walk_2_;
    static const std::vector<std::vector<int>> walk_3_;
    static const std::vector<std::vector<int>> walk_4_;
    static const std::vector<std::vector<int>> jiren_jump_;
    static const std::vector<std::vector<int>> god_1_;
    static const std::vector<std::vector<int>> god_2_;
    static const std::vector<std::vector<int>> god_3_;
    static const std::vector<std::vector<int>> fire_1_;
    static const std::vector<std::vector<int>> fire_2_;
    std::vector<const std::vector<std::vector<int>>*> walk_frames_;
    std::vector<const std::vector<std::vector<int>>*> god_frames_;
    std::vector<const std::vector<std::vector<int>>*> fire_frames_;
    
	// --- FUNCIONS PRIVADES ---
	void default_physics_();
    void god_mode_physics_();
    void fire();

public:
    // --- CONSTRUCTOR ---
    Jiren(pro2::Pt pos, int jump_key, int left_key, int right_key, int down_key);
    
    // --- GETTERS ---
    pro2::Pt pos() const {return pos_;}
    pro2::Pt shoot_pos() const {return {pos_.x, pos_.y - 17};}
    pro2::Rect get_rect() const;
    pro2::Rect get_last_rect() const;
    bool is_grounded() const {return grounded_;}
    bool is_dead() const {return is_dead_;}
    bool is_looking_left() const {return looking_left_;}
    Magazine& get_magazine() {return magazine_;}
    

    // --- SETTERS ---
    void set_y(int y) {pos_.y = y;}
    void revive() {is_dead_ = false;}
    void set_grounded(bool grounded, Platform* p); 
    void toggle_grounded() {grounded_ = !grounded_;}
    void reload() {magazine_.reload(5);}
    
    // --- LÒGICA PRINCIPAL ---
    void jump();
    void update(pro2::Window& window, const std::set<Platform*>& nearby_platforms, const std::set<Enemy*>& nearby_enemies);
    void paint(pro2::Window& window) const;
    void update_projectiles();
    void paint_projectiles(pro2::Window& window) const;
};

#endif