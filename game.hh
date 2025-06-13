#ifndef GAME_HH
#define GAME_HH

#include <iostream>
#include <list>
#include <set>
#include "jiren.hh"
#include "platform.hh"
#include "window.hh"
#include "item.hh"
#include "enemy.hh"
#include "finder.hh"
#include "magazine.hh"
#include "hud.hh"
#include "projectile.hh"
#include "background.hh"

class Game {
private:
    // --- VARIABLES D'ESTAT ---
    static const int clock_;
    const int fps_;
    int frame_counter_;
    int items_collected_;
    bool finished_;
    bool paused_;

    // --- OBJECTES DEL JOC ---
    Jiren jiren_;
    Hud hud_;
    Background background_;
    static std::list<Platform> platforms_;
    std::list<Item> items_;
    std::list<Enemy> enemies_;
    std::list<Projectile> projectiles_;


    // OPTIMITZACIÓ ESPACIAL
    Finder<Platform> finder_platforms_;
    Finder<Item> finder_items_;
    Finder<Enemy> finder_enemies_;
    std::set<Platform*> visible_platforms_;
    std::set<Enemy*> visible_enemies_;
    std::set<Item*> visible_items_;

    // --- FUNCIONS PRIVADES ---
    void process_keys(pro2::Window& window);
    void items_management(std::set<Item*>& visible_items, const pro2::Rect& jiren_rect);
    void respawn_collected_items();
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);
    void print_collected_items() {std::cout << "Items aconseguits: " << items_collected_ << std::endl;}
    int get_seconds() const {return (fps_ > 0) ? (frame_counter_ / fps_) : 0;}

public:
    // --- CONSTRUCTOR ---
    Game(int width, int height, int fps);

    // --- LÒGICA PRINCIPAL ---
    void update(pro2::Window& window);
    void paint(pro2::Window& window);
    
    // --- GETTER ---
    bool is_finished() const {return finished_;}

private:
    // --- COLOR FONS ---
    static constexpr int sky_blue = 0x11219c;
};

#endif