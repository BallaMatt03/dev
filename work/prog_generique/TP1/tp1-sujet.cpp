// -----------------------TP 1 C++ ------------------------//
// Compiler avec l'option -std=c++11
#include <iostream>
#include <typeinfo>
#include <tuple>


/*
Les templates sont la base de la programmation générique en C++. Il s'agit en fait de modèles 
génériques de code qui permettent de créer automatiquement des fonctions ou des classes à partir 
d'un ou plusieurs paramètres.
*/

// Exemple d'une fonction template qui prent un type T en paramètre et qui l'affiche  
template<typename T>
void fonction_exemple(T a)
{
	std::cout<< "la variable a : " << a << std::endl; 
}

// Il est aussi possible de faire ce qu'on appele de la spécialisation partielle 
template<>
void fonction_exemple<double>(double a)
{
	std::cout<< "la variable a de type double vaut : " << a << std::endl; 
}

// Exercice 1
//Ecrire une fonction avec un paramètre template qui calcule le min et une autre calculant le max 
//de deux valeurs en utilisant des templates. On suppose dans un premier temps que a et b sont du même type.


//mettre le code des fonctions min et max.
template<typename TYPE>
TYPE min(TYPE a, TYPE b)
{
	return a<b ? a : b;
}
template<typename TYPE>
TYPE max(TYPE a, TYPE b)
{
	return a>b ? a : b;
}


// Exercice 2 
// Ecrire une fonction template qui calcule la valeur moyenne de deux points. Cette fonction vous semble
// t'elle pertinente tout le temps? Proposer une solution.

//mettre le code de la fonction moy
template<typename TYPE>
TYPE moy(TYPE a, TYPE b)
{
	return (a+b)/TYPE(2);
}

// Astuce 1 : Utiliser une structure qui calculera le type de retour de votre fonction en utilisant decltype 
// (et std::declval). 

// decltype permet d'extraire le type d'une variable (ou d'une expression)
//Exemple d'utilisation.
template<typename T> T fun_t(T a) { return a;}; // voir main pour decltype 
// decltype(x) e1 = x;  // e1 a le type de x 	
// decltype(fun_t(a1) ) e2 = x; // e2 a le type de retour de fun_t(a1) 
// regarder la doc pour declval

// Squelette de la structure
template<typename T>
struct moy1_
{
	typedef decltype((std::declval<T>() + std::declval<T>())/2.f) type;
};

// ecrire le code la fonction moy1
template<typename T>
typename moy1_<T>::type moy1(T a, T b)
{
	return (a+b)/2.f;
}

// Astuce 2 : Utiliser les inférences de type du standard c++11 avec auto et decltype pour faire une fonction de moyenne sans 
// utiliser de structure

// Si le compilateur est capable d'inferer le type d'une variable durant sa déclaration, alors on peut utiliser le mot clef auto
// Exemple : 
// int x = 4; peut être remplacé par 
// auto x = 4; ceci n'est pas très utile
// Cas plus interessant d'utilisation
//vector<int> vec;
// auto itr = vec.iterator(); // au lieu de vector<int>::iterator itr

//mettre le code la fonction moy2
template<typename T>
auto moy2(T a, T b) -> decltype((a+b)/2.f)
{
	return (a+b)/2.f;
}
// Exercice 2 - suite
// Reecrire les fonctions gmin et gmax en prenant cette fois deux arguments template en paramètre en utilisant la auto et 
// decltype . Essayer de compiler avec clang


//mettre le code des fonctions gmin, gmax et moy3
template<typename T, typename S>
auto gmin(T a, S b) -> decltype((a<b) ? a : b)
{
	return (a<b) ? a : b;
}
template<typename T, typename S>
auto gmax(T a, S b) -> decltype((a>b) ? a : b)
{
	return (a>b) ? a : b;
}
template<typename T, typename S>
auto moy3(T a, S b) -> decltype((a+b)/2.f)
{
	return (a+b)/2.f;
}
//Ecrire une fonction variadique retournant la moyenne de n points


//code la fonction moyenne_n
template<typename... T>
float moyenne_n(T...Ts)
{
	float somme;
	float cpt = 0.f;
	for(auto v : {Ts...}){
		somme += v;
		cpt++;
	}
	
	return somme/cpt;
}

