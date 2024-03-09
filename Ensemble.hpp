#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <exception>
#include <ctime>

using namespace std;

const int TAILLEGRILLE = 35;

int const MAXCARD = TAILLEGRILLE*TAILLEGRILLE;

class Ensemble{
	private:
		array<int, MAXCARD>t;  //Tableau d'entiers contenant les elements de l'ensemble
		int card;              //Cardinal
		
	public:
		Ensemble();      //Constructeur
		bool estVide();  //renvoie true ou false selon que l'ensemble est vide ou non.
		int getCard();   //renvoie le cardinal
		array<int, MAXCARD> getT(); //renvoie le tableau des elements
		void ajoute(int a);         //ajoute un entier a l'ensemble
        int tire();                 //tire un entier au hasard dans l'ensemble et le renvoie
    friend ostream& operator<<(ostream& out,Ensemble &e);
	friend bool operator==(Ensemble a, Ensemble b);
};


#endif
