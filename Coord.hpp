#ifndef COORD_HPP
#define COORD_HPP
#include <vector>
#include <array>
#include <string>
#include <exception>
#include <iostream>

using namespace std;

#include "Ensemble.hpp"

class Coord{
	
	public :
        Coord(int);      //Constructeur a partir d'un entier
		Coord(int, int); //Constructeur a partit de 2 entiers
		int getLig();    //renvoie la ligne
		int getCol();    //renvoie la colonne
		int toInt();     //convertie la coordonnée en entier
		Ensemble voisines();  //renvoie l'ensemble des coordonnées voisines
	
	private :
		int lig;   //Ligne
		int col;   //Colonne

};


bool operator==(Coord a, Coord b);

bool operator!=(Coord a, Coord b);

ostream& operator<<(ostream& out,Coord c);



#endif







