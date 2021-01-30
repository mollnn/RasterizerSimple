#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "common.h"

#include <vector>

#include "triangle.hpp"
#include "light.hpp"

struct Scene
{
    std::vector<Triangle> face;
    std::vector<Light> light;
};

#endif