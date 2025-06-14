#ifndef MAGAZINE_HH
#define MAGAZINE_HH

#include "projectile.hh" 

// Els items enllaçats representen PROJECTILS QUE JA HAN SPAWNEJAT AL JOC.
// per això mètodes com reload només afecten, en aquest cas, al p.i current_ammo_
class Magazine {
private:
    struct Item {  
        Projectile proj;
        Item* next;
    };
    const int capacity_;
    int current_ammo_;
    Item* first_;

public:
    Magazine(int capacity) : capacity_(capacity), current_ammo_(0), first_(nullptr) {}

    ~Magazine() {
        Item* curr = first_;
        while (curr != nullptr) {
            Item* to_delete = curr;
            curr = curr->next;
            delete to_delete;
        }
    }

    // No té sentit fer còpia d'un contenidor únic en el joc
    Magazine(const Magazine& other) = delete;
    Magazine& operator=(const Magazine& other) = delete;

    int size() const {return current_ammo_;}
    int capacity() const {return capacity_;}
    bool can_fire() const {return current_ammo_!=0;}
    void shoot() {
        if (current_ammo_ > 0) {current_ammo_--;}
    }

    void reload(int amount) {
        current_ammo_ += amount;
        if (current_ammo_ > capacity_) current_ammo_ = capacity_;        
    }

    void spawn_projectile(const Projectile& projectile_data) {
        Item* new_proj = new Item{projectile_data, first_};
        first_ = new_proj;

    }

    void remove_inactive() {
        Item* current = first_;
        Item* prev = nullptr;

        while (current != nullptr) {
            if (!current->proj.is_active()) {
                Item* aux = current;
                if (prev == nullptr) {
                    first_ = current->next;
                    current = first_;
                } 
                else {
                    prev->next = current->next;
                    current = current->next;
                }
                delete aux;
            } 
            else {
                prev = current;
                current = current->next;
            }
        }
    }

    Item* first() const {return first_;}

    class Iterator {
    private:
        Item* curr_node_;
        
    public:
        Iterator(Item* node) : curr_node_(node) {}

        Iterator& operator++() {
            if (curr_node_) curr_node_ = curr_node_->next;
            return *this;
        }

        Projectile& operator*() const {return curr_node_->proj;}

        bool operator!=(const Iterator& other) const {
            return curr_node_ != other.curr_node_;
        }

    };
    
    Iterator begin() const{return Iterator(first_);}
    Iterator end() const {return Iterator(nullptr);}
    

};

#endif