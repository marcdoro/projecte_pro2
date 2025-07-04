#include "utils.hh"
using namespace std;

namespace pro2 {

void paint_hline(pro2::Window& window, int xini, int xfin, int y, Color color) {
    for (int x = xini; x <= xfin; x++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_vline(pro2::Window& window, int x, int yini, int yfin, Color color) {
    for (int y = yini; y <= yfin; y++) {
        window.set_pixel({x, y}, color);
    }
}

bool collision(pro2::Rect r1, pro2::Rect r2) {
    return !(r1.right < r2.left or r1.left > r2.right or r1.bottom < r2.top or r1.top > r2.bottom);
}

void paint_rect(pro2::Window& window, const Rect r, Color color) {
    for (int i = r.top; i <= r.bottom; i++) {
        paint_hline(window, r.left, r.right, i, color);
    }
}

void paint_sprite(pro2::Window&              window,
                  pro2::Pt                   orig,
                  const vector<vector<int>>& sprite,
                  bool                       mirror) {
    for (int i = 0; i < sprite.size(); i++) {
        const vector<int>& line = sprite[i];
        for (int j = 0; j < line.size(); j++) {
            const int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
        }
    }
}

}  // namespace pro2