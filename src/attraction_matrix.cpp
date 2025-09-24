#include "attraction_matrix.h"

#include <algorithm>
#include <random>

#include <iostream>

#include "util.h"

namespace choco {


static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

static const Color colorNs[] = {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    MAGENTA,
    PINK,
    DARKBLUE,
    SKYBLUE
};

AttractionMatrix::AttractionMatrix() : matrix(MATRIX_SIZE) {
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = std::vector<float>(MATRIX_SIZE);
        for (size_t j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = dis(gen);
        }
    }
}

AttractionMatrix::AttractionMatrix(const std::vector<std::vector<float>>& matrix) : matrix(matrix) {}

float AttractionMatrix::getAttraction(const Color& c1, const Color& c2) const {
    return matrix[getNForColor(c1)][getNForColor(c2)];
}


size_t AttractionMatrix::getNForColor(const Color& c) {
    size_t leastColorIndex = 0;
    float leastColorProximity = 0;

    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        const Color& baseC = colorNs[i];

        float prox = colorProximity(c, baseC);

        if (prox > leastColorProximity) {
            leastColorProximity = prox;
            leastColorIndex = i;

            if (leastColorProximity == 1) break;
        }
    }

    return leastColorIndex;
}

const Color& AttractionMatrix::getColorForN(size_t n) {
    if (n >= MATRIX_SIZE) throw std::invalid_argument("n (" + std::to_string(n) + ") > MATRIX_SIZE");
    return colorNs[n];
}


} // namespace choco

