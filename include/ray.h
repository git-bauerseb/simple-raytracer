#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Ray(Vec3 origin, Vec3 dir) : m_origin{origin}, m_direction{dir} {}
        Vec3 at(float t) const {
            return m_origin + t*m_direction;
        }

        Vec3 direction() const {return m_direction;}
        Vec3 origin() const {return m_origin;}

    private:
        Vec3 m_origin;
        Vec3 m_direction;
};

#endif