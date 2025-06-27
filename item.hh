#ifndef ITEM_HH
#define ITEM_HH

#include <vector>
#include "window.hh"

/**
 * @class Item
 * @brief Representa un objecte recol·lectable en el joc.
 *
 * L'item té una animació de flotació i pot ser recollit pel jugador.
 */
class Item {
 private:
    // --- VARIABLES D'ANIMACIÓ I ESTAT ---
    int  counter;
    int  ini_pos_y;
    bool collected_;

    static const int       amplitude_ = 8;
    static constexpr float angular_speed_ = 0.05;

    // --- VARIABLES DE POSICIÓ I GRÀFICS ---
    pro2::Pt                                   pos_;
    static const std::vector<std::vector<int>> ball_;

    // --- FUNCIONS PRIVADES ---
    /**
     * @brief Gestiona l'animació de flotació de l'item.
     * @details Calcula un desplaçament vertical utilitzant una funció
     * sinusoidal per crear un efecte de moviment amunt i avall.
     */
    void animate_();

 public:
    // --- CONSTRUCTOR ---
    Item(pro2::Pt pos);

    // --- GETTERS ---
    /**
     * @brief Obté el rectangle de col·lisió de l'item.
     * @return Un pro2::Rect que representa la caixa de col·lisió.
     * Si l'item està recollit, retorna un rectangle de mida zero.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Comprova si l'item ha estat recollit.
     * @return Retorna 'true' si ha estat recollit, 'false' en cas contrari.
     */
    bool is_collected() const;

    // --- SETTERS ---
    /**
     * @brief Marca l'item com a recollit.
     */
    void collected_set_true();

    /**
     * @brief Marca l'item com a no recollit (permet reaparèixer).
     */
    void collected_set_false();

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Actualitza l'estat de l'item.
     * @details Executa l'animació de moviment de l'item si no ha estat recollit.
     */
    void update();

    /**
     * @brief Dibuixa l'item a la pantalla.
     * @details No dibuixa res si l'item ja ha estat recollit.
     * @param window La finestra del joc on es dibuixarà.
     */
    void paint(pro2::Window& window) const;
};

#endif