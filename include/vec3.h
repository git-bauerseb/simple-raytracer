#ifndef VEC_3_H
#define VEC_3_H

#include <cmath>
#include <iostream>
#include <fstream>

#include "misc.h"

class Vec3 {

    public:
        Vec3() : m_coords{0, 0, 0} {}
        Vec3(float x, float y, float z) : m_coords{x, y, z} {}

        float dot(const Vec3& other) const {
            return m_coords[0] * other.m_coords[0] +
                m_coords[1] * other.m_coords[1] +
                m_coords[2] * other.m_coords[2];
        }

        Vec3 operator-() const {
            return Vec3{-m_coords[0], -m_coords[1], -m_coords[2]};
        }

        Vec3& operator+=(const Vec3& other) {
            m_coords[0] += other.m_coords[0];
            m_coords[1] += other.m_coords[1];
            m_coords[2] += other.m_coords[2];
            
            return *this;
        }

        Vec3& operator*=(const Vec3& other) {
            m_coords[0] *= other.m_coords[0];
            m_coords[1] *= other.m_coords[1];
            m_coords[2] *= other.m_coords[2];
            
            return *this;
        }

        Vec3& operator*=(const float c) {
            m_coords[0] *= c;
            m_coords[1] *= c;
            m_coords[2] *= c;

            return *this;
        }

        float operator[](int idx) const {
            return m_coords[idx];
        }

        float length() const {
            return std::sqrt(m_coords[0] * m_coords[0] 
                            + m_coords[1] * m_coords[1]
                            + m_coords[2] * m_coords[2]);
        }

        Vec3 operator-() {return Vec3{-m_coords[0], -m_coords[1], -m_coords[2]};}

        Vec3 static random() {
            return Vec3{random_float(), random_float(), random_float()};
        }

        Vec3 static random(float min, float max) {
            return Vec3{random_float(min, max), random_float(min, max), random_float(min, max)};
        }

        Vec3 static random_in_unit_sphere() {
            while (true) {
                Vec3 p = Vec3::random(-1, 1);

                if (p.length() >= 1) {continue;}
                return p;
            }
        }

    private:
        float m_coords[3];
};

inline Vec3 operator+(const Vec3& left, const Vec3& right) {
    return Vec3{left[0] + right[0], left[1] + right[1], left[2] + right[2]};
}

inline Vec3 operator+(float f, const Vec3& right) {
    return Vec3{f + right[0], f + right[1], f + right[2]};
}

inline Vec3 operator+(const Vec3& left, float f) {
    return Vec3{f + left[0], f + left[1], f + left[2]};
}

inline Vec3 operator-(const Vec3& left, const Vec3& right) {
    return Vec3{left[0] - right[0], left[1] - right[1], left[2] - right[2]};
}


inline Vec3 operator*(const float c, const Vec3& right) {
    return Vec3{c * right[0], c * right[1], c * right[2]};
}

inline Vec3 operator/(const Vec3& right, const float f) {
    return Vec3{right[0] / f, right[1] / f, right[2] / f};
}

inline Vec3 unit_vector(const Vec3& original) {
    return original / original.length();
}

inline std::ostream& operator<<(std::ostream& outfile, const Vec3& color) {
    return outfile << color[0] << " " << color[1] << " " << color[2] << " ";
}

/*
    Other functions
*/
void write_color(std::ostream& outfile, const Vec3& color, int samples);
#endif