#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "vec.hpp"
#include "mat.hpp"
#include "color.hpp"
#include "image.hpp"
#include "light.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "camera.hpp"

struct Renderer
{
    void Render(const Scene &scene, const Camera &camera, Image &image)
    {
        vec3 cam_pos = camera.position;
        vec3 cam_gaze = camera.gaze;
        vec3 cam_top = camera.top;
        vec3 cam_gtc = cross(camera.gaze, camera.top);

        mat<4, 4> mat_t_view = {(vec4){1, 0, 0, -cam_pos.x},
                                {0, 1, 0, -cam_pos.y},
                                {0, 0, 1, -cam_pos.z},
                                {0, 0, 0, 1}};
        mat<4, 4> mat_r_view = {(vec4){cam_gtc.x, cam_gtc.y, cam_gtc.z, 0},
                                {cam_top.x, cam_top.y, cam_top.z, 0},
                                {-cam_gaze.x, -cam_gaze.y, -cam_gaze.z, 0},
                                {0, 0, 0, 1}};
        mat<4, 4> mat_view = mat_r_view * mat_t_view;

        double box_n = 0;
        double box_f = -5;
        double box_l = -2;
        double box_r = 2;
        double box_b = -2;
        double box_t = 2;

        mat<4, 4> mat_ortho_scale = {(vec4){2 / (box_r - box_l), 0, 0, 0},
                                     {0, 2 / (box_t - box_b), 0, 0},
                                     {0, 0, 2 / (box_n - box_f), 0},
                                     {0, 0, 0, 1}};
        mat<4, 4> mat_ortho_shift = {(vec4){1, 0, 0, -(box_r + box_l) / 2},
                                     {0, 1, 0, -(box_t + box_b) / 2},
                                     {0, 0, 1, -(box_n + box_f) / 2},
                                     {0, 0, 0, 1}};

        mat<4, 4> mat_persp2ortho = {(vec4){box_n, 0, 0, 0},
                                     {0, box_n, 0, 0},
                                     {0, 0, box_n + box_f, -box_n * box_f},
                                     {0, 0, 1, 0}};

        mat<4, 4> mat_ortho = mat_ortho_scale * mat_ortho_shift;
        mat<4, 4> mat_persp = mat_ortho * mat_persp2ortho;

        // continue!
    }
};

#endif