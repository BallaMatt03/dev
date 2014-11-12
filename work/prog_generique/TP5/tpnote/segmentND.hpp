#ifndef SEGMENTND_HPP_INCLUDED
#define SEGMENTND_HPP_INCLUDED

#include <array>
#include "pointND.hpp"

template<typename Type>
using segmentND = std::array<pointND<Type>,2>;

template<typename Type, int Index>
struct coord<segmentND<pointND<Type>>,Index>
{
  using type = Type;
};

#endif