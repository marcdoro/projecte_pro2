/*SHOUTOUT A @NECROHELIO PELS SPRITES!!!!!!!!!!!!!*/

#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 600, HEIGHT = 400;
const int ZOOM = 2;
const int FPS = 48;

int main() {
    pro2::Window window("PLATFORMER GAME PRO2", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    srand(static_cast<unsigned>(time(NULL)));

    Game game(WIDTH, HEIGHT, FPS);

    while (window.next_frame() && !game.is_finished()) {
        game.update(window);
        game.paint(window);
    }
}
