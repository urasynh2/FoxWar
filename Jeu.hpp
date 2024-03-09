#ifndef JEU_HPP
#define JEU_HPP
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <exception>
#include <iomanip> 
#include <sstream> 
#include <fstream>
#include <string>
#include "Grille.hpp"

using namespace std;

class Jeu{
    private :
        Grille grille;  //Grille
        Population pop; //Population
    public :
        Jeu();  //Constructeur 
        void dessine(int c);  //Cree une image avec les lapins en gris et les renard en orange 
        Grille getGrille();  //renvoie la grille
        Population getPop();  //renvoie la population
        void ajouteAnimal(Espece, Coord); //crée un animal d'espece donnée et le place au coordonnées données
        bool verifieGrille();  //vérifie que chaque animal est bien àsa place dans la grille
        Ensemble voisinsVide(Coord c); //retourne l’ensemble des cases voisines vides d’une case
        Ensemble voisinsLapin(Coord c); //retourne l’ensemble des cases voisines contenant des lapins 
        void deplace(Animal*); //déplace l’animal sur une case voisine libre et le range dans la grille
        void afficheJeu();  //affiche l'etat du jeu
};

#endif



