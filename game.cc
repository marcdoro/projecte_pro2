#include "game.hh"
#include <iostream>
#include "platform.hh"
#include "spike.hh"
#include "utils.hh"

using namespace std;

// --- CONSTRUCTOR ---

Game::Game(int width, int height, int fps)
    : jiren_({width / 2, 150}, pro2::Keys::W, pro2::Keys::A, pro2::Keys::D, pro2::Keys::S),
      background_(200, width, height),
      items_collected_(0),
      finished_(false),
      fps_(fps),
      frame_counter_(0),
      menu_(),
      flag_({1520, 100}) {
    platforms_.clear();
    enemies_.clear();
    spikes_.clear();

    platforms_.push_back(make_unique<StaticPlatform>(-50, 400, 250, 700));
    platforms_.push_back(
        make_unique<MovingPlatform>(430, 480, 270, 290, MovingPlatform::Axis::Y, 100, 400, -2));
    platforms_.push_back(make_unique<FallingPlatform>(500, 700, 100, 120));
    platforms_.push_back(make_unique<FallingPlatform>(720, 820, 120, 140));
    platforms_.push_back(make_unique<FallingPlatform>(840, 940, 120, 140));
    platforms_.push_back(make_unique<StaticPlatform>(970, 1200, 100, 120));
    platforms_.push_back(
        make_unique<MovingPlatform>(1250, 1350, 100, 120, MovingPlatform::Axis::X, 1250, 1500, 2));

    enemies_.push_back(Enemy(-50, 400, 250, 2));
    enemies_.push_back(Enemy(970, 1200, 100, 3));

    spikes_.push_back(Spike({-50, 250}));
    spikes_.push_back(Spike({0, 250}));
    spikes_.push_back(Spike({50, 250}));
    spikes_.push_back(Spike({100, 250}));
    spikes_.push_back(Spike({150, 250}));
    spikes_.push_back(Spike({200, 250}));
    spikes_.push_back(Spike({250, 250}));
    spikes_.push_back(Spike({350, 250}));

    items_.push_back(Item({-25, 200}));
    items_.push_back(Item({1000, 50}));
    items_.push_back(Item({1300, 50}));

    for (auto& p : platforms_) {
        finder_platforms_.add(p.get());
    }
    for (Item& i : items_) {
        finder_items_.add(&i);
    }
    for (Enemy& e : enemies_) {
        finder_enemies_.add(&e);
    }
    for (Spike& s : spikes_) {
        finder_spikes_.add(&s);
    }

    cout << "\n=========================================================" << endl;
    cout << "||                                                     ||" << endl;
    cout << "||         BENVINGUT/DA A PLATFORMER PRO2 !            ||" << endl;
    cout << "||                                                     ||" << endl;
    cout << "=========================================================" << endl;
    cout << "                   CONTROLS DEL JOC                      " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "\n  [ Controls del Jugador ]\n" << endl;
    cout << "\t[ W ]\t\t- Saltar" << endl;
    cout << "\t[ A ]\t\t- Moure a l'esquerra" << endl;
    cout << "\t[ D ]\t\t- Moure a la dreta" << endl;
    cout << "\t[ F ]\t\t- Disparar" << endl;
    cout << "\n  [ Menú i Pantalles ]\n" << endl;
    cout << "\t[ Amunt/Avall ]\t- Navegar pel menú" << endl;
    cout << "\t[ Enter ]\t- Seleccionar opció / Revivir" << endl;
    cout << "\n  [ Controls Generals ]\n" << endl;
    cout << "\t[ Esc ]\t\t- Sortir del joc" << endl;
    cout << "\n=========================================================" << endl;
    cout << "                  Espero que t'agradi!                  " << endl;
    cout << "=========================================================\n" << endl;
}

// --- GETTER ---

bool Game::is_finished() const {
    return finished_;
}

// --- MÈTODES PÚBLICS ---

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (jiren_.is_dead()) {
        if (window.was_key_pressed(pro2::Keys::Return)) {
            reset_game();
            jiren_.revive();
        }
        return;
    }

    if (menu_.active()) {
        if (!window.is_key_down(pro2::Keys::Up) and !window.is_key_down(pro2::Keys::Down)) {
            menu_.unlock_menu();
        }
        if (menu_.unlocked()) {
            if (window.is_key_down(pro2::Keys::Up) or window.is_key_down(pro2::Keys::Down)) {
                menu_.toggle_option();
                menu_.lock_menu();
            }
        }
        if (window.was_key_pressed(pro2::Keys::Return)) {
            Menu::MenuOptions selected = menu_.selected_option();
            if (selected == Menu::PLAY) {
                menu_.switch_active();
                print_collected_items();
            } else if (selected == Menu::QUIT) {
                finished_ = true;
            }
        }
        return;
    }

    update_objects(window);
    update_camera(window);
}

