/*
 * vec2.h
 *
 *  Created on: Dec 12, 2011
 *      Author: kyle
 *  Modified on: Sep 21, 2025
 *      Author: chococaker
 */

#ifndef CHOC_VECTOR2_H_
#define CHOC_VECTOR2_H_

#include <cmath>
#include <iostream>
#include <string>

namespace choco {

class Vector2 {
public:
    float x;
    float y;

    Vector2();
    explicit Vector2(float x, float y);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const Vector2& other);
    Vector2& operator/=(const Vector2& other);

    Vector2 operator-() const;

    Vector2 operator+(float scalar) const;
    Vector2 operator-(float scalar) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    Vector2& operator+=(float scalar);
    Vector2& operator-=(float scalar);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    static const Vector2 Zero;
    static const Vector2 One;

    [[nodiscard]] float magnitude() const;
    [[nodiscard]] float magnitude_squared() const;
    void normalize();
    [[nodiscard]] Vector2 normalized() const;
    [[nodiscard]] float dot(const Vector2& other) const;
    [[nodiscard]] float cross(const Vector2& other) const;
    void truncate(float max_length);
    [[nodiscard]] Vector2 perpendicular() const;
    [[nodiscard]] int sign(const Vector2& other) const;
    [[nodiscard]] Vector2 reflect(const Vector2& normal) const;
};

inline Vector2::Vector2() : x(0.0f), y(0.0f) {}
inline Vector2::Vector2(float new_x, float new_y) : x(new_x), y(new_y) {}

inline Vector2 Vector2::operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
inline Vector2 Vector2::operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
inline Vector2 Vector2::operator*(const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
inline Vector2 Vector2::operator/(const Vector2& other) const { return Vector2(x / other.x, y / other.y); }

inline Vector2& Vector2::operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
inline Vector2& Vector2::operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
inline Vector2& Vector2::operator*=(const Vector2& other) { x *= other.x; y *= other.y; return *this; }
inline Vector2& Vector2::operator/=(const Vector2& other) { x /= other.x; y /= other.y; return *this; }

inline Vector2 Vector2::operator-() const { return Vector2(-x, -y); }

inline Vector2 Vector2::operator+(float scalar) const { return Vector2(x + scalar, y + scalar); }
inline Vector2 Vector2::operator-(float scalar) const { return Vector2(x - scalar, y - scalar); }
inline Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
inline Vector2 Vector2::operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }

inline Vector2& Vector2::operator+=(float scalar) { x += scalar; y += scalar; return *this; }
inline Vector2& Vector2::operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
inline Vector2& Vector2::operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
inline Vector2& Vector2::operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

const float EPSILON = 0.000001f;
inline bool Vector2::operator==(const Vector2& other) const { return std::fabs(x - other.x) < EPSILON && std::fabs(y - other.y) < EPSILON; }
inline bool Vector2::operator!=(const Vector2& other) const { return !(*this == other); }

inline std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
    return os << "X: " << vector.x << ", Y: " << vector.y;
}

inline Vector2 operator*(float scalar, const Vector2& vector) {
    return Vector2(scalar * vector.x, scalar * vector.y);
}

inline float Vector2::dot(const Vector2& other) const { return x * other.x + y * other.y; }
inline float Vector2::magnitude_squared() const { return dot(*this); }
inline float Vector2::magnitude() const { return std::sqrt(magnitude_squared()); }
inline Vector2 Vector2::normalized() const {
    float mag = magnitude();
    return (mag > EPSILON) ? *this / mag : Vector2::Zero;
}

inline void Vector2::normalize() {
    float mag = magnitude();
    if (mag > EPSILON) {
        *this /= mag;
    }
}

inline float Vector2::cross(const Vector2& other) const {
    return x * other.y - y * other.x;
}

inline Vector2 Vector2::perpendicular() const {
    return Vector2(-y, x);
}

inline int Vector2::sign(const Vector2& other) const {
    float cross_product = cross(other);
    return (cross_product > 0) ? 1 : ((cross_product < 0) ? -1 : 0);
}

inline void Vector2::truncate(float max_length) {
    if (magnitude_squared() > max_length * max_length) {
        *this = normalized() * max_length;
    }
}

inline Vector2 Vector2::reflect(const Vector2& normal) const {
    return *this - (2.0f * dot(normal) * normal);
}

} // namespace choco

#endif // CHOC_VECTOR2_H_
