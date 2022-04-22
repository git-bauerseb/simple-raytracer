#include <cmath>
#include <iostream>
#include <fstream>

#include "../include/vec3.h"
#include "../include/ray.h"
#include "../include/p3.h"

float hit_sphere(const Vec3& center, float radius, const Ray& r) {
    Vec3 ac = r.origin() - center;

    float ac_dot = ac.dot(ac);
    float bb_dot = r.direction().dot(r.direction());
    float bac_dot = r.direction().dot(ac);

    float discr = 4*bac_dot*bac_dot - 4 * bb_dot * (ac_dot - radius*radius);
    
    if (discr < 0) {
        return -1.0;
    } else {
        // Closest hit point (smallest value of t for solving quadratic equation)
        return (- 2 * bac_dot - std::sqrt(discr) ) / (2 * bb_dot); 
    }
}

Vec3 ray_color(const Ray& ray) {
    float t;

    if ((t = hit_sphere(Vec3{0, 0, -1}, 0.5, ray)) > 0.0) {
        Vec3  normal = unit_vector(ray.at(t) - Vec3{0, 0, -1});
        return 0.5 * (normal + 1);
    }

    Vec3 unit_dir = unit_vector(ray.direction());
    t = 0.5 * (unit_dir[1] + 1.0);
    return (1.0 - t) * Vec3(1., 1., 1.) + t * Vec3{0., 0., 0.};
}

int main(int argc, char** argv) {

    std::ofstream myfile;
    myfile.open(argv[1]);

    int img_width = 256;
    int img_height = 256;

    float viewport_height = 2.0;
    float viewport_width = 2.0;

    float focal_length = 1.0;

    Vec3 ray_origin = Vec3{0, 0, 0};
    Vec3 horizontal{viewport_width, 0, 0};
    Vec3 vertical = Vec3{0, viewport_height, 0};

    Vec3 lower_left = ray_origin - horizontal / 2 - vertical / 2 - Vec3{0, 0, focal_length};

    P3 p3{img_width,img_height};
    p3.write_header(myfile);

    for (int j = img_height - 1; j >= 0; j--) {
        for (int i = 0; i < img_width; i++) {
            auto u = float{i} / (img_width-1);
            auto v = float{j} / (img_height-1);
            
            Ray ray{ray_origin, lower_left + u * horizontal + v * vertical - ray_origin};
            Vec3 color = ray_color(ray);
            write_color(myfile, color);
        }
    }


    myfile.close();

    return 0;
}
