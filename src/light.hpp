#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__


#include "vec.hpp"
#include "color.hpp"


struct Light 
{
    point3 position;
    color3 color;
};

#endif