#include <iostream>
#include <cmath>
#include <vector>

struct Point2D
{
	double x, y;
};

struct Point3D
{
	double x, y, z;
};

int nb_dims(Point2D const&)
{
    return 2;
}

int nb_dims(Point3D const&)
{
    return 3;
}

template<typename T, typename A /*allocateur*/>
int nb_dims(std::vector<T,A> /**/ const& p)
{
	return p.size();
}

double get(Point2D const& toto, int i)
{
	switch(i){
		case 0:
			return toto.x;
			break;
		case 1:
			return toto.y;
			break;
		default:
			return 0;
			break;
	}
}

double get(Point3D const& toto, int i){
	switch(i){
		case 0:
			return toto.x;
			break;
		case 1:
			return toto.y;
			break;
		case 2:
			return toto.z;
			break;
		default:
			return 0;
			break;

	}
}

template <typename T1,typename T2>
double distance(T1 p0, T2 p1)
{
	double somme = 0;
	for(int i=0;i<std::max(nb_dims(p0),nb_dims(p1));i++)
	{
		auto d = get(p1,i)-get(p0,i);
		somme += d * d;
	}
	return sqrt(somme);
}

int main()
{
	Point2D p1 = {2,2}, p2 = {4,4};
	std::cout << distance(p1,p2) << std::endl;

	Point3D p3 = {2,2,2}, p4 = {4,4,4};
	std::vector<double> p5 = {0.0,5.9,6.3};

	std::cout << distance(p4,p5) << std::endl;
	std::cout << distance(p3,p4) << std::endl;
	std::cout << distance(p2,p3) << std::endl;

	return 0;
}