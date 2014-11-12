// -----------------------TP 1 C++ ------------------------//
// Compiler avec l'option -std=c++11
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/type_traits/is_same.hpp>



/* 
	Exercice 1 : Tag dispatching  
*/

/* Définir un tag rectangle et un tag square. Implémenter les structures square et rectangle
   en leur rajoutant chacun une définition pour la forme.
*/
   struct rectangle_tag {};
   struct square_tag {};

   struct Rectangle
   {
   public:
   	typedef rectangle_tag shape_type;
   	Rectangle() : h(0.f), w(0.f) {}
   	Rectangle(float const& h_, float const& w_) : h(h_), w(w_) {}
   	Rectangle(Rectangle const& rs)
   	{
   		w = rs.w;
   		h = rs.h;
   	}
   	Rectangle& operator=(Rectangle const& r)
   	{
   		w = r.w;
   		h = r.h;
   		return *this;
   	}
   	void set_width( float const& w_){ w  = w_; }
   	void set_height(float const& h_){ h = h_; }
   	float  get_width()  const { return w;  }
   	float  get_height() const { return h; }
   private:
   	float h,w;
   };

   struct Square 
   {
   public:
   	typedef square_tag shape_type;
   	Square() : c(0.f) {}
   	Square(float const& c_) : c(c_) {}
   	Square(Square const& rs)
   	{
   		c = rs.c;
   	}
   	Square& operator=(Square const& r)
   	{
   		c = r.c;
   		return *this;
   	}
   	void set_side( float const& s){ c  = s; }
   	float get_side() const { return c; }
   private:
   	float c;
   };

/*
	Dans un namespace details définir les fonctions perimeter qui prennent en entré une structure et un tag
	et renvoient la valeur de son périmètre 
*/
	namespace details 
	{
    template<typename Rectangle>
		float perimeter(Rectangle const& r, rectangle_tag ) { return 2.*(r.get_height()+r.get_width()); }
    template<typename Square>
		float perimeter(Square const& s, square_tag) { return 4.*s.get_side(); }
	}

/*
	Dans un namesapce tagd on définira ensuite une fonction perimeter générique qui prend une structure en paramètre
	et renvoie son périmètre 
*/
	namespace tagd
	{
	template<class Shape>
		float perimeter(Shape const& s)
		{
			typename Shape::shape_type shape_type_;
			return details::perimeter(s,shape_type_);
		}

	}
/* 
	Exercice 2 : SFINAE 

	Regarder le cours pour des exemples de sfinae 
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


template<typename T>
	T testfun() {}

	template<>
	int testfun<int>() {}
/*
	Dans un namespace traits définir les structures is_rectangle et is_square en utilisant boost::is_same 
*/

	namespace traits 
	{
  template<typename T>
		struct is_rectangle : boost::is_same<Rectangle,T> {};
  template<typename T>
		struct is_square : boost::is_same<Square,T> {};
	}

/*
	Dans un namespace sfinae définir les spécialisations de perimeter en utilisants les définitions précédentes
*/

	namespace sfinae
	{
template<typename Rectangle>
		float perimeter( Rectangle const& r
			, 

		{ return 2.*(r.get_height()+r.get_width()); }
template<typename Square>
		float perimeter(Square const& s , typename enable_if<traits::is_square<Square>::value>::type* dummy=0) 
		{ return 4.*s.get_side(); }

	}


/*
	Exercice Bonus : Trouver un moyen de redéfinir l'opérateur << pour la classe matrice définie ci-dessous
	( http://www.stroustrup.com/Programming/Matrix/Matrix.h )
*/
//-----------------------------------------------------------------------------

	struct Matrix_error {
		std::string name;
		Matrix_error(const char* q) :name(q) { }
		Matrix_error(std::string n) :name(n) { }
	};

//-----------------------------------------------------------------------------

	inline void error(const char* p)
	{
		throw Matrix_error(p);
	}

	typedef long Index;

// Matrix_base represents the common part of the Matrix classes:
template<class T> class Matrix_base {
    // matrixs store their memory (elements) in Matrix_base and have copy semantics
    // Matrix_base does element-wise operations
protected:
    T* elem;    // vector? no: we couldn't easily provide a vector for a slice
    const Index sz;    
    mutable bool owns;
    mutable bool xfer;
public:
	Matrix_base(Index n) :elem(new T[n]()), sz(n), owns(true), xfer(false)
        // matrix of n elements (default initialized)
	{
        // std::cerr << "new[" << n << "]->" << elem << "\n";
	}

	Matrix_base(Index n, T* p) :elem(p), sz(n), owns(false), xfer(false)
        // descriptor for matrix of n elements owned by someone else
	{
	}

	~Matrix_base()
	{
		if (owns) {
            // std::cerr << "delete[" << sz << "] " << elem << "\n";
			delete[]elem;
		}
	}

    // if necessay, we can get to the raw matrix:
	T* data()       { return elem; }
	const T* data() const { return elem; }
	Index    size() const { return sz; }

	void copy_elements(const Matrix_base& a)
	{
		if (sz!=a.sz) error("copy_elements()");
		for (Index i=0; i<sz; ++i) elem[i] = a.elem[i];
	}

void base_assign(const Matrix_base& a) { copy_elements(a); }

void base_copy(const Matrix_base& a)
{
        if (a.xfer) {          // a is just about to be deleted
                               // so we can transfer ownership rather than copy
            // std::cerr << "xfer @" << a.elem << " [" << a.sz << "]\n";
        	elem = a.elem;
            a.xfer = false;    // note: modifies source
            a.owns = false;
        }
        else {
        	elem = new T[a.sz];
            // std::cerr << "base copy @" << a.elem << " [" << a.sz << "]\n";
        	copy_elements(a);
        }
        owns = true;
        xfer = false;
    }

    // to get the elements of a local matrix out of a function without copying:
    void base_xfer(Matrix_base& x)
    {
    	if (owns==false) error("cannot xfer() non-owner");
        owns = false;     // now the elements are safe from deletion by original owner
        x.xfer = true;    // target asserts temporary ownership
        x.owns = true;
    }

    template<class F> void base_apply(F f) { for (Index i = 0; i<size(); ++i) f(elem[i]); }
    template<class F> void base_apply(F f, const T& c) { for (Index i = 0; i<size(); ++i) f(elem[i],c); }
private:
    void operator=(const Matrix_base&);    // no ordinary copy of bases
    Matrix_base(const Matrix_base&);
};


template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix_base<T> const& m)
{
	for(int i = 0; i<m.size(); ++i)
	{
		os << (m.data())[i] ;
		os << " ";
	}
	os << "\n";
	return os;
}


int main()
{
	std::cout << "Exercice 1 : tag dispatching " << std::endl;
	Rectangle rec(2.,5.);
	Square s(2.);
	std::cout << "P: " << tagd::perimeter(rec) << std::endl;
	std::cout << "P: " << tagd::perimeter(s) << std::endl;

	std::cout << "Exercice 2 : sfinae " << std::endl;
	std::cout << "P: " << sfinae::perimeter(rec) << std::endl;
	std::cout << "P: " << sfinae::perimeter(s) << std::endl;

	std::cout << "Exercice 3 : bonus " << std::endl;
	float foo[] = { 1., 2., 1., 2.,1., 2.,1., 2.,1., 2. };
 // Matrix_base<float> mat1(10,foo);
 // std::cout << mat1 ;

	return 0;
}





