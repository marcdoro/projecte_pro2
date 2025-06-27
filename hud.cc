#include "hud.hh"
#include "utils.hh"
using namespace std;

// --- SPRITES ---
const int _ = -1;
const int a = 0xff8c00;
const int b = 0x0;

const vector<vector<vector<int>>> Hud::numbers_ = {{{_, _, b, b, b, _, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {_, _, b, b, b, _, _}},
                                                   {{_, _, b, b, _, _, _},
                                                    {_, b, a, a, b, _, _},
                                                    {b, a, a, a, b, _, _},
                                                    {b, a, a, a, b, _, _},
                                                    {_, b, a, a, b, _, _},
                                                    {_, b, a, a, b, _, _},
                                                    {b, a, a, a, a, b, _},
                                                    {b, a, a, a, a, b, _},
                                                    {_, b, b, b, b, _, _}},
                                                   {{_, _, b, b, b, _, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {_, b, b, a, a, b, _},
                                                    {_, b, a, a, b, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, b, b, b, b, _}},
                                                   {{_, _, b, b, b, _, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {_, b, b, a, a, b, _},
                                                    {b, a, a, b, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {_, _, b, b, b, _, _}},
                                                   {{_, _, _, b, b, _, _},
                                                    {_, _, b, a, a, b, _},
                                                    {_, b, a, a, a, b, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, b, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, b, a, a, b, _},
                                                    {_, _, _, b, b, _, _}},
                                                   {{_, b, b, b, b, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, b, b, _},
                                                    {b, a, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, b, b, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {_, _, b, b, b, _, _}},

                                                   {{_, _, b, b, b, _, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, b, b, _},
                                                    {b, a, a, a, a, b, _},
                                                    {b, a, a, b, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {_, _, b, b, b, _, _}},
                                                   {{_, b, b, b, b, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, b, b, a, b, _},
                                                    {_, _, b, a, a, b, _},
                                                    {_, _, b, a, b, _, _},
                                                    {_, b, a, a, b, _, _},
                                                    {_, b, a, a, b, _, _},
                                                    {_, _, b, b, _, _, _}},
                                                   {{_, _, b, b, b, _, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, b, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {_, _, b, b, b, _, _}},
                                                   {{_, _, b, b, b, _, _},
                                                    {_, b, a, a, a, b, _},
                                                    {b, a, a, a, a, a, b},
                                                    {b, a, a, b, a, a, b},
                                                    {_, b, a, a, a, a, b},
                                                    {_, b, b, b, a, a, b},
                                                    {b, a, a, a, a, a, b},
                                                    {_, b, a, a, a, b, _},
                                                    {_, _, b, b, b, _, _}}};

// --- IMPLEMENTACIONS ---

// --- CONSTRUCTOR ---
Hud::Hud() : number_index_(0), secs_(0), ammo_(0) {}

// --- MÈTODES PÚBLICS ---
void Hud::update(int n, int s, int a) {
    number_index_ = n;
    secs_ = s;
    ammo_ = a;
}

void Hud::paint(pro2::Window& window) {
    pro2::Rect window_rect = window.camera_rect();
    int        pos_x = window_rect.right;
    int        pos_y = window_rect.top;

    for (int i = 0; i < 4; ++i) {
        // Items
        paint_sprite(window, {pos_x - (25 + 9 * i), pos_y + 15},
                     numbers_[(number_index_ == 0) ? 0 : number_index_ % 10], false);
        number_index_ /= 10;

        // Segons
        paint_sprite(window, {pos_x - (25 + 9 * i), pos_y + 30},
                     numbers_[(secs_ == 0) ? 0 : secs_ % 10], false);
        secs_ /= 10;

        // Munició
        paint_sprite(window, {pos_x - (25 + 9 * i), pos_y + 45},
                     numbers_[(ammo_ == 0) ? 0 : ammo_ % 10], false);
        ammo_ /= 10;
    }
}