#include <raylib.h>
#include <vector>
#include <unordered_map>

#include "chocodefs.h"
#include "particle.h"

int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    std::vector<choco::Particle> particles;

    int numParticles = 1000;
    int particleTypeCount = 7;

    std::shared_ptr<choco::AttractionMatrix> attrMatrix = std::make_shared<choco::AttractionMatrix>();
    int currentParticleType = 0;
    for (int i = 0; i < numParticles; i++) {
        choco::Vector2 randomPos(getRandomInt(0, X_MAX), getRandomInt(0, Y_MAX));

        Color color = choco::AttractionMatrix::getColorForN(currentParticleType);
        particles.push_back(choco::Particle(randomPos, color, attrMatrix));

        if (++currentParticleType == particleTypeCount) {
            currentParticleType = 0;
        }
    }
    
    InitWindow(X_MAX, Y_MAX, "Evolving Particles");
    SetTargetFPS(60);

    std::unordered_map<choco::Particle*, choco::Vector2> accels(particles.size());
    
    while (!WindowShouldClose()) {
        static const float FRAME_TIME = 1/300.f;
        static const float DEPTH = 1;

        for (int i = 0; i < DEPTH; i++) {
            // Updates
            for (choco::Particle& particle : particles) {
                accels[&particle] = particle.getNetAccelOnMe(particles);
            }

            for (const auto& pair : accels) {
                pair.first->update(pair.second, FRAME_TIME);
            }
            accels.clear();
        }

        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        for (const choco::Particle& particle : particles) {
            const choco::Vector2& pos = particle.getPos();
            DrawCircle(pos.x, pos.y, PARTICLE_RAD, particle.getColor());
        }
        EndDrawing();
    }
    
    CloseWindow();
}
