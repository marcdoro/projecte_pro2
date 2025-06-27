#ifndef FINDER_HH
#define FINDER_HH

#include <map>
#include <set>
#include "geometry.hh"

template <class T>
class Finder {
 private:
    static const int                             CHUNK_SIZE = 100;  // Són chunks quadrats
    std::map<std::pair<int, int>, std::set<T *>> chunks_;
    std::map<T *, std::set<std::pair<int, int>>> object_chunks_;

 public:
    Finder() {};

    void add(T *t) {
        pro2::Rect rect = t->get_rect();

        // Veure a quins chunks pertany
        int left_r = rect.left / CHUNK_SIZE;
        int right_r = rect.right / CHUNK_SIZE;
        int top_r = rect.top / CHUNK_SIZE;
        int bottom_r = rect.bottom / CHUNK_SIZE;

        for (int fila = left_r; fila < right_r + 1; fila++) {
            for (int columna = top_r; columna < bottom_r + 1; columna++) {
                auto curr_chunk = std::make_pair(fila, columna);
                chunks_[curr_chunk].insert(t);
                object_chunks_[t].insert(curr_chunk);
            }
        }
    }

    void update(T *t) {
        remove(t);
        add(t);
    }

    void remove(T *t) {
        auto existeix = object_chunks_.find(t);
        if (existeix == object_chunks_.end()) {
            return;
        }

        const std::set<std::pair<int, int>>& chunks_with_t = existeix->second;

        for (const auto& chunk_id : chunks_with_t) {
            auto it_chunk = chunks_.find(chunk_id);
            if (it_chunk != chunks_.end()) {
                it_chunk->second.erase(t);
                if (it_chunk->second.empty()) {
                    chunks_.erase(
                        it_chunk);  // Si s'ha quedat buit eliminem tot el relacionat al chunk
                }
            }
        }
        object_chunks_.erase(existeix);
    }

    std::set<T *> query(pro2::Rect qrect) const {
        int left_r = qrect.left / CHUNK_SIZE;
        int right_r = qrect.right / CHUNK_SIZE;
        int top_r = qrect.top / CHUNK_SIZE;
        int bottom_r = qrect.bottom / CHUNK_SIZE;

        std::set<T *> result;
        for (int fila = left_r; fila < right_r + 1; fila++) {
            for (int columna = top_r; columna < bottom_r + 1; columna++) {
                auto curr_chunk = std::make_pair(fila, columna);
                auto it_chunk = chunks_.find(curr_chunk);
                if (it_chunk != chunks_.end()) {
                    for (const auto& e : it_chunk->second) {
                        if (collision(e->get_rect(), qrect)) {
                            result.insert(e);
                        }
                    }
                }
            }
        }
        return result;
    }
};

#endif