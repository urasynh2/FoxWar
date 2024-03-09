#ifndef GRILLE_HPP
#define GRILLE_HPP
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <exception>
#define Vide -1
#include "Population.hpp"

using namespace std;

class Grille{
    private :
        array<array<int, TAILLEGRILLE>, TAILLEGRILLE> g;  //Grille
    
    public : 
        Grille(); //Constructeur
        bool caseVide(Coord); //renvoie truesi la case est vide, et false sinon
        int getCase(Coord); //renvoie l’identifiant de l’animal au coordonnées données
        void videCase(Coord);  //vide une case connaissant ses coordonnées
        void setCase(Coord, int); //range un animal (par son identifiant) dans une case de coordonnées données.
        void affiche(); //affiche la grille
};
                              
#endif 