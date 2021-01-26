#include <bits/stdc++.h>

#include "vec.hpp"
#include "mat.hpp"
#include "color.hpp"
#include "image.hpp"
#include "light.hpp"
#include "material.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello" << std::endl;

    // A test to gen TGA image
    TGAImage image(200, 200, 3);

    for (int i = 0; i < 200; i++)
        for (int j = 0; j < 200; j++)
        {
            image.set(i, j, color3(i * 0.005, j * 0.005, 0));
        }

    image.flip_vertically();

    image.write_tga_file("output.tga");
}