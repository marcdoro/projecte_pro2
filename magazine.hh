#ifndef MAGAZINE_HH
#define MAGAZINE_HH

#include "projectile.hh"

/**
 * @class Magazine
 * @brief Contenidor personalitzat (llista enllaçada) per gestionar els projectils del joc.
 * * @details Aquesta classe gestiona tant la munició disponible ('current_ammo_') com la
 * llista de projectils que ja han estat disparats i són actius a l'escena.
 * Proporciona un iterador per poder recórrer els projectils actius.
 */
class Magazine {
 private:
    /**
     * @struct Item
     * @brief Node de la llista enllaçada que conté un projectil.
     */
    struct Item {
        Projectile proj;
        Item      *next;
    };

    const int capacity_;
    int       current_ammo_;
    Item     *first_;

 public:
    /**
     * @class Iterator
     * @brief Classe iteradora per recórrer la llista de projectils del carregador.
     * * @details Permet utilitzar bucles 'for-each' sobre un objecte de la classe Magazine.
     */
    class Iterator {
     private:
        Item *curr_node_;

     public:
        Iterator(Item *node) : curr_node_(node) {}

        /**
         * @brief Avança l'iterador al següent element de la llista.
         * @return Una referència a l'iterador actualitzat.
         */
        Iterator& operator++() {
            if (curr_node_) {
                curr_node_ = curr_node_->next;
            }
            return *this;
        }

        /**
         * @brief Obté el projectil al qual apunta l'iterador.
         * @return Una referència al projectil.
         */
        Projectile& operator*() const {
            return curr_node_->proj;
        }

        /**
         * @brief Compara si dos iteradors són diferents.
         * @param other L'altre iterador amb el qual es compara.
         * @return 'true' si apunten a nodes diferents, 'false' altrament.
         */
        bool operator!=(const Iterator& other) const {
            return curr_node_ != other.curr_node_;
        }
    };

    // --- CONSTRUCTOR / DESTRUCTOR ---
    Magazine(int capacity) : capacity_(capacity), current_ammo_(0), first_(nullptr) {}

    ~Magazine() {
        Item *curr = first_;
        while (curr != nullptr) {
            Item *to_delete = curr;
            curr = curr->next;
            delete to_delete;
        }
    }

    // El contenidor és únic, s'evita la còpia.
    Magazine(const Magazine& other) = delete;
    Magazine& operator=(const Magazine& other) = delete;

    // --- GETTERS ---
    /**
     * @brief Retorna el nombre de bales disponibles per disparar.
     * @return La munició actual.
     */
    int size() const {
        return current_ammo_;
    }

    /**
     * @brief Retorna la capacitat màxima de munició.
     * @return La capacitat total del carregador.
     */
    int capacity() const {
        return capacity_;
    }

    /**
     * @brief Comprova si es pot disparar (si queda munició).
     * @return 'true' si 'current_ammo_' és més gran que zero.
     */
    bool can_fire() const {
        return current_ammo_ != 0;
    }

    /**
     * @brief Retorna un punter al primer node de la llista (per a iteració manual si fos
     * necessari).
     * @return Punter al primer 'Item'.
     */
    Item *first() const {
        return first_;
    }

    // --- SETTERS ---
    /**
     * @brief Decrementa el comptador de munició en una unitat.
     */
    void shoot() {
        if (current_ammo_ > 0) {
            current_ammo_--;
        }
    }

    /**
     * @brief Buida completament el comptador de munició.
     */
    void empty_mag() {
        current_ammo_ = 0;
    }

    /**
     * @brief Afegeix munició al carregador, amb la capacitat com a límit.
     * @param amount La quantitat de munició a afegir.
     */
    void reload(int amount) {
        current_ammo_ += amount;
        if (current_ammo_ > capacity_) {
            current_ammo_ = capacity_;
        }
    }

    // --- MÈTODES PÚBLICS ---
    /**
     * @brief Afegeix un nou projectil a la llista (el crea a l'escena).
     * @param projectile_data L'objecte Projectile a afegir a la llista.
     */
    void spawn_projectile(const Projectile& projectile_data) {
        Item *new_proj = new Item{projectile_data, first_};
        first_ = new_proj;
    }

    /**
     * @brief Neteja la llista, eliminant els projectils que ja no són actius.
     */
    void remove_inactive() {
        Item *current = first_;
        Item *prev = nullptr;

        while (current != nullptr) {
            if (!current->proj.is_active()) {
                Item *aux = current;
                if (prev == nullptr) {
                    first_ = current->next;
                    current = first_;
                } else {
                    prev->next = current->next;
                    current = current->next;
                }
                delete aux;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    /**
     * @brief Retorna un iterador a l'inici de la col·lecció.
     * @return Un 'Iterator' que apunta al primer projectil.
     */
    Iterator begin() const {
        return Iterator(first_);
    }

    /**
     * @brief Retorna un iterador al final de la col·lecció.
     * @return Un 'Iterator' que apunta a 'nullptr'.
     */
    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif