#ifndef __SHADER_HPP__
#define __SHADER_HPP__
#include "common.h"

#include "vec.hpp"
#include "triangle.hpp"
#include "mat.hpp"
#include "light.hpp"
#include "color.hpp"

struct Shader
{
    color3 Shade(const point3 &cam_pos, const Light &light, const Triangle &face, const point3 &hit_pos)
    {
        auto light_pos = light.position;
        vec3 hit_cam_vec = cam_pos - hit_pos;
        vec3 hit_light_vec = light_pos - hit_pos;
        hit_cam_vec.normalize();
        hit_light_vec.normalize();

        vec3 mid_vec = (hit_cam_vec + hit_light_vec) / 2;
        mid_vec.normalize();

        vec3 normal_vec = face.normal;

        if ((normal_vec * hit_cam_vec > 0 && normal_vec * hit_light_vec > 0) || (normal_vec * hit_cam_vec < 0 && normal_vec * hit_light_vec < 0))
        {
            double cos_d = normal_vec * mid_vec;

            auto face_color = face.material.color;
            auto face_shininess = face.material.shininess;

            return face_color * pow(cos_d, face_shininess);
        }
        else
        {
            return {0, 0, 0};
        }
    }
};

#endif