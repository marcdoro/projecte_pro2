#ifndef MENU_HH
#define MENU_HH

#include <vector>
#include "window.hh"

class Menu {
private:
    static const std::vector<std::vector<int>> menu_;
    bool active_;

public:
    Menu() : active_(true) {}

    bool active() const {return active_;}

    void switch_active() {active_ = !active_;}
    //void update();
    void paint(pro2::Window& window) const;
};

#endif