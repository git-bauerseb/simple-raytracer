#include "../include/vec3.h"

void write_color(std::ostream& outfile, const Vec3& color) {
    outfile << static_cast<int>(255.9 * color[0]) << " " 
            << static_cast<int>(255.9 * color[1]) << " "
            << static_cast<int>(255.9 * color[2]) << " ";
}