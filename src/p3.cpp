#include "../include/p3.h"

void P3::setBuffer(std::vector<Vec3> buffer) {
    if (buffer.size() != m_width * m_height) {
        std::cerr << "Invalid buffersize: " << buffer.size() << "\n";
        std::exit(1);
    }

    m_buffer = buffer;
}
 
void P3::write_image(std::ostream& outfile, bool progress) {
    // Header
    outfile << "P3\n" << m_width << " " << m_height << "\n255\n";

    int idx = 0;
    int line = 0;

    for(Vec3& c : m_buffer) {
        int int_r = static_cast<int>(255.9 * c[0]);
        int int_g = static_cast<int>(255.9 * c[1]);
        int int_b = static_cast<int>(255.9 * c[2]);

        outfile << int_r << " " << int_g << " " << int_b << " ";

        if (idx == (m_width-1)) {

            if (progress) {
                std::cout << "Rendered line " << line << " from " << m_height << "\n";
            }

            outfile << "\n";

            idx = 0;
            line++;
            continue;
        }

        idx++;
    }
}

void P3::write_header(std::ostream& outfile) const {
    // Header
    outfile << "P3\n" << m_width << " " << m_height << "\n255\n";
}

