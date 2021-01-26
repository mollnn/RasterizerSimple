#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include <cmath>
#include <cassert>
#include <iostream>

#include "color.hpp"

struct Material
{
    color3 color;

    Material(color3 color = {0.5, 0.5, 0.5}) : color(color)
    {
    }
};

#endif