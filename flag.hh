#ifndef FLAG_HH
#define FLAG_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

/**
 * @class Flag
 * @brief Representa un el final del joc
 *
 * Aquest objecte és provoca el fi del joc si el jugador
 * entra en contacte amb ell
 */
class Flag {
 private:
    // --- VARIABLES ---
    pro2::Pt                                   pos_;
    static const std::vector<std::vector<int>> sprite_;

 public:
    // --- CONSTRUCTOR ---
    Flag(pro2::Pt pos);

    // --- GETTER ---
    /**
     * @brief Obté el rectangle de col·lisió de la bandera.
     * @return Un pro2::Rect que representa la seva caixa de col·lisió.
     */
    pro2::Rect get_rect() const;

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Dibuixa la bandera a la pantalla.
     * @param window La finestra de pro2 on es dibuixarà.
     */
    void paint(pro2::Window& window) const;
};

#endif