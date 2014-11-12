// -----------------------TP 1 C++ ------------------------//
// Compiler avec l'option -std=c++11
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
/*
CRTP (Curiously recurring Template pattern) :
C'est l'équivalent ( mais à la compilation) de private/protected appliqué à des fonctions 
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
//template <typename >


struct Arbre
{
    enum type {Rouge, Bleu};
    Arbre *fils0;
    Arbre *fils1;
    type maValeur;

    Arbre(type t1, Arbre *a0=NULL, Arbre *a1=NULL)
    {
        maValeur = t1;
        this->fils0 = a0;
        this->fils1 = a1;
    }
};

/* Ecrire une classe générique de visiteur permettant de visiter l'arbre dans l'ordre 
de votre choix en utilisant CRTP :
    - inclure une fonction pour visiter l'arbre qui affichera la couleur du noeud courant
    et parcours ensuite les suivant ( ou dans un autre ordre)
    - une fonction d'affichage pour le cas rouge et une pour bleu
    - le CRTP 
*/

template <class Derived>
class GenericVisitor
{
    public:
        void visit_1(Arbre *a)
        {
            noeud_val(a);
            if(a->fils0 != NULL){
                visit_1(a->fils0);
            }
            if(a->fils1 != NULL){
                visit_1(a->fils1);
            }
        }

        void cas_rouge(){std::cout << "Je suis Rouge !" << std::endl;}
        void cas_bleu(){std::cout << "Je suis Bleu !" << std::endl;}

    private:
    // CRTP
        Derived & derived()
        {
            return *static_cast<Derived *>(this);
        }
        // analyse la valeur d'un noeud
        void noeud_val(Arbre* noeud)
        {
            if(noeud->maValeur == Arbre::Bleu){
                cas_bleu();
            }
            else if(noeud->maValeur == Arbre::Rouge){
                derived().cas_rouge();
            }
        }    
};

/* Créer une spécialisation pour le visiteur générique et une autre 
pour un visiteur avec spécialisation sur le cas rouge
*/
 class NormalVisitor : public GenericVisitor<NormalVisitor> {};

class RedVisitor : public GenericVisitor<RedVisitor>
{
    public:
        void cas_rouge(){
            std::cout << "Je suis Rouge mais avec du caca !" << std::endl;
        }  
};
   
int main()
{
    // Exemple simple d'utilisation de CRTP
    std::cout << "\nExemple simple d'utilisation de CRTP : " << std::endl;
    Fille f;
    f.interface();  // affiche implementation de Fille
    std::cout << "\n";
    //Exemple simple de mauvaise utilisation de CRTP
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