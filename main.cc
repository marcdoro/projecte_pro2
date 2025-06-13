/*SHOUTOUT A @NECROHELIO PELS SPRITES!!!!!!!!!!!!!*/ 

#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 550, HEIGHT = 330;
const int ZOOM = 4;
const int FPS = 48;

int main() {
    pro2::Window window("PLATFORMER GAME PRO2", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    Game game(WIDTH, HEIGHT, FPS);

    while (window.next_frame() && !game.is_finished()) {
        game.update(window);
        game.paint(window);
    }
}
