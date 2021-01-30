#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include <cmath>
#include <cassert>
#include <iostream>

#include "vec.hpp"
#include "mat.hpp"
#include "material.hpp"

#define dbg(x) std::cerr << #x << "=" << x << "; ";

struct Triangle
{
    point3 p[3];
    vec3 normal;
    Material material;

    Triangle()
    {
    }

    Triangle(point3 p0, point3 p1, point3 p2, Material material = Material())
        : material(material)
    {
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
        this->AutoNormal();
        material.color = {0.5, 0.5, 0.5};
    }

    vec3 AutoNormal()
    {
        normal = cross(p[1] - p[0], p[2] - p[0]);
        normal.normalize();
        return normal;
    }

    bool OnPlane(point3 q)
    {
        return fabs(normal * (q - p[0])) < 1e-6;
    }

    bool InTriangle(point3 q)
    {
        // dbg(p[0]);
        // dbg(p[1]);
        // dbg(p[2]);
        // dbg(q);
        // std::cerr << std::endl;
        
        if (!OnPlane(q))
            return false;
        vec3 v[3];
        for (int i = 0; i < 3; i++)
        {
            point3 a = p[i];
            point3 b = p[(i + 1) % 3];
            point3 c = q;
            v[i] = cross(b - a, c - a);
        }
        double t1 = v[0] * v[1], t2 = v[0] * v[2], t3 = v[1] * v[2];
        return t1 >= 0 && t2 >= 0 && t3 >= 0;
    }
};

#endif