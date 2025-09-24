#ifndef CHOC_ATTRACTION_MATRIX_H_
#define CHOC_ATTRACTION_MATRIX_H_

#include <vector>
#include <stddef.h>
#include <raylib.h>

namespace choco {

class AttractionMatrix {
public:
    // init w/ random values
    AttractionMatrix();
    explicit AttractionMatrix(const std::vector<std::vector<float>>& matrix);

    float getAttraction(const Color& c1, const Color& c2) const;

    static const size_t MATRIX_SIZE = 10;

    static size_t getNForColor(const Color& color);
    static const Color& getColorForN(size_t n);

private:
    std::vector<std::vector<float>> matrix;
};

} // namespace choco

#endif // CHOC_ATTRACTION_MATRIX_H_
