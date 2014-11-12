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

//Distance entre un segment2D et un point2D
template<typename Type1, typename Type2>
double distance(segment2D<Type1> const& s, point2D<Type2> const& p)
{
  //Si le segment est nul : retourner la distance entre un point du segment et le point2D
  double lengthSegment = distance(s[0],s[1]);
  if(lengthSegment == 0) return distance(s[0],p);
  
  // Coordonnées du vecteur que fait le point p avec le premier point du segment
  auto vecAx = p.at(0) - s.at(0).at(0);
  auto vecAy = p.at(1) - s.at(0).at(1);

  // Coordonnées du vecteur que fait le premier point du segment avec le second
  auto vecBx = s.at(1).at(0) - s.at(0).at(0);
  auto vecBy = s.at(1).at(1) - s.at(0).at(1);

  // On calcule le projeté orthogonal Pprime de p sur s paramétré par t
  auto t = (vecAx * vecBx + vecAy * vecBy) / ( pow(vecBx,2) + pow(vecBy,2) );

  // Si P' € s alors t €]0;1] sinon on le ramène à l'extréminité la plus proche sur le segment
  if( !(t >= 0 && t <= 1)) t = fmin( fmax(0,t), 1);

  // On obtient la distance entre p et s en calculant la distance entre p et Pprime
  auto Pprimex = s.at(0).at(0) + t*vecBx;
  auto Pprimey = s.at(0).at(1) + t*vecBy;

  // retourner la racine carré de la somme des carré des coordonées
  return std::sqrt( pow(Pprimey - p.at(1), 2) + pow(Pprimex - p.at(0),2) );
}






//Distance entre un segment3D et un point3D
template<typename Type1, typename Type2>
double distance(segment3D<Type1> const& s, point3D<Type2> const& p)
{
  //Si le segment est nul : retourner la distance entre un point du segment et le point3D
  double lengthSegment = distance(s[0],s[1]);
  if(lengthSegment == 0) return distance(s[0],p);
  
  // Coordonnées du vecteur que fait le point p avec le premier point du segment
  auto vecAx = p.at(0) - s.at(0).at(0);
  auto vecAy = p.at(1) - s.at(0).at(1);
  auto vecAz = p.at(2) - s.at(0).at(2);

  // Coordonnées du vecteur que fait le premier point du segment avec le second
  auto vecBx = s.at(1).at(0) - s.at(0).at(0);
  auto vecBy = s.at(1).at(1) - s.at(0).at(1);
  auto vecBz = s.at(1).at(2) - s.at(0).at(2);

  // On calcule le projeté orthogonal Pprime de p sur s paramétré par t
  auto t = (vecAx * vecBx + vecAy * vecBy + vecAz * vecBz) / ( pow(vecBx,2) + pow(vecBy,2) + pow(vecBz,2) );

  // Si P' € s alors t €]0;1] sinon on le ramène à l'extréminité la plus proche sur le segment
  if( !(t >= 0 && t <= 1)) t = fmin( fmax(0,t), 1);

  // On obtient la distance entre p et s en calculant la distance entre p et Pprime
  auto Pprimex = s.at(0).at(0) + t*vecBx;
  auto Pprimey = s.at(0).at(1) + t*vecBy;
  auto Pprimez = s.at(0).at(2) + t*vecBz;

  // retourner la racine carré de la somme des carré des coordonées
  return std::sqrt( pow(Pprimey - p.at(1), 2) + pow(Pprimex - p.at(0),2) + pow(Pprimez - p.at(2),2) );
}

//Distance entre un segmentND et un pointND

//Distance entre un segment et un point
template <class Point>
class Segment
{
  private:
    std::array<Point,2> lesPoints;
};

