#ifndef PLATFORM_HH
#define PLATFORM_HH

#include <vector>
#include "window.hh"

/**
 * @enum PlatformType
 * @brief Defineix els diferents tipus de plataformes que poden existir al joc.
 */
enum class PlatformType { STATIC, FALLING, MOVING };

/**
 * @class Platform
 * @brief Classe base abstracta per a totes les plataformes del joc.
 * @details Defineix la interfície comuna i les propietats bàsiques que totes les
 * plataformes han de tenir, com la posició, dimensions i mètodes de col·lisió.
 */
class Platform {
 protected:
    // --- VARIABLES ---
    int          left_, right_, top_, bottom_;
    pro2::Rect   last_rect_;
    PlatformType type_;

 public:
    // --- CONSTRUCTOR / DESTRUCTOR ---
    Platform(int left, int right, int top, int bottom, PlatformType type);
    virtual ~Platform() = default;

    // --- GETTERS ---
    /** @brief Retorna la coordenada Y superior de la plataforma. */
    int top() const;

    /** @brief Retorna la coordenada Y inferior de la plataforma. */
    int bot() const;

    /** @brief Retorna la coordenada X esquerra de la plataforma. */
    int left() const;

    /** @brief Retorna la coordenada X dreta de la plataforma. */
    int right() const;

    /** @brief Retorna el tipus de la plataforma. */
    PlatformType type() const;

    /** @brief Retorna el rectangle actual que ocupa la plataforma. */
    pro2::Rect get_rect() const;

    /** @brief Retorna el rectangle que ocupava la plataforma en el fotograma anterior. */
    pro2::Rect get_last_rect() const;

    /** @brief Obté el desplaçament de la plataforma en el darrer fotograma. */
    pro2::Pt get_increment() const;

    // --- COL·LISIONS ---
    /** @brief Comprova si un rectangle ha creuat la part superior de la plataforma cap avall. */
    bool has_crossed_floor_downwards(const pro2::Rect& last_rect,
                                     const pro2::Rect& curr_rect) const;

    /** @brief Comprova si un rectangle ha creuat la part inferior de la plataforma cap amunt. */
    bool has_crossed_floor_upwards(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;

    /** @brief Comprova si un rectangle ha col·lidit amb el costat esquerre de la plataforma. */
    bool is_hit_from_left_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;

    /** @brief Comprova si un rectangle ha col·lidit amb el costat dret de la plataforma. */
    bool is_hit_from_right_(const pro2::Rect& last_rect, const pro2::Rect& curr_rect) const;

    /** @brief Comprova si un punt es troba dins de la plataforma. */
    bool is_pt_inside(pro2::Pt pt) const;

    // --- MÈTODES VIRTUALS ---
    /** @brief Obté la textura de la plataforma (mètode virtual pur). */
    virtual const std::vector<std::vector<int>>& get_texture() const = 0;

    /** @brief Activa el comportament especial de la plataforma (ex: caiguda). */
    virtual void trigger();

    /** @brief Reinicia l'estat de la plataforma a la seva posició inicial. */
    virtual void reset();

    /** @brief Actualitza l'estat de la plataforma per a un fotograma. */
    virtual void update();

    // --- PINTAR ---
    /** @brief Dibuixa la plataforma a la pantalla. */
    void paint(pro2::Window& window) const;
};

/**
 * @class StaticPlatform
 * @brief Una plataforma que no es mou.
 */
class StaticPlatform : public Platform {
 private:
    static const std::vector<std::vector<int>> texture_;

 public:
    StaticPlatform(int left, int right, int top, int bottom);

    /** @brief Retorna la textura per a les plataformes estàtiques. */
    virtual const std::vector<std::vector<int>>& get_texture() const override;
};

/**
 * @class FallingPlatform
 * @brief Una plataforma que cau quan el jugador la trepitja.
 */
class FallingPlatform : public Platform {
 private:
    static const std::vector<std::vector<int>> texture_;
    bool                                       falling_;
    int                                        speed_;
    const int                                  ini_top_, ini_bottom_;

 public:
    FallingPlatform(int left, int right, int top, int bottom);

    /** @brief Activa la caiguda de la plataforma. */
    virtual void trigger() override;

    /** @brief Actualitza la posició de la plataforma si està caient. */
    virtual void update() override;

    /** @brief Reinicia la posició i l'estat de la plataforma. */
    virtual void reset() override;

    /** @brief Retorna la textura per a les plataformes que cauen. */
    virtual const std::vector<std::vector<int>>& get_texture() const override;
};

/**
 * @class MovingPlatform
 * @brief Una plataforma que es mou contínuament entre dos punts en un eix.
 */
class MovingPlatform : public Platform {
 public:
    /** @enum Axis @brief Defineix l'eix de moviment de la plataforma. */
    enum class Axis { X, Y };

 private:
    static const std::vector<std::vector<int>> texture_;
    Axis                                       axis_;
    int                                        min_;
    int                                        max_;
    int                                        speed_;

 public:
    MovingPlatform(int  left,
                   int  right,
                   int  top,
                   int  bottom,
                   Axis axis,
                   int  min,
                   int  max,
                   int  speed);

    /** @brief Retorna l'eix de moviment de la plataforma. */
    MovingPlatform::Axis axis() const;

    /** @brief Actualitza la posició de la plataforma segons el seu eix i velocitat. */
    virtual void update() override;

    /** @brief Retorna la textura per a les plataformes mòbils. */
    virtual const std::vector<std::vector<int>>& get_texture() const override;
};

#endif  // PLATFORM_HH