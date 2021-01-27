#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "vec.hpp"

struct Camera
{
    point3 position;
    vec3 gaze;
    vec3 top;

    Camera(point3 p, vec3 g, vec3 t) : position(p), gaze(g), top(t)
    {
    }
};

#endif