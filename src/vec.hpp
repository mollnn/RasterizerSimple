#ifndef __VEC_HPP__
#define __VEC_HPP__

#include <cmath>
#include <cassert>
#include <iostream>

///////////////////////////////////////////////////////
// n-dim. vector
///////////////////////////////////////////////////////

template <int n>
struct vec
{
    vec() = default;
    double &operator[](const int i)
    {
        assert(i >= 0 && i < n);
        return data[i];
    }
    double operator[](const int i) const
    {
        assert(i >= 0 && i < n);
        return data[i];
    }
    double norm2() const
    {
        return (*this) * (*this);
    }
    double norm() const
    {
        return std::sqrt(norm2());
    }
    vec &normalize()
    {
        *this = (*this) / norm();
        return *this;
    }
    vec normal() const
    {
        auto t = *this;
        t = t / norm();
        return t;
    }
    double data[n] = {0};
};

template <int n>
double operator*(const vec<n> &lhs, const vec<n> &rhs)
{
    double ret = 0;
    for (int i = n; i--; ret += lhs[i] * rhs[i])
        ;
    return ret;
}

template <int n>
vec<n> operator+(const vec<n> &lhs, const vec<n> &rhs)
{
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] += rhs[i])
        ;
    return ret;
}

template <int n>
vec<n> operator-(const vec<n> &lhs, const vec<n> &rhs)
{
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] -= rhs[i])
        ;
    return ret;
}

template <int n>
vec<n> operator*(const double &rhs, const vec<n> &lhs)
{
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] *= rhs)
        ;
    return ret;
}

template <int n>
vec<n> operator*(const vec<n> &lhs, const double &rhs)
{
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] *= rhs)
        ;
    return ret;
}

template <int n>
vec<n> operator/(const vec<n> &lhs, const double &rhs)
{
    vec<n> ret = lhs;
    for (int i = n; i--; ret[i] /= rhs)
        ;
    return ret;
}

template <int n>
std::ostream &operator<<(std::ostream &os, const vec<n> &v)
{
    os << "(";
    for (int i = 0; i < n; i++)
        os << v[i] << ",";
    os << ")";
    return os;
}

///////////////////////////////////////////////////////
// 2d vector
///////////////////////////////////////////////////////

template <>
struct vec<2>
{
    vec() = default;
    vec(double X, double Y) : x(X), y(Y) {}
    double &operator[](const int i)
    {
        assert(i >= 0 && i < 2);
        return i == 0 ? x : y;
    }
    double operator[](const int i) const
    {
        assert(i >= 0 && i < 2);
        return i == 0 ? x : y;
    }
    double norm2() const
    {
        return (*this) * (*this);
    }
    double norm() const
    {
        return std::sqrt(norm2());
    }
    vec &normalize()
    {
        *this = (*this) / norm();
        return *this;
    }
    vec normal() const
    {
        auto t = *this;
        t = t / norm();
        return t;
    }
    double x{}, y{};
};

///////////////////////////////////////////////////////
// 3d vector
///////////////////////////////////////////////////////

template <>
struct vec<3>
{
    vec() = default;
    vec(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    double &operator[](const int i)
    {
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (1 == i ? y : z);
    }
    double operator[](const int i) const
    {
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (1 == i ? y : z);
    }
    double norm2() const
    {
        return (*this) * (*this);
    }
    double norm() const
    {
        return std::sqrt(norm2());
    }
    vec &normalize()
    {
        *this = (*this) / norm();
        return *this;
    }
    vec normalize() const
    {
        auto t = *this;
        t = t / norm();
        return t;
    }

    double x{}, y{}, z{};
};

typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

vec3 cross(const vec3 &v1, const vec3 &v2)
{
    return vec<3>{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

#endif