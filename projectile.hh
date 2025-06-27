#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

/**
 * @class Projectile
 * @brief Representa un projectil disparat pel jugador.
 * @details Es mou en línia recta en una direcció fins que col·lideix o surt
 * de la pantalla.
 */
class Projectile {
 private:
    // --- VARIABLES D'ANIMACIÓ I ESTAT ---
    int  sprite_num_;
    bool is_active_;
    bool looking_left_;

    // --- VARIABLES DE POSICIÓ I GRÀFICS ---
    pro2::Pt                                                pos_;
    pro2::Pt                                                speed_;
    static const std::vector<std::vector<std::vector<int>>> sprites_;

 public:
    // --- CONSTRUCTOR ---
    Projectile(pro2::Pt pos, bool looking_left);

    // --- GETTERS ---
    /**
     * @brief Obté el rectangle de col·lisió del projectil.
     * @return Un pro2::Rect que representa la seva caixa de col·lisió.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Comprova si el projectil està actiu.
     * @details Un projectil inactiu està pendent de ser eliminat.
     * @return 'true' si el projectil està actiu, 'false' altrament.
     */
    bool is_active() const;

    // --- SETTERS ---
    /**
     * @brief Desactiva el projectil (per a la seva posterior eliminació).
     */
    void deactivate();

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Actualitza la posició del projectil segons la seva velocitat.
     */
    void update();

    /**
     * @brief Dibuixa el projectil a la pantalla si està actiu.
     * @param window La finestra de pro2 on es dibuixarà.
     */
    void paint(pro2::Window& window) const;
};

#endif  // PROJECTILE_HH