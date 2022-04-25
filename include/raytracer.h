#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <cmath>
#include <memory>

#include "vec3.h"
#include "ray.h"
#include "p3.h"

struct Hit {
    Vec3 position;
    Vec3 normal;
    float t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = r.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

/*
    Represents an render object which can be hit 
    by a ray of the raycaster
*/
class Traceable {
    public:
        virtual bool hit(const Ray& r, float t_min, float t_max, Hit& hit_info) const =0;
};

class TraceableList : public Traceable {
    public:
        TraceableList() {}
        TraceableList(std::shared_ptr<Traceable> object) {
            add(object);
        }

        void add(std::shared_ptr<Traceable> obj) {
            objects.push_back(obj);
        }

        virtual bool hit(const Ray& r, float t_min, float t_max, Hit& hit_info) const override;

    public:
        std::vector<std::shared_ptr<Traceable>> objects;
};

bool TraceableList::hit(const Ray& r, float t_min, float t_max, Hit& hit_info) const {
    Hit rec;
    bool hit_any = false;
    auto closest = t_max;

    for (const std::shared_ptr<Traceable>& obj : objects) {
        if (obj->hit(r, t_min, closest, rec)) {
            hit_any = true;
            closest = rec.t;
            hit_info = rec;
        }
    }

    return hit_any;
}

class Sphere : public Traceable {
    public:
        Sphere() : m_center{0, 0, 0}, m_radius{1} {}
        Sphere(Vec3 center, float radius) : m_center{center}, m_radius{radius} {}

        virtual bool hit(const Ray& r, float t_min, float t_max, Hit& hit_info) const override {
            Vec3 ac = r.origin() - m_center;

            float a = r.direction().length() * r.direction().length();
            float half_b = ac.dot(r.direction());
            float c = ac.length() * ac.length() - m_radius*m_radius;

            float discr = half_b * half_b - a * c;
            
            if (discr < 0) {
                return false;
            }

            float root = (-half_b - std::sqrt(discr)) / a;

            if (root < t_min || root > t_max) {
                root = (-half_b - std::sqrt(discr)) / a;

                if (root < t_min || root > t_max) {
                    return false;
                }
            }

            hit_info.t = root;
            hit_info.position = r.at(root);
            Vec3 normal = (hit_info.position - m_center) / m_radius;
            hit_info.set_face_normal(r, normal);

            return true;
    }

    private:
        Vec3 m_center;
        float m_radius;
};

#endif