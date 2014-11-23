#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include "at.hpp"
#include "size.hpp"
#include "point2D.hpp"
#include "point3D.hpp"
#include "pointND.hpp"
#include "segment2D.hpp"
#include "segment3D.hpp"
#include "segmentND.hpp"
#include <cmath>
#include <numeric>
#include <boost/type_traits/is_same.hpp>

/*
//Distance entre deux points
template<typename P1, typename P2>
double distance(P1 const& p1, P2 const& p2)
{
  double r{0};
  auto s = std::max(size(p1),size(p2));

  for(std::size_t i=0;i<s;++i)
  {
    auto d = at(p1,i) - at(p2,i);
    r += d*d;
  }

  return std::sqrt(r);
}
*/

//Définir la structure enable_if comme vu en cours
template<bool, typename T = void> 
  struct enable_if {};

template<typename T>
  struct enable_if<true, T> {
    typedef T type;
  };

//Dans un namespace objets définir les structures is_point.. et is_segment.. en utilisant boost::is_same 
namespace objets
{
  template<typename T, typename TypePrimitif>
    struct is_point2D   : boost::is_same<point2D<TypePrimitif>,T> {};
  template<typename T, typename TypePrimitif>
    struct is_point3D   : boost::is_same<point3D<TypePrimitif>,T> {};
  template<typename T, typename TypePrimitif>
    struct is_pointND   : boost::is_same<pointND<TypePrimitif>,T> {};

  template<typename T, typename TypePrimitif>
    struct is_segment2D : boost::is_same<segment2D<TypePrimitif>,T> {};
  template<typename T, typename TypePrimitif>
    struct is_segment3D : boost::is_same<segment3D<TypePrimitif>,T> {};
  template<typename T, typename TypePrimitif>
    struct is_segmentND : boost::is_same<segmentND<TypePrimitif>,T> {};
}

//Dans un namespace sfinae définir les spécialisations de distance en utilisants les définitions précédentes
namespace sfinae
{
  // Distance entre un point et un point
  template<typename Type1, typename Type2> double distance(
                          Type1 const& p1,
                          Type2 const& p2,
                          typename enable_if<
                          (objets::is_point2D<Type1, coord_t<Type1>>::value || objets::is_point3D<Type1, coord_t<Type1>>::value
                          || objets::is_pointND<Type1, coord_t<Type1>>::value)
                          &&
                          (objets::is_point2D<Type2, coord_t<Type2>>::value || objets::is_point3D<Type2, coord_t<Type2>>::value
                          || objets::is_pointND<Type2, coord_t<Type2>>::value)
                          >::type* dummy=0)
  {
    double r{0};
    auto s = std::max(size(p1),size(p2));

    for(std::size_t i=0;i<s;++i)
    {
      auto d = at(p1,i) - at(p2,i);
      r += d*d;
    }

    return std::sqrt(r);
  }
  
  // Distance entre un segment et un point
  template<typename Type, typename Point> double distance(
                          Type const& s,
                          Point const& p,
                          typename enable_if<
                          (objets::is_segment2D<Type, coord_t<Type>>::value
                          || objets::is_segment3D<Type, coord_t<Type>>::value
                          || objets::is_segmentND<Type, coord_t<Type>>::value)
                          &&
                          (objets::is_point2D<Point, coord_t<Point>>::value
                          || objets::is_point3D<Point, coord_t<Point>>::value
                          || objets::is_pointND<Point, coord_t<Point>>::value)
                          >::type* dummy=0) 
  {
    //Si le segment est nul : retourner la distance entre un point du segment et le point3D
    double lengthSegment = sfinae::distance(s[0],s[1]);
    if(lengthSegment == 0) return sfinae::distance(s[0],p);
    
    // Coordonnées du vecteur que fait le point p avec le premier point du segment
    double r{0}, r_pow{0};
    std::vector<coord_t<Type>> vecBVector;
    auto siz = std::max(size(s),size(p));

    for(std::size_t i=0;i<siz;++i)
    {
      auto vecA = at(p,i) - at(s.at(0),i);
      auto vecB = at(s.at(1),i) - at(s.at(0),i);
      vecBVector.push_back(vecB);
      r += vecA * vecB;
      r_pow += pow(vecB,2);
    }

    // On calcule le projeté orthogonal Pprime de p sur s paramétré par t
    auto t = r / r_pow;

    // Si P' € s alors t €]0;1] sinon on le ramène à l'extréminité la plus proche sur le segment
    if( !(t >= 0 && t <= 1)) t = fmin( fmax(0,t), 1);

    r = 0;
    for(std::size_t j=0;j<siz;++j)
    {
      r += pow((at(s.at(0),j) + t*vecBVector.at(j)) - at(p,j),2);
    }

    // retourner la racine carré de la somme des carré des coordonnées
    return std::sqrt(r);
  }

  // Distance entre un point et un segment
  template<typename Point, typename Type> double distance(
                          Point const& p,
                          Type const& s,
                          typename enable_if<
                          (objets::is_segment2D<Type, coord_t<Type>>::value
                          || objets::is_segment3D<Type, coord_t<Type>>::value
                          || objets::is_segmentND<Type, coord_t<Type>>::value)
                          &&
                          (objets::is_point2D<Point, coord_t<Point>>::value
                          || objets::is_point3D<Point, coord_t<Point>>::value
                          || objets::is_pointND<Point, coord_t<Point>>::value)
                          >::type* dummy=0) 
  {
    return distance(s,p);
  }

  // Distance entre deux segments
  template<typename Type1, typename Type2> double distance(
                          Type1 const& s1,
                          Type2 const& s2,
                          typename enable_if<
                          (objets::is_segment2D<Type1, coord_t<Type1>>::value 
                          || objets::is_segment3D<Type1, coord_t<Type1>>::value
                          || objets::is_segmentND<Type1, coord_t<Type1>>::value)
                          &&
                          (objets::is_segment2D<Type2, coord_t<Type2>>::value 
                          || objets::is_segment3D<Type2, coord_t<Type2>>::value
                          || objets::is_segmentND<Type2, coord_t<Type2>>::value)
                          >::type* dummy=0)
  {
    // Les milieux des segments sont des pointND (dans le doute)
    pointND<coord_t<Type1>> premier;
    pointND<coord_t<Type2>> deuxieme;

    for(std::size_t i=0;i<size(s1);++i)
    {
      premier.push_back((at(s1.at(0),i)+at(s1.at(1),i))/2);
    }

    for(std::size_t i=0;i<size(s2);++i)
    {
      deuxieme.push_back((at(s2.at(0),i)+at(s2.at(1),i))/2);
    }

    // Retourne la distance entre les milieux des deux segments
    return distance(premier, deuxieme);
  }
}

#endif
