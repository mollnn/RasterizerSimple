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
    void Render(const Scene &scene, const Camera& camera, TGAImage& image)
    {
        
    }
};

#endif