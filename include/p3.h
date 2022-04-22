#ifndef P3_H
#define P3_H

#include <vector>
#include <iostream>

#include "vec3.h"

class P3 {

    public:
        P3(int width, int height) : m_width{width}, m_height{height} {}
        void setBuffer(std::vector<Vec3> buffer);

        void write_image(std::ostream& outfile, bool progress=false);
        void write_header(std::ostream& outfile) const;

    private:
        std::vector<Vec3> m_buffer;
        int m_width;
        int m_height;

};


#endif