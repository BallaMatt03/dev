// -----------------------TP 1 C++ ------------------------//
// Compiler avec l'option -std=c++11
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
/*
CRTP (Curiously recurring Template pattern) :
C'est l'équivalent mais à la compilation de private ( ou protected) appliqué à des fonctions 
virtuelles qui peuvent être réimplémenté par une classe dérivé. 

Voici une exemple d'utilisation du CRTP :
*/

template <typename Child>
struct Base    
{
    void interface() 
    {
        static_cast<Child*>(this)->implementation();
    }
};

struct Fille: Base<Fille> // Fille herite de Base<Fille> ce qui permet d'injecter
{						  // le type de Fille dans Base pour caster statiquement
    void implementation()
    {
        std::cout << "implementation de Fille" << std::endl;
    }
};


// Un exemple de code ayant un comportement indetermine :

class Base1 {
public:
    virtual ~Base1() {}
    virtual Base1 *copy() = 0;
    virtual void print() = 0;
};

template <typename Derived>
class BaseCopy: public Base1 {
public:
    virtual Base1 *copy()
    {
        return new Derived(static_cast<Derived const&>(*this));
    }
};

class Bar: public BaseCopy<Bar> { public: void print(void) { std::cout << "Je suis Bar" << std::endl;} };
class Foo: public BaseCopy<Bar> { public: void print(void) { std::cout << "Je suis Foo" << std::endl;} };


/*
Ecrire une structure d'arbre binaire avec chaque noeud ayant une valeur et deux fils.
Pour la valeur on utilisera un type enum { Rouge, Bleu}
*/

struct Arbre
{
    enum type { Rouge, Bleu };

    Arbre(type f_ = Rouge, Arbre* g_ = NULL, Arbre* d_ = NULL)
        : fvalue(f_), fils_g(g_) , fils_d(d_)
    {}

    type fvalue;
    Arbre *fils_g, *fils_d;
};

/* Ecrire une classe générique de visiteur permettant de visiter l'arbre dans l'ordre 
de votre choix en utilisant CRTP :
    - inclure une fonction pour visiter l'arbre qui affichera la couleur du noeud courant
    et parcours ensuite les suivant ( ou dans un autre ordre)
    - une fouction d'affichage pour le cas rouge et une pour bleu
    - le CRTP 
*/

template <typename Derived>
class GenericVisitor
{
public:
    void visit_1(Arbre* noeud)
    {
        if (noeud) {
            noeud_val(noeud);
            visit_1(noeud->fils_g);
            visit_1(noeud->fils_d);
        }
    }
     void cas_rouge(Arbre* noeud)
    {
        std::cout << " generique rouge" << std::endl;
    }

    void cas_bleu(Arbre* noeud)
    {
        std::cout << " generique bleu" << std::endl;
    }

private:
    // CRTP
    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }

    void noeud_val(Arbre* noeud)
    {
        if (noeud->fvalue == Arbre::Rouge)
        {
            derived().cas_rouge(noeud);
        }
        else if (noeud->fvalue == Arbre::Bleu)
        {
            derived().cas_bleu(noeud);
        }
        else exit(0);       
    }
    
};

/* Créer une spécialisation pour le visiteur générique et une autre 
pour un visiteur avec spécialisation sur le cas rouge
*/
class NormalVisitor : public GenericVisitor<NormalVisitor> {};

class RedVisitor : public GenericVisitor<RedVisitor>
{
public:
    void cas_rouge(Arbre* noeud)
    {
        std::cout << "rouge specification CRTP" << std::endl;
    }
};
   
int main()
{
    // Exemple simple d'utilisation de CRTP
    std::cout << "\nExemple simple d'utilisation de CRTP : " << std::endl;
    Fille f;
    f.interface();  // affiche implementation de Fille
    std::cout << "\n";
    //Exemple simplede mauvaise utilisation de CRTP
    std::cout << "Exemple simple d'une mauvaise utilisation de CRTP : " << std::endl;   
    Foo *foo1 = new Foo;
    Base1 *foo2 = foo1->copy(); // Que va afficher foo2?
    foo1->print();
    foo2->print(); 
    std::cout << "\n";
    // Définition des types rouge et blue pour déclarer des arbres
    Arbre::type red = Arbre::Rouge; 
    Arbre::type blue = Arbre::Bleu;
    Arbre n2(red),n3(red),n4(red),n5(red); 
    Arbre n1(blue,&n2,&n3);

    // Visiteur générique
    std::cout << "Visiteur generique :" << std::endl;
    NormalVisitor gv;
    gv.visit_1(&n1);
    std::cout << "\n";
    // Visiteur avec spécialisation sur rouge
    std::cout << "Visiteur rouge :" << std::endl;
    RedVisitor redv;
    redv.visit_1(&n1); 
}