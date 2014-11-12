#include <iostream>
#include <numeric>
#include <functional>

int myfunction (int x, int y) {return x+2*y;}

struct myclass {
	int operator()(int x, int y) {return x+3*y;}
} myobject;

int main () {
  int init = 0;
  int nombres[] = {1,2,3};

  std::cout << "using default accumulate: ";
  std::cout << std::accumulate(nombres,nombres+3,init) << '\n';

  std::cout << "using functional's minus: ";
  std::cout << std::accumulate(nombres, nombres+3, init, std::minus<int>());
  std::cout << '\n';

  std::cout << "using custom function: ";
  std::cout << std::accumulate(nombres, nombres+3, init, myfunction);
  std::cout << '\n';

  std::cout << "using custom object: ";
  std::cout << std::accumulate(nombres, nombres+3, init, myobject);
  std::cout << '\n';

  return 0;
}