// Ecrire une classe template vecteur basique. On utilisera un pointeur sur type générique pour
// les valeurs à stocker. Il faudra une fonction pour retourner la taille du vecteur ainsi qu'un 
// opérateur de parcours de tableau

template <typename T>
class Vecteur{
	protected:
		std::size_t taille; 
		T *data; 
	public:

		// operateur pour initialiser le Vecteur

        // le constructeur
        Vecteur<T>(std::size_t nb = 0 /*Valeur par défaut*/){
            taille = nb; /*Initialisation de la taille du vecteur*/
            
            data = ((T *)malloc(sizeof(T)*nb)); /*Allocation mémoire*/
            
            for(std::size_t i=0;i<nb;i++){
                data[i] = T(1)+ T(1)/T(10);
            }
        }

		// Le destructeur
		~Vecteur()
		{
		    free(data);
		}

		std::size_t size() const
		{
		return taille;
		}

		T & operator[](std::size_t i)
		{
		    if(i >= size() ) exit(1); /*Si pas le bon indice, je sors*/
            return data[i];
		}
};

// Ecrire la fonction accumulation prenant un vecteur en entree
template <typename T>
T Accumulation(Vecteur<T> & v){ /*Passage en référence*/
    T somme = 0;
    for(std::size_t i=0;i<v.size();i++){
        somme += v[i];
    }
    
    return somme;
}

int main()
{
	int a = 5;
	int b = 6;
	int x = 6;
	double a1 = 5.1;
	double b1 = 6.;
	char c = 'e' ;
	char c1 = 'f';

	// affichage de l'exemple :
	std::cout << "Exemple d'utilisation de template :" << std::endl;
	fonction_exemple(a);
	fonction_exemple(a1);
	std::cout << "\n";

	// Exercice 1

	std::cout << "Exercice 1 :" << std::endl;
	std::cout << "la valeur min entre a et b est : " << min(a,b) << std::endl;
	std::cout << "la valeur min entre a1 et b1 est : " << min(a1,b1) << std::endl;
	std::cout << "la valeur max entre a et b est : " << max(a,b) << std::endl;
	std::cout << "la valeur max entre c et c1 est : " << max(c,c1) << std::endl << std::endl;

	// Exercice 2 :
	std::cout << "Exercice 2 :" << std::endl;

	std::cout << "la moyenne (moy)  de a et b est : " 		 << moy(a,b) << std::endl<< std::endl;

	// Exemple avec decltype
	std::cout << "Exemple d'utilisation de decltype" << std::endl;
	decltype(x) e1 = x;  // e1 a le type de x soit int	
	std::cout << " le type de e1 est : " << typeid(e1).name() << std::endl;
	decltype(fun_t(a1) ) e2 = x; // e2 a le type de retour de fun_t(a1) soit double
	std::cout << " le type de e2 est : " << typeid(e2).name() << std::endl << std::endl;

	// Astuce 1

	std::cout << "Astuce 1 : " << std::endl;
	std::cout << "la moyenne (moy1) de a et b est : " 	     << moy1(a,b) << std::endl;
	// Astuce 2

	std::cout << "Astuce 2 : " << std::endl;
	std::cout << "la moyenne (moy2) de a et b est : " 		 << moy2(a,b) << std::endl;
	std::cout << "la moyenne (moy3) de a et b1 est : " 	     << moy3(a,b1) << std::endl;
	
	// Exercice 2 - suite

	std::cout << "Exercice 2 - suite : " << std::endl;
	std::cout << "la valeur min (gmin) entre a et b1 est : " << gmin(a,b1) << std::endl;
	std::cout << "la valeur max (gmax) entre c et b1 est : " << gmax(c,b1) << std::endl << std::endl;

	//Exercice 3 :

	std::cout << "Exercice 3 :" << std::endl;
	std::cout << "la moyenne de a,b,x est : " << moyenne_n(a,b,x) << std::endl << std::endl ; 
	
	//Exercice 4 :

	std::cout << "Exercice 4 :" << std::endl;
	Vecteur<int> v1(10);
	Vecteur<double> v2(10);
	std::cout << "la somme des valeurs du vecteur v1 vaut : " << Accumulation(v1) << std::endl; 
	std::cout << "la somme des valeurs du vecteur v2 vaut : " << Accumulation(v2) << std::endl; 

	return 0;
}
