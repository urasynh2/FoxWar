#ifndef POPULATION_HPP
#define POPULATION_HPP
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <exception>
#define Vide -1 
#include "Animal.hpp"

using namespace std;

struct Population{
    private :
        array<Animal*, TAILLEGRILLE*TAILLEGRILLE>pop;//Un tableau a 2dimensions de pointeurs vers des animaux
        int card;    //Cardinal
    public :
        Population(); //Constructeur
        Animal* get(int) const; //renvoie l’animal ayant un identifiant donné
        Ensemble getIds() const; //renvoie l’ensemble de tous les identifiants d’une population
        int reserve(); // réserve un identifiant libre et une place memoire pour un nouvel animal. 
		array<Animal*, TAILLEGRILLE*TAILLEGRILLE> getPop(); //renvoie le tableau 2d de la population
        void set(Animal*, int); //range un animal dans la population
        void supprime(int);    //supprime un animal de la population connaissant son identifiant
        int getCardRenard() const;  //renvoie le nombre de renard
        int getCardLapin() const;   //renvoie le nombre de lapin
		
};

#endif
