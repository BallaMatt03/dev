// -----------------------TP 3 C++ ------------------------//
// Compiler avec l'option -std=c++11
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/type_traits/is_same.hpp>
/* 
	Exercice 1 : Tag dispatching 
*/

/* Définir un tag rectangle et un tag square. Implémenter les classes square et rectangle (forme de copplien)
   en leur rajoutant chacun une définition pour la forme.
*/
struct rectangle_tag {};
struct square_tag {};

 class Rectangle
 {
 	/*Définition*/
 private:
 	float longueur;
 	float largeur;
 public:

 	typedef rectangle_tag monTag;

 	Rectangle(float a, float b){
 		longueur = a;
 		largeur = b;
 	}

 	Rectangle(const Rectangle& a)
 	{
 		longueur = a.longueur;
 		largeur = a.largeur;
 	}

 	Rectangle& operator=(const Rectangle& a) 
 	{
 		longueur = a.longueur;
 		largeur = a.largeur;
 		return *this;
 	}

 	~Rectangle()
 	{
 		/*delete ?*/
 		longueur = 0;
 		largeur = 0;
 	}

 	float getLongeur()
 	{
 		return longueur;
 	}

 	float getLargeur()
 	{
 		return largeur;
 	}
 };

 class Square
 {
 	//Définition
 private:
 	float cote;
 public:

 	typedef square_tag monTag;

 	Square(float a)
 	{
 		cote = a;
 	}
 	Square(const Square& a)
 	{
 		cote = a.cote;
 	}

 	Square& operator=(const Square& a)
 	{
 		cote = a.cote;
 		return *this;
 	}

 	~Square()
 	{
 		//delete ?
 		cote = 0;
 	}

 	float getCote(){
 		return cote;
 	}
 };

/*
	Dans un namespace details définir les fonctions perimeter qui prennent en entrée une structure et un tag
	et renvoient la valeur de son périmètre 
*/
	namespace details 
	{
		template <class InputForme>
		float perimeter(InputForme obj, rectangle_tag const& t){
			return obj.getLongeur()*2 + obj.getLargeur()*2;
		}

		template <class InputForme>
		float perimeter(InputForme obj, square_tag const& t){
			return obj.getCote()*4;
		}
	}

/*
	Dans un namespace tagd on définira ensuite une fonction perimeter générique qui prend une structure en paramètre
	et renvoie son périmètre 
*/
	namespace tagd
	{
		template <class InputForme>
		float perimeter(InputForme obj)
		{
			/*perimetre de l'objet*/
			typename InputForme::monTag leTag;
			return details::perimeter(obj, leTag);
		}
	}
/* 
	Exercice 2 : SFINAE 

	Regarder le cours pour des exemples de sfinae 
*/

/*
	Définir la structure enable_if comme vu en cours
*/
template<bool Condition, typename Result=void>
struct enable_if;

template<typename Result>
struct enable_if<true, Result>
{
	typedef Result type;
};

/*
	Dans un namespace traits définir les structures is_rectangle et is_square en utilisant boost::is_same 
*/

	namespace traits 
	{
		template<typename InputForme>
		struct is_rectangle;
		template<typename InputForme>
		struct is_square;

		template<class InputForme>
		struct is_rectangle<boost::is_same<InputForme, Rectangle>::value_type> {};

		template<class InputForme>
		struct is_square<boost::is_same<InputForme, Square>::value_type> {};
	}

/*
	Dans un namespace sfinae définir les spécialisations de perimeter en utilisants les définitions précédentes
*/

	namespace sfinae
	{
		template<class InputForme, typename is_square>
		typename enable_if<is_square>::type
		float perimeter(InputForme obj)
		{
			/*Square*/
			return obj.getCote()*4;
		}

		template<class InputForme, typename is_rectangle>
		typename enable_if<is_rectangle>::type
		float perimeter(InputForme obj)
		{
			/*Rectangle*/
			return obj.getLargeur()*2 + obj.getLongueur()*2;
		}
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

// Que représente la classe F dans base_apply ?

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





