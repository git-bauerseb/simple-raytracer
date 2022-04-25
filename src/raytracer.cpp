#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

#include "../include/misc.h"
#include "../include/raytracer.h"
#include "../include/camera.h"

TraceableList l;

Vec3 ray_color(const Ray& ray, int depth = 1) {
    Hit hit;

    if (depth <= 0) {
        return Vec3(0,0,0);
    }
    
    if (l.hit(ray, 0, infity, hit)) {
        Vec3 target = hit.position + hit.normal + Vec3::random_in_unit_sphere();
        return 0.5 * ray_color(Ray{hit.position, target - hit.position}, depth-1);
    }

    Vec3 unit_dir = unit_vector(ray.direction());
    float t = 0.5 * (unit_dir[1] + 1.0);
    return (1.0 - t) * Vec3(1., 1., 1.) + t * Vec3{0.5, 0.7, 1.0};
}

int main(int argc, char** argv) {

    std::ofstream myfile;
    myfile.open(argv[1]);

    // SETUP
    int img_width = 258;
    int img_height = 258;
    int samples_per_pixel = 20;
    int max_depth = 50;

   
    // World
    l.add(std::make_shared<Sphere>(Vec3{0, 0, -1}, 0.5f));
    l.add(std::make_shared<Sphere>(Vec3{0, -100.5f, -1}, 100.0f));

    // Camera
    Camera cam;

    // RENDERING
    P3 p3{img_width,img_height};
    p3.write_header(myfile);


    for (int j = img_height - 1; j >= 0; j--) {
        // std::cout << "Rendering line " << j << "\n";
        for (int i = 0; i < img_width; i++) {
            
            Vec3 color;
            
            for (int iter = 0; iter < samples_per_pixel; iter++) {
                auto u = float{i + random_float()} / (img_width-1);
                auto v = float{j + random_float()} / (img_height-1);
                Ray r = cam.get_ray(u, v);            

                color += ray_color(r, max_depth);
            }

            write_color(myfile, color, samples_per_pixel);
        }
    }


    myfile.close();

    return 0;
}
