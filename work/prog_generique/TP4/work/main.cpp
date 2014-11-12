#include <iostream>
#include <vector>
#include <cmath>
#include <array>

struct Point2D
{
	int x, y;
};

struct Point3D
{
	int x, y, z;
};

int get(Point2D const& p, int i)
{
	return i == 0 ? p.x : (i == 1 ? p.y : 0);
}

int get(Point3D const& p, int i)
{
	return i == 0 ? p.x : (i == 1 ? p.y : (i == 2 ? p.z : 0));
}

template<typename T, typename A>
T get(std::vector<T,A> const& p, int i)
{
	return i < p.size() ? p[i] : 0;
}

template<typename T, std::size_t N>
T get(std::array<T,N> const& p, int i)
{
	return i < p.size() ? p[i] : 0;
}

int nbDims(Point2D const&)
{
	return 2;
}

int nbDims(Point3D const&)
{
	return 3;
}

template<typename T, typename A>
int nbDims(std::vector<T, A> const& p)
{
	return p.size();
}

template<typename T, std::size_t N>
int nbDims(std::array<T, N> const& p)
{
	return p.size();
}

template<typename P1, typename P2>
double distance(P1 const& p1, P2 const& p2)
{
	double sum = 0.;
	
	auto dim1 = nbDims(p1);
	auto dim2 = nbDims(p2);

	for(int i = 0; i < std::max(dim1, dim2); i++)
	{
		auto d = get(p2, i) - get(p1, i); 
		sum +=  d * d;
	}

	return sqrt(sum);
}

/*
Point2D translate(Point2D p, )
{

}
*/
int main(int argc, char const *argv[])
{
	Point2D p1{0, 0}, p2{1, 1}, p3{2, 2};

	Point3D p4{0, 0, 0}, p5{1, 1, 1}, p6{2, 2, 2};

	std::vector<int> p7{0, 0, 0};
	std::vector<int> p8{1, 1, 1};

	std::cout << "distance (0, 0) - (1, 1) : " << distance(p1, p2) << std::endl;
	std::cout << "distance (0, 0) - (2, 2) : " << distance(p1, p3) << std::endl;

	std::cout << std::endl;

	std::cout << "distance (0, 0, 0) - (1, 1, 1) : " << distance(p4, p5) << std::endl;
	std::cout << "distance (0, 0, 0) - (2, 2, 2) : " << distance(p4, p6) << std::endl;

	std::cout << std::endl;

	std::cout << "distance (0, 0, 0) - (1, 1, 1) : " << distance(p7, p8) << std::endl;

	std::cout << "distance (0, 0, 0) - (1, 1, 1) : " << distance(p1, p8) << std::endl;

	std::array<int, 3> a {2,2,2};

	std::cout << "distance (1, 1, 1) - (2, 2, 2) : " << distance(p8, a) << std::endl;

	return 0;
}
/*
Points communs array & vector :
Elements in sequence containers are ordered in a strict linear sequence.
Individual elements are accessed by their position in this sequence.

*/