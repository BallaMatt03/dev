/*
Matthias Ballarini
Date : Lundi 17 novembre 2014
TP noté : Programmation Générique

ligne pour compiler :
g++ --std=c++11 main.cpp -o exe
*/
#include <iostream>
#include <string>
#include "distance.hpp"
#include "perimetre.hpp"
#include "pixel.hpp"

template<typename Point>
void foo(Point const& p)
{
  coord_t<pixel,0> px = at(p,0);
  coord_t<pixel,1> py = at(p,1);
}

int main()
{
  pointND<double> p{1.,1.,1.};
  pointND<double> q(3);
  pixel a{3,4},b{1,-3};

  std::array<float,5> xx{1,2,3,4,5};
  std::array<float,5> yy{-1,-2,-3,-4,-5};
  point2D<double> q2{68,4};

  coord_t<pixel> px = at(a,0);
  coord_t<pixel> py = at(a,1);

  // Declarations de point2D
  point2D<double> q3{1,1};
  point2D<double> q4{2,2};
  point2D<double> p1{5,5};

  // Declarations de point3D
  point3D<double> r1{1.,1.,1.};
  point3D<double> r2{2.,2.,2.};
  point3D<double> p2{5.,5.,5.};
  point3D<double> p3{66.,0,10.};

  // Declarations de pointND
  pointND<double> n1{1.,2.,3.,4.,5.};
  pointND<double> n2{1.,1.,1.,1.,1.};
  pointND<double> n3{2.,2.,2.,2.,2.};
  pointND<double> monPointND{1,2,3,4,5,6};

  // Declarations de segment2D
  segment2D<double> monSegment2D{q3,q4};
  segment2D<double> monSegment2DQuiPete{q3,p1};
  segment2D<double> monSegment2DNul{q3,q3};

  // Declarations de segment3D
  segment3D<double> monSegment3D{r1,r2};
  segment3D<double> monSegment3DQuiPete{r1,p2};
  segment3D<double> monSegment3DNul{r1,r2};

  // Declarations de segmentND
  segmentND<double> monSegmentND{n1,n2};
  segmentND<double> monSegmentNDQuiPete{n2,n3};

  // Tests de la fonction distance
  std::cout << "Distance entre deux point2D :" << "\n";
  std::cout << sfinae::distance(q3, q4) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre deux point3D :" << "\n";
  std::cout << sfinae::distance(r1, r2) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un point2D et un point3D :" << "\n";
  std::cout << sfinae::distance(q3, r2) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un point3D et un point2D :" << "\n";
  std::cout << sfinae::distance(r2, q3) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment2D et un point2D :" << "\n";
  std::cout << sfinae::distance(monSegment2D, p1) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment3D et un point3D :" << "\n";
  std::cout << sfinae::distance(monSegment3D, p3) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un point2D et un segment2D :" << "\n";
  std::cout << sfinae::distance(p1, monSegment2D) << "\n";    
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un point3D et un segment3D :" << "\n";
  std::cout << sfinae::distance(p3, monSegment3D) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment2D et un point3D :" << "\n";
  std::cout << sfinae::distance(monSegment2D, p3) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un point3D et un segment2D :" << "\n";
  std::cout << sfinae::distance(p3, monSegment2D) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un point2D et un segment3D :" << "\n";
  std::cout << sfinae::distance(p1, monSegment3D) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment3D et un point2D :" << "\n";
  std::cout << sfinae::distance(monSegment3D, p1) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un pointND et un pointND :" << "\n";
  std::cout << sfinae::distance(n1, n2) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment2D et un segment2D :" << "\n";
  std::cout << sfinae::distance(monSegment2DQuiPete, monSegment2D) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment3D et un segment3D :" << "\n";
  std::cout << sfinae::distance(monSegment3DQuiPete, monSegment3D) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segmentND et un segmentND :" << "\n";
  std::cout << sfinae::distance(monSegmentND, monSegmentNDQuiPete) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Distance entre un segment3D et un segmentND :" << "\n";
  std::cout << sfinae::distance(monSegment3DQuiPete, monSegmentNDQuiPete) << "\n";
  std::cout << "--------------------------------" << "\n";

  // Polygone
  // Declarations des pointND
  pointND<double> m1{0.,0.,1.};
  pointND<double> m2{0.,1.,1.};
  pointND<double> m3{1.,1.,1.};
  pointND<double> m4{1.,0.,1.};
  pointND<double> m5{1.,-1.,1.};

  // Declaration des polygones
  polygone<double> monPolygone {m1, m2, m3, m4};
  polygone<double> monPolygone2 {m1, m2, m3, m4, m5};

  // Test de la fonction perimetre d'un polygone
  std::cout << "Perimetre d'un polygone a 4 sommets :" << "\n";
  std::cout << perimetre(monPolygone) << "\n";
  std::cout << "--------------------------------" << "\n";
  std::cout << "Perimetre d'un polygone a 5 sommets :" << "\n";
  std::cout << perimetre(monPolygone2) << "\n";
  std::cout << "--------------------------------" << "\n";


}

/*
Segment : 2D
          3D
          ...
          ND
Distance  segment-point
          point-segment
          segment-segment

perimetre polygone
aire polygone
*/