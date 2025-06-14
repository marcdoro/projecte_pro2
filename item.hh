#ifndef ITEM_HH
#define ITEM_HH

#include <vector>
#include "window.hh"

class Item {
private:
    // --- VARIABLES D'ANIMACIÓ I ESTAT ---
    int counter;
    int ini_pos_y;
    static const int amplitude_ = 8;
    
    static constexpr float angular_speed_ = 0.05;
    
    bool collected_;
    
    // --- VARIABLES DE POSICIÓ I GRÀFICS ---
    pro2::Pt pos_;
    static const std::vector<std::vector<int>> ball_;

    // --- FUNCIONS PRIVADES ---
    const std::vector<std::vector<int>>& get_current_sprite_() const;
    void animate_();

public:
    // --- CONSTRUCTOR ---
    Item(pro2::Pt pos) : pos_(pos), collected_(false), 
    counter(0), ini_pos_y(pos.y) {}
    
    // --- GETTERS ---
    pro2::Rect get_rect() const;
    bool is_collected() const {return collected_;}
    //bool is_ammo() const {return star_;}

    // --- SETTERS ---
    void collected_set_true() {collected_ = true;}
    void collected_set_false() {collected_ = false;}
    
    // --- LÓGICA PRINCIPAL ---
    void update();
    void paint(pro2::Window& window) const;
};

#endif