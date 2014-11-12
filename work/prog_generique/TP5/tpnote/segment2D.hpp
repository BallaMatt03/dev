#ifndef SEGMENT2D_HPP_INCLUDED
#define SEGMENT2D_HPP_INCLUDED

#include <array>
#include "point2D.hpp"

template<typename Type>
using segment2D = std::array<point2D<Type>,2>;

/*
template<typename Type>
struct segment2D
{
	public:
		std::array<point2D<Type>, 2> lesPoints;
};
*/
template<typename Type, int Index>
struct coord<segment2D<Type>,Index>
{
  using type = Type;
};

#endif