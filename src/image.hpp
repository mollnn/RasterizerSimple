#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <vector>
#include "color.hpp"

#include "tgaimage.hpp"

struct Image
{
    int size_x;
    int size_y;

    std::vector<std::vector<color3>> buffer;

    void reallocate()
    {
        buffer.clear();
        buffer.resize(size_y);
        for (int i = 0; i < size_y; i++)
            buffer[i].resize(size_x);
    }

    Image(int sx = 0, int sy = 0) : size_x(sx), size_y(sy)
    {
        this->reallocate();
    }

    
};

#endif