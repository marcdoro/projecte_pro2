#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include <list>
#include <vector>
#include "window.hh"

/**
 * @class Background
 * @brief Gestiona el dibuixat del fons del joc.
 *
 * S'encarrega de dibuixar el cel, les estrelles i els planetes amb un
 * efecte de paral·laxi per crear una sensació de profunditat.
 */
class Background {
 private:
    // --- PLANETES ---
    static const std::vector<std::vector<int>> planet_;
    static constexpr float                     planet_factor = 0.1;

    // --- ESTRELLES ---
    int                                                     stars_;
    static const std::vector<std::vector<std::vector<int>>> stars_sprites_;
    std::list<std::pair<pro2::Pt, int>>                     random_positions_;

 public:
    // --- CONSTRUCTOR ---
    Background(int stars, int width, int height);

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Dibuixa un objecte (com un planeta) amb efecte de paral·laxi.
     * @param window La finestra de pro2 on es dibuixa.
     * @param sprite La matriu de l'objecte a dibuixar.
     * @param factor El factor de paral·laxi a aplicar al moviment.
     */
    void paint_object(pro2::Window&                        window,
                      const std::vector<std::vector<int>>& sprite,
                      float                                factor) const;

    /**
     * @brief Dibuixa totes les capes del fons a la finestra.
     *
     * Neteja la finestra amb un color de fons i després dibuixa les
     * estrelles i els planetes en la seva posició corresponent.
     * @param window La finestra de pro2 on s'ha de dibuixar.
     */
    void paint(pro2::Window& window) const;
};

#endif