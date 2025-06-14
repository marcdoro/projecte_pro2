#ifndef HUD_HH
#define HUD_HH

#include "window.hh"
#include <vector>

class Hud {
private:
    // --- VARIABLES ---
    int number_index_;
    int secs_;
    int ammo_;
    static const std::vector<std::vector<std::vector<int>>> numbers_;

public:
    // --- CONSTRUCTOR ---
    Hud() : number_index_(0), secs_(0), ammo_(0) {};
    
    // --- LÒGICA PRINCIPAL ---
    void update(int n, int s, int a);
    void paint(pro2::Window& window);
};

#endif