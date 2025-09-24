#ifndef CHOC_PARTICLE_H_
#define CHOC_PARTICLE_H_

#include <vector>
#include <memory>
#include <raylib.h>

#include "vec2.h"
#include "attraction_matrix.h"

namespace choco {


class Particle {
public:
    Particle(const Vector2& pos, const Color& color);
    Particle(const Vector2& pos, const Color& color, const std::shared_ptr<AttractionMatrix>& attrMatrix);

    void update(const Vector2& netForceOnMe, float tStep);
    Vector2 getNetAccelOnMe(const std::vector<Particle>& particles) const;

    const Color& getColor() const;
    const Vector2& getPos() const;

private:
    Vector2 pos;
    Vector2 vel;

    const Color color;

    std::shared_ptr<AttractionMatrix> attractionMatrix;
};

} // namespace choco

#endif // CHOC_PARTICLE_H_
