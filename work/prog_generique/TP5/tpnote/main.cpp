#include <iostream>
#include <string>
#include "distance.hpp"
#include "pixel.hpp"
//#include "bizarro.hpp"

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
  //bizarro_point wuz{3,0.5,'Z'};

  std::array<float,5> xx{1,2,3,4,5};
  std::array<float,5> yy{-1,-2,-3,-4,-5};
  point2D<double> q2{68,4};

  coord_t<pixel> px = at(a,0);
  coord_t<pixel> py = at(a,1);
  //std::cout << px << " " << py << "\n"; // 3 4
  //std::cout << at<3>(xx) << "\n"; // 4
  //std::cout << at<0>(q2) << "\n"; // 68

  /*std::cout << at(wuz,0) << "\n";
  std::cout << at(wuz,1) << "\n";
  std::cout << at(wuz,2) << "\n";
  std::cout << at<0>(wuz) << "\n";
  std::cout << at<1>(wuz) << "\n";
  std::cout << at<2>(wuz) << "\n";
  std::cout << at<-2>(wuz) << "\n";*/
/*
  std::cout << q.size() << "\n"; // 3
  std::cout << p[0] << "\n"; // 1
  std::cout << p[1] << "\n"; // 1
  std::cout << p[2] << "\n"; // 1
  std::cout << distance(p,q) << "\n"; // 1.7320
  std::cout << distance(q2,q) << "\n";
  std::cout << distance("lol!","rofl") << "\n";
  std::cout << distance(a,b) << "\n";
  std::cout << distance(xx,yy) << "\n";
  std::cout << distance(xx,a) << "\n";
*/
  point2D<double> q3{1,1};
  point2D<double> q4{2,2};
  point2D<double> p1{5,5};

  point3D<double> r1{1.,1.,1.};
  point3D<double> r2{2.,2.,2.};
  point3D<double> p2{5.,5.,5.};
  point3D<double> p3{66.,0,10.};

  segment2D<double> monSegment2D{q3,q4};
  segment2D<double> monSegment2DNul{q3,q3};
  segment3D<double> monSegment3D{r1,r2};
  segment3D<double> monSegment3DNul{r1,r2};

  segmentND<double> monSegmentND{p,q};
  pointND<double> monPointND{1,2,3,4,5,6};

  coord_t<point2D<int>> toto = at(p1,0);

  //std::cout << toto << "\n";
  //std::cout << sfinae::distance(q3, q4) << "\n";
  std::cout << sfinae::distance(monSegment2D, p1) << "\n";
  //std::cout << distance(monSegment2DNul, q3) << "\n";
  //std::cout << distance(monSegment2DNul, p1) << "\n";

  //std::cout << distance(monSegment3D, p2) << "\n";
  //std::cout << distance(monSegment3DNul, r1) << "\n";
  //std::cout << distance(monSegment3DNul, p2) << "\n";
  //std::cout << distance(monSegment3D, p3) << "\n";

  //std::cout << distance(monSegmentND,p1) << "\n";
}

/**
Segment : 2D
          3D
          ...
          ND
Distance  segment-point
          point-segment

perimetre polygone
aire polygone
*/