#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <exception>
#include "Coord.hpp"
//#include "variable.hpp"

using namespace std;

enum Espece {Renard, Lapin};

struct Animal{
    
    private :
		int id;      //Identifiant
		Coord coord; //Coordonnées
        Espece espece; //Espec
        int foodLevel; //Niveau de nourriture
    
    public :
        Animal(int, Coord, Espece, int); //Constructeur
        int getId() const;      //renvoie l’identifiant de l’animal
        Coord getCoord() const; //renvoie les coordonnées de l’animal
        void setCoord(Coord);  // change les coordonnées de l’animal
        Espece getEspece() const;  //renvoie l’espèce de l’animal
        string toPixel() const;  //convertit l’animal en couleur de caractères
        string toString() const;  //convertit l’animal en chaîne de caractères
        void addFL(int);      //ajoute un entier au niveau de nourriture
        int getFL() const;    //renvoie le niveau de nourriture
        bool meurt();    //renvoie true si l'animal meurt, false sinon
        bool seReproduit(int); //renvoie true si l'animal se reproduit, false sinon
        void mange(); //l'animal se nourrit et son niveau de nourriture augmente
};

#endif
