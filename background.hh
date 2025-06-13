#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include "window.hh"
#include <vector>
#include <list>

class Background {
private:
    int stars_;
    // --- CAPA 0 -> MUNTANYES ---
    static const std::vector<std::vector<int>> planet1_;
    static constexpr float mountain_factor_ = 0.01;

    // --- CAPA 1 -> PLANETES ---
    static const std::vector<std::vector<int>> planets_;
    static constexpr float planet_factor = 0.1;
    static const std::vector<std::vector<std::vector<int>>> stars_sprites_;

    std::list<std::pair<pro2::Pt, int>> random_positions_;
    // --- FUNCIONS PRIVADES ---
    
    
public:
    // --- CONSTRUCTOR ---
    Background(int stars, int width, int height) : stars_(stars) {
        for (int i = 0; i < stars; i++) {
            // Cada estrella apareixerà a una posció aleatoria amb un sprite aleatori de stars_sprites_
            random_positions_.push_back({{rand()%(width+100), rand()%(height-30)}, rand()%static_cast<int>(stars_sprites_.size())}); 
        }
    };

    // --- LÒGICA PRINCIPAL
    void paint_object(pro2::Window& window, const std::vector<std::vector<int>>& sprite, float factor) const;
    void paint_layer(pro2::Window& window, const std::vector<std::vector<int>>& sprite, float factor) const;
    void paint(pro2::Window& window) const;
    
};

#endif