void Game::paint(pro2::Window& window) {
    if (jiren_.is_dead()) {
        menu_.paint_death(window);
        return;
    }

    if (menu_.active()) {
        menu_.paint_menu(window);
        return;
    }

    background_.paint(window);

    for (Platform *p : visible_platforms_) {
        p->paint(window);
    }
    for (Item *i : visible_items_) {
        i->paint(window);
    }
    for (Spike *s : visible_spikes_) {
        s->paint(window);
    }
    for (Enemy *e : visible_enemies_) {
        e->paint(window);
    }

    jiren_.paint_projectiles(window);
    jiren_.paint(window);
    hud_.paint(window);
    flag_.paint(window);
}

// --- FUNCIONS PRIVADES ---

int Game::get_seconds() const {
    return (fps_ > 0) ? (frame_counter_ / fps_) : 0;
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(pro2::Keys::Escape)) {
        finished_ = true;
        return;
    }
}

void Game::items_management(set<Item *>& visible_items, const pro2::Rect& jiren_rect) {
    int aux = 0;
    for (Item *item_pointer : visible_items) {
        if (!item_pointer->is_collected()) {
            item_pointer->update();
            pro2::Rect item_rect = item_pointer->get_rect();
            if (collision(jiren_rect, item_rect)) {
                jiren_.reload();
                aux++;
                item_pointer->collected_set_true();
                finder_items_.remove(item_pointer);
            }
        }
    }

    if (aux > 0) {
        items_collected_ += aux;
        print_collected_items();
    }
}

void Game::respawn_collected_items() {
    items_collected_ = 0;
    print_collected_items();

    for (Item& i : items_) {
        if (i.is_collected()) {
            i.collected_set_false();
            finder_items_.add(&i);
        }
    }
}

void Game::update_objects(pro2::Window& window) {
    pro2::Rect window_rect = window.camera_rect();

    // Actualitza els sets d'objectes visibles
    visible_platforms_ = finder_platforms_.query(window_rect);
    visible_enemies_ = finder_enemies_.query(window_rect);
    visible_items_ = finder_items_.query(window_rect);
    visible_spikes_ = finder_spikes_.query(window_rect);

    // Actualitza la lògica dels objectes
    for (auto& p : platforms_) {
        p->update();
        finder_platforms_.update(p.get());
    }

    jiren_.update(window, visible_platforms_, visible_enemies_, visible_spikes_);
    jiren_.update_projectiles();

    if (collision(jiren_.get_rect(), flag_.get_rect())) {
        cout << "HAS GUANYAT" << endl;
        finished_ = true;
        return;
    }

    for (auto& e : enemies_) {
        e.update();
        finder_enemies_.update(&e);
    }

    for (Projectile& p : jiren_.get_magazine()) {
        if (p.is_active()) {
            if (p.get_rect().left < window_rect.left - 50 or
                p.get_rect().left > window_rect.right + 50) {
                p.deactivate();
                continue;
            }
            for (auto& e : enemies_) {
                if (e.is_alive() and collision(p.get_rect(), e.get_rect())) {
                    p.deactivate();
                    e.decrement_lives();
                    if (e.lives() == 0) {
                        e.kill();
                    }
                    break;
                }
            }
        }
    }

    items_management(visible_items_, jiren_.get_rect());

    frame_counter_++;
    hud_.update(items_collected_, get_seconds(), jiren_.get_magazine().size());
}

void Game::update_camera(pro2::Window& window) {
    const pro2::Pt pos = jiren_.pos();
    const pro2::Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 8;
    const int right = cam.x + window.width() / 8;
    const int top = cam.y - window.width() / 8;
    const int bot = cam.y + window.width() / 8;

    int dx = 0;
    int dy = 0;

    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }

    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bot) {
        dy = pos.y - bot;
    }

    window.move_camera({dx, dy});
}

void Game::print_collected_items() {
    std::cout << "Items aconseguits: " << items_collected_ << std::endl;
}

void Game::reset_game() {
    for (const auto& p : platforms_) {
        if (p.get()->type() == PlatformType::FALLING) {
            p->reset();
        }
        finder_platforms_.update(p.get());
    }

    for (Enemy& e : enemies_) {
        e.revive();
        finder_enemies_.update(&e);
    }
    frame_counter_ = 0;
    respawn_collected_items();
}