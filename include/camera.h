#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera {

    public:
        Camera() {
            float aspect_ratio = 1.0;
            float viewport_height = 2.0;
            float viewport_width = aspect_ratio * viewport_height;
            float focal_length = 1.0;

            origin = Vec3{0, 0, 0};
            horizontal = Vec3{viewport_width, 0, 0};
            vertical = Vec3{0, viewport_height, 0};
            lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3{0, 0, focal_length};
        }

        Ray get_ray(float u, float v) const {
            return Ray{origin, lower_left_corner + u * horizontal + v*vertical - origin};
        }


    private:
        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};

#endif