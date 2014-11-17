#ifndef PERIMETRE_HPP_INCLUDED
#define PERIMETRE_HPP_INCLUDED

#include "distance.hpp"
#include "polygone.hpp"

template <typename T>
double perimetre(polygone<T> const& p)
{
	double r{0};
	auto siz = p.size();
    for(std::size_t i=0;i<siz-1;++i)
    {
    	r += sfinae::distance(p.at(i), p.at(i+1));
    }
    r += sfinae::distance(p.back(), p.front());

    return r;
}

#endif