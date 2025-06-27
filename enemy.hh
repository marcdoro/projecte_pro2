#ifndef ENEMY_HH
#define ENEMY_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

/**
 * @class Enemy
 * @brief Representa un enemic bàsic del joc.
 *
 * L'enemic es mou horitzontalment entre dos límits, té un nombre de vides
 * i canvia el seu aspecte (sprite) segons les vides que li queden.
 */
class Enemy {
 private:
    // --- VARIABLES ---
    int speed_;
    int lives_;
    int x_min_, x_max_;

    bool looking_left_;
    bool is_alive_;

    pro2::Pt       pos_;
    const pro2::Pt ini_pos_;

    static const std::vector<std::vector<std::vector<int>>> sprites_;
    std::vector<std::vector<int>>                           current_sprite_;

 public:
    // --- CONSTRUCTOR ---
    Enemy(int a, int b, int c, int speed);

    // --- GETTERS ---
    /**
     * @brief Obté les vides restants de l'enemic.
     * @return El nombre de vides.
     */
    int lives() const;

    /**
     * @brief Comprova si l'enemic és viu.
     * @return 'true' si l'enemic està viu, 'false' en cas contrari.
     */
    bool is_alive() const;
    /**
     * @brief Obté el rectangle que ocupa l'enemic.
     * @return Un pro2::Rect que representa la caixa de col·lisió de l'enemic.
     * Si l'enemic no està viu, retorna un rectangle de mida zero.
     */
    pro2::Rect get_rect() const;

    // --- SETTERS ---
    /**
     * @brief Marca l'enemic com a mort.
     */
    void kill();

    /**
     * @brief Redueix en una les vides de l'enemic.
     */
    void decrement_lives();

    /**
     * @brief Reviu l'enemic, restaurant el seu estat inicial.
     */
    void revive();

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Actualitza l'estat de l'enemic per a un fotograma.
     * @details Gestiona el moviment horitzontal i el canvi de direcció.
     * També actualitza el seu sprite segons les vides que li queden.
     */
    void update();

    /**
     * @brief Dibuixa l'enemic a la finestra.
     * @param window La finestra de pro2 on es debe dibuixar.
     */
    void paint(pro2::Window& window) const;
};

#endif