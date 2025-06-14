#include "game.hh"
#include "utils.hh"
using namespace std;

// left_, right_, top_, bottom_;
// PLATAFORMES DEL NIVELL ---

// CONSTRUCTOR
Game::Game(int width, int height, int fps)
    : jiren_({width / 2, 150}, pro2::Keys::W, pro2::Keys::A, pro2::Keys::D, pro2::Keys::S),background_(100, width, height), 
    items_collected_(0), finished_(false), paused_(false), fps_(fps), frame_counter_(0), menu_(),
    items_ { 
        Item({240, 200}), Item({370, 200}), Item({410, 200}), 
        Item({530, 160}), Item({710, 160}), Item({1030, 140}),
    }
{       
    platforms_.clear(); 
    platforms_.push_back(make_unique<StaticPlatform>(-200, 560, 380, 400));
    platforms_.push_back(make_unique<StaticPlatform>(90, 110, 230, 250));
    platforms_.push_back(make_unique<StaticPlatform>(160, 390, 200, 220));
    platforms_.push_back(make_unique<FallingPlatform>(430, 660, 200, 220));
    platforms_.push_back(make_unique<MovingPlatform>(700, 850, 180, 200, MovingPlatform::Axis::X, 700, 1000, 2));
    platforms_.push_back(make_unique<FallingPlatform>(1000, 1100, 220, 240));
    platforms_.push_back(make_unique<MovingPlatform>(1150, 1250, 300, 320, MovingPlatform::Axis::Y, 200, 350, 1));

    print_collected_items();

    bool first_platform = true;
    for (const auto& p : platforms_) { 
        finder_platforms_.add(p.get()); 
        pro2::Rect platform_rect = p->get_rect();
        if (!first_platform) {
            if (p->type() != PlatformType::FALLING && rand() % 100 < 70 and (platform_rect.right - platform_rect.left) >= 50) {
                enemies_.push_back(Enemy(platform_rect, 1));
            }
        }
        first_platform = false;
    }

    for (Item& i : items_) {finder_items_.add(&i);}
    for (Enemy& e : enemies_) {finder_enemies_.add(&e);}
}

// --- FUNCIONS PRIVADES ---
void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(pro2::Keys::Escape)) {
        finished_ = true;
        return;
    } 
    else if (window.is_key_down(pro2::Keys::P)) {
        paused_ = !paused_;
        return;
    }
}

void Game::items_management(set<Item*>& visible_items, const pro2::Rect& jiren_rect) {
    int aux = 0;
    for (Item* item_pointer : visible_items) {
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
    pro2::Rect jiren_rect = jiren_.get_rect();
    pro2::Rect jiren_rect_expanded = {
        jiren_rect.left - 20, jiren_rect.top - 20, 
        jiren_rect.right + 20, jiren_rect.bottom + 20
    };

    pro2::Rect window_rect = window.camera_rect();

    visible_platforms_ = finder_platforms_.query(window_rect);
    visible_enemies_ = finder_enemies_.query(window_rect);
    visible_items_ = finder_items_.query(window_rect);


    jiren_.update(window, visible_platforms_, visible_enemies_);
    jiren_.update_projectiles();
    if (jiren_.is_dead()) {
        respawn_collected_items();
        jiren_.revive();
    }

    for (auto& e : enemies_) {
        e.update();
        finder_enemies_.update(&e);
    }

    for (auto& p : platforms_) {p.get()->update();}

    for (Projectile& p : jiren_.get_magazine()) {
        pro2::Rect p_rect = p.get_rect();
        if (p.is_active()) {
            if (p_rect.left < window_rect.left - 50 or p_rect.left > window_rect.right + 50) {
                p.deactivate();
                continue;
            }
            for (auto& e : enemies_) {
                if (e.is_alive() and collision(p.get_rect(), e.get_rect())) {
                    p.deactivate(); 
                    e.kill();      
                    break;
                }                
            }
        }
    }

    items_management(visible_items_, jiren_rect);

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

// --- LÒGICA PRINCIPAL
void Game::update(pro2::Window& window) {
    process_keys(window);
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
            } 
            else if (selected == Menu::QUIT) {
                finished_ = true;
            }
        }
        return;
    }

    if (!paused_) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::paint(pro2::Window& window) {
    if (menu_.active()) {
        menu_.paint(window);
        return;
    }

    background_.paint(window);
    
    pro2::Rect window_rect = window.camera_rect();
    
    for (Platform* p : visible_platforms_) {p->paint(window);}
    for (Item* i : visible_items_) {i->paint(window);}
    for (Enemy* e : visible_enemies_) {e->paint(window);}
    jiren_.paint_projectiles(window);

    hud_.paint(window);
    jiren_.paint(window);       
    

}