template <typename Point1, typename Point2>
double distance(Segment<Point1> const& s, Point2 const& p)
{
  //Si le segment est nul : retourner la distance entre un point du segment et le point3D
  double lengthSegment = distance(s[0],s[1]);
  if(lengthSegment == 0) return distance(s[0],p);
  
  // Coordonnées du vecteur que fait le point p avec le premier point du segment
  auto vecAx = p.at(0) - s.at(0).at(0);
  auto vecAy = p.at(1) - s.at(0).at(1);
  auto vecAz = p.at(2) - s.at(0).at(2);

  // Coordonnées du vecteur que fait le premier point du segment avec le second
  auto vecBx = s.at(1).at(0) - s.at(0).at(0);
  auto vecBy = s.at(1).at(1) - s.at(0).at(1);
  auto vecBz = s.at(1).at(2) - s.at(0).at(2);

  // On calcule le projeté orthogonal Pprime de p sur s paramétré par t
  auto t = (vecAx * vecBx + vecAy * vecBy + vecAz * vecBz) / ( pow(vecBx,2) + pow(vecBy,2) + pow(vecBz,2) );

  // Si P' € s alors t €]0;1] sinon on le ramène à l'extréminité la plus proche sur le segment
  if( !(t >= 0 && t <= 1)) t = fmin( fmax(0,t), 1);

  // On obtient la distance entre p et s en calculant la distance entre p et Pprime
  auto Pprimex = s.at(0).at(0) + t*vecBx;
  auto Pprimey = s.at(0).at(1) + t*vecBy;
  auto Pprimez = s.at(0).at(2) + t*vecBz;

  // retourner la racine carré de la somme des carré des coordonées
  return std::sqrt( pow(Pprimey - p.at(1), 2) + pow(Pprimex - p.at(0),2) + pow(Pprimez - p.at(2),2) );
}


*/






/*
  Définir la structure enable_if comme vu en cours
*/
template<bool, typename T = void> 
  struct enable_if {};

template<typename T>
  struct enable_if<true, T> {
    typedef T type;
  };


template<typename T> T testfun() {}

template<> int testfun<int>() {}

/*
  Dans un namespace objets définir les structures is_rectangle et is_square en utilisant boost::is_same 
*/
namespace objets
{
  template<typename T, typename TypePrimitif>
    struct is_point   : boost::is_same<point2D<TypePrimitif>,T> {};
  template<typename T, typename TypePrimitif>
    struct is_segment : boost::is_same<segment2D<TypePrimitif>,T> {};
}

/*
  Dans un namespace sfinae définir les spécialisations de perimeter en utilisants les définitions précédentes
*/
namespace sfinae
{
  template<typename Type> double distance(
                          Type const& t,
                          Type const& p,
                          typename enable_if<objets::is_point<Type, coord_t<Type>>::value>::type* dummy=0)
  {
    // Point et point
    return -2;
  }
  
  template<typename Type, typename Point> double distance(
                          Type const& t,
                          Point const& p,
                          typename enable_if<objets::is_segment<Type, coord_t<Type>>::value>::type* dummy=0) 
  {
    // Segment et point
    return -3;
  }
}






/*
//Distance entre un segment et un point
template<typename Type1, typename Type2>
double distance(Type1 const& s, Type2 const& p)
{
  //Si le segment est nul : retourner la distance entre un point du segment et le point3D
  double lengthSegment = distance(s[0],s[1]);
  if(lengthSegment == 0) return distance(s[0],p);
  
  // Coordonnées du vecteur que fait le point p avec le premier point du segment
  auto vecAx = p.at(0) - s.at(0).at(0);
  auto vecAy = p.at(1) - s.at(0).at(1);
  auto vecAz = p.at(2) - s.at(0).at(2);

  // Coordonnées du vecteur que fait le premier point du segment avec le second
  auto vecBx = s.at(1).at(0) - s.at(0).at(0);
  auto vecBy = s.at(1).at(1) - s.at(0).at(1);
  auto vecBz = s.at(1).at(2) - s.at(0).at(2);

  // On calcule le projeté orthogonal Pprime de p sur s paramétré par t
  auto t = (vecAx * vecBx + vecAy * vecBy + vecAz * vecBz) / ( pow(vecBx,2) + pow(vecBy,2) + pow(vecBz,2) );

  // Si P' € s alors t €]0;1] sinon on le ramène à l'extréminité la plus proche sur le segment
  if( !(t >= 0 && t <= 1)) t = fmin( fmax(0,t), 1);

  // On obtient la distance entre p et s en calculant la distance entre p et Pprime
  auto Pprimex = s.at(0).at(0) + t*vecBx;
  auto Pprimey = s.at(0).at(1) + t*vecBy;
  auto Pprimez = s.at(0).at(2) + t*vecBz;

  // retourner la racine carré de la somme des carré des coordonées
  return std::sqrt( pow(Pprimey - p.at(1), 2) + pow(Pprimex - p.at(0),2) + pow(Pprimez - p.at(2),2) );
}
*/



#endif
