#ifndef SPIKE_HH
#define SPIKE_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

/**
 * @class Spike
 * @brief Representa un obstacle de punxes estàtic al joc.
 *
 * Aquest objecte és un perill immòbil que pot afectar el jugador si hi
 * entra en contacte.
 */
class Spike {
 private:
    // --- VARIABLES ---
    pro2::Pt                                   pos_;
    static const std::vector<std::vector<int>> sprite_;

 public:
    // --- CONSTRUCTOR ---
    Spike(pro2::Pt pos);

    // --- GETTER ---
    /**
     * @brief Obté el rectangle de col·lisió de la punxa.
     * @return Un pro2::Rect que representa la seva caixa de col·lisió.
     */
    pro2::Rect get_rect() const;

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Dibuixa la punxa a la pantalla.
     * @param window La finestra de pro2 on es dibuixarà.
     */
    void paint(pro2::Window& window) const;
};

#endif