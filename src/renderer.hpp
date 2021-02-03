#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "common.h"

#include "vec.hpp"
#include "mat.hpp"
#include "color.hpp"
#include "image.hpp"
#include "light.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "shader.hpp"

struct Renderer
{
    void Render(const Scene &scene, const Camera &camera, Image &image)
    {
        Image zbuffer(image.size_x, image.size_y);

        // OrthoBox parameters
        double box_n = -1;
        double box_f = -5;
        double box_l = -2;
        double box_r = 2;
        double box_b = -2;
        double box_t = 2;

        // Init zbuffer
        auto Z2C = [&](double x) -> double { return (x + 1) / 2; };
        auto C2Z = [&](double x) -> double { return x * 2 - 1; };
        for (int i = 0; i < image.size_x; i++)
        {
            for (int j = 0; j < image.size_y; j++)
            {
                zbuffer.Set(i, j, color3(0, 0, 0));
            }
        }

        // Copy some basic parameters
        vec3 cam_pos = camera.position;
        vec3 cam_gaze = camera.gaze;
        vec3 cam_top = camera.top;
        vec3 cam_gtc = cross(camera.gaze, camera.top);

        // MVP-View Transform Matrix
        mat<4, 4> mat_t_view = {(vec4){1, 0, 0, -cam_pos.x},
                                {0, 1, 0, -cam_pos.y},
                                {0, 0, 1, -cam_pos.z},
                                {0, 0, 0, 1}};
        mat<4, 4> mat_r_view = {(vec4){cam_gtc.x, cam_gtc.y, cam_gtc.z, 0},
                                {cam_top.x, cam_top.y, cam_top.z, 0},
                                {-cam_gaze.x, -cam_gaze.y, -cam_gaze.z, 0},
                                {0, 0, 0, 1}};
        mat<4, 4> mat_view = mat_r_view * mat_t_view;

        // MVP-Proj Transform Matrix
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

        mat<4, 4> mat_persp_inv = mat_persp.invert();

        // MVP-View+Proj Transform Matrix
        mat<4, 4> mat_vp = mat_persp * mat_view;

        // Rasterization
        for (auto light : scene.light)
        {
            for (auto face : scene.face)
            {
                color3 dbg_color = {rand() * 1. / RAND_MAX, rand() * 1. / RAND_MAX, rand() * 1. / RAND_MAX};

                // Vertex Transform: make face in the ortho space
                for (int i = 0; i < 3; i++)
                {
                    face.p[i] = point_cast(mat_vp * point_cast(face.p[i]));
                }

                // Projected Face: exactly on the near plane
                Triangle projected_face;
                for (int i = 0; i < 3; i++)
                {
                    projected_face.p[i] = face.p[i];
                    projected_face.p[i].z = box_n;
                }

                // For each image pixels
                for (int image_y = 0; image_y < image.size_y; image_y++)
                {
                    for (int image_x = 0; image_x < image.size_x; image_x++)
                    {
                        // Ortho x,y (which will be projected to current pixel)
                        double ortho_x = -1 + (2 * image_x + 1.0) / image.size_x;
                        double ortho_y = -1 + (2 * image_y + 1.0) / image.size_y;

                        point3 proj_p = {ortho_x, ortho_y, box_n};

                        if (projected_face.InTriangle(proj_p))
                        {
                            vec2 P[3] = {{face.p[0].x, face.p[0].y},
                                         {face.p[1].x, face.p[1].y},
                                         {face.p[2].x, face.p[2].y}};
                            vec2 Q = {ortho_x, ortho_y};
                            double area[3] = {abs(cross(P[1] - Q, P[2] - Q)),
                                              abs(cross(P[2] - Q, P[0] - Q)),
                                              abs(cross(P[0] - Q, P[1] - Q))};
                            double total_area = area[0] + area[1] + area[2];
                            double weight[3] = {area[0] / total_area,
                                                area[1] / total_area,
                                                area[2] / total_area};

                            double ortho_z = weight[0] * face.p[0].z +
                                             weight[1] * face.p[1].z +
                                             weight[2] * face.p[2].z;

                            point3 ortho_p = {ortho_x, ortho_y, ortho_z};
                            point3 hit_pos = point_cast(mat_persp_inv * point_cast(ortho_p));

                            if (Z2C(ortho_z) > zbuffer.Get(image_x, image_y).x)
                            {
                                Shader shader;
                                color3 radiance = shader.Shade(cam_pos, light, face, hit_pos);
                                zbuffer.Set(image_x, image_y, color3(Z2C(ortho_z), Z2C(ortho_z), Z2C(ortho_z)));
                                image.Set(image_x, image_y, radiance);
                            }
                        }
                    }
                }
            }
        }

        zbuffer.WriteToTGA("zbuffer.tga");
    }
};

#endif