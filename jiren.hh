#ifndef JIREN_HH
#define JIREN_HH

#include <set>
#include <vector>
#include "enemy.hh"
#include "magazine.hh"
#include "platform.hh"
#include "spike.hh"
#include "window.hh"

/**
 * @class Jiren
 * @brief Representa el personatge principal controlat pel jugador.
 *
 * Gestiona el moviment, salt, col·lisions, animacions, trets i l'estat
 * (viu/mort) del jugador.
 */
class Jiren {
 private:
    // --- VARIABLES D'ESTAT I ANIMACIÓ ---
    int  accel_time_;
    int  jump_key_, left_key_, right_key_, down_key_;
    int  current_animation_frame_;
    int  animation_frame_;
    bool grounded_;
    bool looking_left_;
    bool is_dead_;
    bool GOD_MODE_;
    bool is_firing_;

    static const int walking_speed_ = 10;
    static const int fire_animation_speed_ = 3;

    // --- VARIABLES DE POSICIÓ I FÍSICA ---
    const pro2::Pt initial_pos_;
    pro2::Pt       pos_, last_pos_;
    pro2::Pt       speed_;
    pro2::Pt       accel_;
    Platform      *on_platform;

    // --- VARIABLES DE JOC I GRÀFICS---
    Magazine                                   magazine_;
    static const std::vector<std::vector<int>> jiren_default_;
    static const std::vector<std::vector<int>> walk_1_, walk_2_, walk_3_, walk_4_;
    static const std::vector<std::vector<int>> jiren_jump_;
    static const std::vector<std::vector<int>> fire_1_, fire_2_;

    std::vector<const std::vector<std::vector<int>> *> walk_frames_;
    std::vector<const std::vector<std::vector<int>> *> fire_frames_;

    // --- FUNCIONS PRIVADES ---
    /** @brief Aplica la física bàsica (gravetat, moviment) al jugador. */
    void default_physics_();

    /** @brief Aplica la física del "mode Déu", permetent moviment lliure. */
    void god_mode_physics_();

    /** @brief Gestiona la lògica de disparar un projectil. */
    void fire();

 public:
    // --- CONSTRUCTOR ---
    Jiren(pro2::Pt pos, int jump_key, int left_key, int right_key, int down_key);

    // --- GETTERS ---
    /** @brief Obté la posició actual del jugador (centre inferior). */
    pro2::Pt pos() const;

    /** @brief Obté la posició des d'on surten els projectils. */
    pro2::Pt shoot_pos() const;

    /** @brief Obté el rectangle de col·lisió actual del jugador. */
    pro2::Rect get_rect() const;

    /** @brief Obté el rectangle de col·lisió del fotograma anterior. */
    pro2::Rect get_last_rect() const;

    /** @brief Comprova si el jugador està sobre una superfície. */
    bool is_grounded() const;

    /** @brief Comprova si el jugador és mort. */
    bool is_dead() const;

    /** @brief Comprova si el jugador mira a l'esquerra. */
    bool is_looking_left() const;

    /** @brief Obté una referència al carregador de projectils del jugador. */
    Magazine& get_magazine();

    // --- SETTERS ---
    /** @brief Estableix la coordenada Y del jugador. */
    void set_y(int y);

    /** @brief Reviu el jugador després de morir. */
    void revive();

    /** @brief Estableix l'estat 'grounded' del jugador. */
    void set_grounded(bool grounded, Platform *p);

    /** @brief Canvia l'estat 'grounded' del jugador. */
    void toggle_grounded();

    /** @brief Recarrega la munició del jugador. */
    void reload();

    // --- MÈTODES PÚBLICS ---
    /** @brief Inicia un salt si el jugador està a terra. */
    void jump();

    /** @brief Actualitza la lògica del jugador per a un fotograma. */
    void update(pro2::Window&               window,
                const std::set<Platform *>& nearby_platforms,
                const std::set<Enemy *>&    nearby_enemies,
                const std::set<Spike *>&    nearby_spikes);

    /** @brief Dibuixa el jugador a la pantalla. */
    void paint(pro2::Window& window) const;

    /** @brief Actualitza la posició dels projectils actius. */
    void update_projectiles();

    /** @brief Dibuixa els projectils actius. */
    void paint_projectiles(pro2::Window& window) const;
};

#endif