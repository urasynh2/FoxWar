#include "Grille.hpp"
//#include "Coord.hpp"

using namespace std;

Grille::Grille(){
    for (int i=0; i < TAILLEGRILLE; i++){
        g[i].fill(Vide);                //on remplit l'ensemble des cases de la grille avec la valeur Vide valant -1
    }
}

bool Grille::caseVide(Coord c){
    return g[c.getLig()][c.getCol()] == Vide;
}

int Grille::getCase(Coord c){
    return g[c.getLig()][c.getCol()];
}

void Grille::videCase(Coord c){
    g[c.getLig()][c.getCol()] = Vide;
 
}

void Grille::setCase(Coord c, int a){
    g[c.getLig()][c.getCol()] = a;
}


    
void Grille::affiche(){
    for (int r = 0; r < TAILLEGRILLE;r++){
        for(int c = 0; c< TAILLEGRILLE;c++){
            cout<< g[r][c]<<"\t";
        }
        cout<<endl;
    }
}
