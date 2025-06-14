#ifndef MENU_HH
#define MENU_HH

#include <vector>
#include "window.hh"

class Menu {
public:
    enum MenuOptions {PLAY, QUIT};

private:
    static const std::vector<std::vector<int>> menu_play_;
    static const std::vector<std::vector<int>> menu_quit_;

    bool active_;
    bool locked_menu;
    MenuOptions selected_option_; 

public:
    Menu() : active_(true), selected_option_(PLAY) {}

    // --- GETTERS ---
    bool active() const {return active_;}
    bool unlocked() const {return !locked_menu;}
    MenuOptions selected_option() const {return selected_option_;}

    // --- SETTERS / LÒGICA ---
    void switch_active() {active_ = !active_;}
    
    void lock_menu() {locked_menu = true;}
    void unlock_menu() {locked_menu = false;}
    void toggle_option() {
        if (selected_option_ == PLAY) {selected_option_ = QUIT;} 
        else {selected_option_ = PLAY;}
    }

    // --- PINTAR ---
    void paint(pro2::Window& window) const;
};

#endif