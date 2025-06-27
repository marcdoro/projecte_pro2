#ifndef MENU_HH
#define MENU_HH

#include <vector>
#include "window.hh"

/**
 * @class Menu
 * @brief Gestiona els menús del joc, com el menú principal i la pantalla de mort.
 */
class Menu {
 private:
    // --- VARIABLES ---
    bool active_;
    bool locked_menu;

    // Sprites per a les diferents pantalles del menú
    static const std::vector<std::vector<int>> menu_play_;
    static const std::vector<std::vector<int>> menu_quit_;
    static const std::vector<std::vector<int>> death_;

 public:
    /**
     * @enum MenuOptions
     * @brief Defineix les possibles opcions seleccionables al menú.
     */
    enum MenuOptions { PLAY, QUIT };

 private:
    // Estat intern de l'opció seleccionada
    MenuOptions selected_option_;

 public:
    // --- CONSTRUCTOR ---
    Menu();

    // --- GETTERS ---
    /**
     * @brief Comprova si el menú principal està actiu.
     * @return 'true' si el menú està actiu, 'false' altrament.
     */
    bool active() const;

    /**
     * @brief Comprova si el menú no està bloquejat (permet canviar d'opció).
     * @return 'true' si el menú està desbloquejat.
     */
    bool unlocked() const;

    /**
     * @brief Obté l'opció del menú actualment seleccionada.
     * @return El valor de l'enum MenuOptions corresponent a l'opció seleccionada.
     */
    MenuOptions selected_option() const;

    // --- SETTERS / LÒGICA ---
    /**
     * @brief Activa o desactiva el menú.
     */
    void switch_active();

    /**
     * @brief Bloqueja el menú per evitar canvis ràpids d'opció.
     */
    void lock_menu();

    /**
     * @brief Desbloqueja el menú.
     */
    void unlock_menu();

    /**
     * @brief Canvia entre les opcions del menú (PLAY/QUIT).
     */
    void toggle_option();

    // --- PINTAR ---
    /**
     * @brief Dibuixa la pantalla de mort.
     * @param window La finestra de pro2 on es dibuixarà.
     */
    void paint_death(pro2::Window& window) const;

    /**
     * @brief Dibuixa el menú principal, ressaltant l'opció seleccionada.
     * @param window La finestra de pro2 on es dibuixarà.
     */
    void paint_menu(pro2::Window& window) const;
};

#endif