#include "particle.h"

#include "util.h"
#include "chocodefs.h"

#include <iostream>

namespace choco {


void reverseWallVector(const Vector2& pos, Vector2& vec, float factor = 1);


// Returns value 0-1 expressing proximity of colours (0 for same colour, 1 for white vs black)
float colorProximity(const Color& c1, const Color& c2);

static const float PARTICLE_PROCESSING_DIST = 120.f;

static const float DENSITY_EFFECT_DIST = 40.f; // 33.333
static const float MAX_PRESSURE_ACCEL = 5000.0f;

static const float MAX_ATTRACTION_ACCEL = 5000.0f;

static const float MAX_VELOCITY = 5000.f;
static const float MAX_ACCEL = 250000.f;

static const float STACKED_PARTICLE_ACCEL = 10000.0f;

static const float NOPRESSURE_PROCESSING_DIST = PARTICLE_PROCESSING_DIST - DENSITY_EFFECT_DIST;

Particle::Particle(const Vector2& pos, const Color& color) : pos(pos), vel(Vector2::Zero), color(color), attractionMatrix(std::make_shared<AttractionMatrix>()) {
}

Particle::Particle(
    const Vector2& pos,
    const Color& color,
    const std::shared_ptr<AttractionMatrix>& attrMatrix)
    : pos(pos),
      vel(Vector2::Zero),
      color(color),
      attractionMatrix(attrMatrix) {
}


void Particle::update(const Vector2& netAccelOnMe, float tStep) {
    vel += tStep * netAccelOnMe;
    vel.x = clamp(vel.x, -MAX_VELOCITY, MAX_VELOCITY);
    vel.y = clamp(vel.y, -MAX_VELOCITY, MAX_VELOCITY);

    vel *= pow(.6, 60 * tStep); // Friction

    pos += tStep * vel;
    pos.x = clamp(pos.x, 0.f + PARTICLE_RAD, X_MAX - PARTICLE_RAD);
    pos.y = clamp(pos.y, 0.f + PARTICLE_RAD, Y_MAX - PARTICLE_RAD);

    static const float BOUNCE_FACTOR = 1;

    reverseWallVector(pos, vel, BOUNCE_FACTOR);
}

Vector2 Particle::getNetAccelOnMe(const std::vector<Particle>& particles) const {
    Vector2 netAccel = Vector2(0, 0);
    
    for (const Particle& other : particles) {
        Vector2 v = other.pos - pos;
        if (v.magnitude_squared() > PARTICLE_PROCESSING_DIST * PARTICLE_PROCESSING_DIST) continue; // skip far particles
        Vector2 norm = Vector2(v);
        norm.normalize();
        float dist = v.magnitude();

        if (pos == other.pos) {
            netAccel += getRandomNormVector() * STACKED_PARTICLE_ACCEL;
        }

        // stacked particles should just get sent in a random direction
        if (dist > DENSITY_EFFECT_DIST) {
            float attraction = attractionMatrix->getAttraction(color, other.color);

            float mid = (DENSITY_EFFECT_DIST + PARTICLE_PROCESSING_DIST) / 2;
            float slope = attraction / (mid - DENSITY_EFFECT_DIST);
            netAccel += (-(slope * std::abs(dist - mid)) + attraction) * MAX_ATTRACTION_ACCEL * norm;
        } else { // within density
            netAccel += ((MAX_PRESSURE_ACCEL / DENSITY_EFFECT_DIST) * dist - MAX_PRESSURE_ACCEL) * norm;
        }
    }

    float netAccelMag = netAccel.magnitude();
    netAccel.normalize();

    netAccel *= clamp(netAccelMag, 0.f, MAX_ACCEL);
    reverseWallVector(pos, netAccel, 1);

    return netAccel;
}

const Color& Particle::getColor() const { return color; }
const Vector2& Particle::getPos() const { return pos; }


void reverseWallVector(const Vector2& pos, Vector2& vec, float factor) {
    if (pos.x <= 0 + PARTICLE_RAD && vec.x < 0) vec.x = factor * -vec.x;
    if (pos.x >= X_MAX - PARTICLE_RAD && vec.x > 0) vec.x = factor * -vec.x;
    if (pos.y <= 0 + PARTICLE_RAD && vec.y < 0) vec.y = factor * -vec.y;
    if (pos.y >= Y_MAX - PARTICLE_RAD && vec.y > 0) vec.y = factor * -vec.y;
}


} // namespace choco
