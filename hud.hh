#ifndef HUD_HH
#define HUD_HH

#include <vector>
#include "window.hh"

/**
 * @class Hud
 * @brief Gestiona el Heads-Up Display del joc.
 *
 * S'encarrega de mostrar informació rellevant per al jugador directament
 * a la pantalla, com el temps, els items recollits i la munició.
 */
class Hud {
 private:
    // --- VARIABLES ---
    int number_index_;
    int secs_;
    int ammo_;

    // Conté els sprites per als números del 0 al 9
    static const std::vector<std::vector<std::vector<int>>> numbers_;

 public:
    // --- CONSTRUCTOR ---
    Hud();

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Actualitza els valors que mostra el HUD.
     * @param n Nombre d'items recollits a mostrar.
     * @param s Segons de joc transcorreguts.
     * @param a Munició restant del jugador.
     */
    void update(int n, int s, int a);

    /**
     * @brief Dibuixa el HUD a la pantalla.
     * @details Mostra la informació actualitzada (items, temps, munició)
     * a la cantonada superior dreta de la vista de la càmera.
     * @param window La finestra del joc on es dibuixarà.
     */
    void paint(pro2::Window& window);
};

#endif