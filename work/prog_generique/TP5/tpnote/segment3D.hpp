#ifndef SEGMENT3D_HPP_INCLUDED
#define SEGMENT3D_HPP_INCLUDED

#include <array>
#include "point3D.hpp"

template<typename Type>
using segment3D = std::array<point3D<Type>,2>;

template<typename Type, int Index>
struct coord<segment3D<point3D<Type>>,Index>
{
  using type = Type;
};

#endif