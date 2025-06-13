// NOU CONTENIDOR PER EMMAGATZEMAR ELS PROJECTILS QUE TÉ EL PLAYER (DISPARA RÀFAGUES D'ENERGIA)

#ifndef MAGAZINE_HH
#define MAGAZINE_HH

template <class T>
class Magazine {
private:
    struct Item {
        T val;
        Item* next;
    };
    int size_;
    int max_size_; 

    Item* first_;

public:
    Magazine(int max_size) : max_size_(max_size), size_(0), first_(nullptr) {}

    ~Magazine() {
        Item* p = first_;
        while (p != nullptr) {
            Item* aux = p;
            p = p->next;
            delete aux;
        }
        size_ = 0;
    }

    // Com no té sentit realitzar còpies, provoco error de compilador
    Magazine(const Magazine& other) = delete;
    Magazine& operator=(const Magazine& other) = delete;

    int size() const {return size_;}
    int max_size() const {return max_size_;}

    void shoot() {
        if (size_ == 0) return;
        Item* aux = first_;
        first_ = first_->next;
        delete aux;
        size_--;
    }

    void one_reload(const T& value) {
        if (size_ == max_size_) return;
        Item* new_projectile = new Item();
        new_projectile->val = value;
        new_projectile->next = first_;
        first_ = new_projectile;
        size_++;
    }

    void complete_reload(const T& value) {
        if (size_ == max_size_) return;
        int aux = size_;
        for (int i = aux; i < max_size_; i++) {
            Item* new_projectile = new Item();
            new_projectile->val = value;
            new_projectile->next = first_;
            first_ = new_projectile;
            size_++;
        }
    }
};

#endif