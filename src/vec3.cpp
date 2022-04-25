#include "../include/vec3.h"

void write_color(std::ostream& outfile, const Vec3& color, int samples) {
    float r = color[0];
    float g = color[1];
    float b = color[2];

    float scale = 1.0 / samples;

    r *= scale;
    g *= scale;
    b *= scale;

    outfile << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << ' ';
}