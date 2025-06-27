#ifndef GAME_HH
#define GAME_HH

#include <list>
#include <memory>
#include <set>
#include "background.hh"
#include "enemy.hh"
#include "finder.hh"
#include "flag.hh"
#include "hud.hh"
#include "item.hh"
#include "jiren.hh"
#include "menu.hh"
#include "platform.hh"
#include "spike.hh"
#include "window.hh"

/**
 * @class Game
 * @brief Orquestra tots els elements i la lògica principal del joc.
 *
 * S'encarrega del bucle principal, gestionant l'estat del joc,
 * els objectes, les entrades de teclat, la càmera i el dibuixat.
 */
class Game {
 private:
    // --- VARIABLES D'ESTAT ---
    const int fps_;
    int       frame_counter_;
    int       items_collected_;
    bool      finished_;

    // --- OBJECTES DEL JOC ---
    Jiren                                jiren_;
    Hud                                  hud_;
    Background                           background_;
    Menu                                 menu_;
    Flag                                 flag_;
    std::list<std::unique_ptr<Platform>> platforms_;
    std::list<Item>                      items_;
    std::list<Enemy>                     enemies_;
    std::list<Spike>                     spikes_;

    // --- OPTIMITZACIÓ ESPACIAL ---
    Finder<Platform>     finder_platforms_;
    Finder<Item>         finder_items_;
    Finder<Enemy>        finder_enemies_;
    Finder<Spike>        finder_spikes_;
    std::set<Platform *> visible_platforms_;
    std::set<Enemy *>    visible_enemies_;
    std::set<Item *>     visible_items_;
    std::set<Spike *>    visible_spikes_;

    // --- FUNCIONS PRIVADES ---
    /**
     * @brief Calcula els segons de joc transcorreguts.
     * @return El temps de joc en segons.
     */
    int get_seconds() const;

    /**
     * @brief Processa les entrades de teclat generals del joc.
     * @details Actualment, gestiona la tecla 'Escape' per sortir del joc.
     * @param window La finestra del joc per consultar l'estat de les tecles.
     */
    void process_keys(pro2::Window& window);

    /**
     * @brief Gestiona la interacció del jugador amb els items visibles.
     * @details Comprova si el jugador col·lideix amb algun item, l'afegeix
     * a l'inventari, i l'elimina de l'escena.
     * @param visible_items Un set de punters als items actualment visibles.
     * @param jiren_rect El rectangle de col·lisió del jugador.
     */
    void items_management(std::set<Item *>& visible_items, const pro2::Rect& jiren_rect);

    /**
     * @brief Fa reaparèixer tots els items que havien estat recollits.
     * @details Marca tots els items com a no recollits i els torna a afegir
     * al cercador espacial.
     */
    void respawn_collected_items();

    /**
     * @brief Actualitza l'estat de tots els objectes del joc.
     * @details Actualitza jugador, enemics, plataformes, projectils i HUD.
     * @param window La finestra del joc, necessària per a l'update del jugador.
     */
    void update_objects(pro2::Window& window);

    /**
     * @brief Ajusta la posició de la càmera per seguir al jugador.
     * @details Manté el jugador dins d'una "dead zone" al centre de la pantalla.
     * @param window La finestra del joc per manipular la càmera.
     */
    void update_camera(pro2::Window& window);

    /**
     * @brief Imprimeix el nombre d'items recollits per la consola.
     */
    void print_collected_items();

    /**
     * @brief Reinicia l'estat del nivell després que el jugador mori.
     * @details Fa reaparèixer enemics i items, i reseteja les plataformes.
     */
    void reset_game();

 public:
    // --- CONSTRUCTOR ---
    Game(int width, int height, int fps);

    // --- GETTER ---
    /**
     * @brief Comprova si el joc ha finalitzat.
     * @return Retorna 'true' si el joc ha acabat, 'false' en cas contrari.
     */
    bool is_finished() const;

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Actualitza l'estat del joc per a un fotograma.
     * @details Processa les tecles, actualitza tots els objectes, la càmera i
     * gestiona la lògica dels menús o de la partida.
     * @param window La finestra del joc, per accedir a l'entrada de teclat.
     */
    void update(pro2::Window& window);

    /**
     * @brief Dibuixa tots els elements del joc a la pantalla.
     * @details Dibuixa el fons, plataformes, enemics, objectes, jugador i HUD,
     * o els menús si estan actius.
     * @param window La finestra del joc on es dibuixarà tot.
     */
    void paint(pro2::Window& window);
};

#endif