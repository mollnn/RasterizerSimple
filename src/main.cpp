#include <bits/stdc++.h>
#include "common.h"


#include "vec.hpp"
#include "mat.hpp"
#include "color.hpp"
#include "image.hpp"
#include "light.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "renderer.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello" << std::endl;

    int image_size_x = 256;
    int image_size_y = 256;

    point3 camera_pos = {0, 0, 3};
    vec3 camera_gaze = {0, 0, -1};
    vec3 camera_top = {0, 1, 0};
    Camera camera(camera_pos, camera_gaze, camera_top);

    Scene scene;

    scene.face.push_back(Triangle({-1, 0, 0}, {1, 0, 0}, {0, 2, 0}));
    scene.light.push_back(Light({0, 0, 1}, {0.5, 0.5, 0.5}));

    Image image(image_size_x, image_size_y);
    Renderer renderer;
    renderer.Render(scene, camera, image);

    image.WriteToTGA("output.tga");
}