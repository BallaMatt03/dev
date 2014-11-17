#ifndef POLYGONE_HPP_INCLUDED
#define POLYGONE_HPP_INCLUDED

#include <vector>
#include "coord.hpp"

template<typename Type>
using polygone = std::vector<pointND<Type>>;

template<typename Type, int Index>
struct coord<polygone<Type>,Index>
{
  using type = Type;
};

#endif
