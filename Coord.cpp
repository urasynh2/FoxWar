#include "Coord.hpp"
using namespace std;

Coord::Coord(int lig, int col){
	if (not(0 <= lig and lig < TAILLEGRILLE) and (col >= 0 and col < TAILLEGRILLE)){
		throw invalid_argument("Coordonnées non valide");
	}else{
        this->lig = lig;
        this->col = col;
    }
}

bool operator==(Coord a, Coord b){
	return a.getLig()==b.getLig() and a.getCol()==b.getCol();
}

bool operator!=(Coord a, Coord b){
	return a.getLig() != b.getLig() or a.getCol()!=b.getCol();
}

int Coord::getLig(){
	return lig;
}

int Coord::getCol(){
	return col;
}

Coord::Coord(int n){
    this-> lig = n/TAILLEGRILLE;
    this-> col = n - (n/TAILLEGRILLE) * TAILLEGRILLE;
}

int Coord::toInt(){
    return lig*TAILLEGRILLE+col;
}

ostream& operator<<(ostream& out,Coord c){
	out << "(" << c.getLig() << "," << c.getCol() << ")";
	return out;
}

Ensemble Coord::voisines(){
    Ensemble ev = Ensemble();
    for(int i= max(lig-1, 0); i<=min(lig + 1, TAILLEGRILLE - 1); i++){
        for(int j= max(col-1, 0); j<=min(col + 1, TAILLEGRILLE - 1); j++){
            Coord c{i,j};
            if(c != Coord(lig, col)){
                ev.ajoute(c.toInt());
            }
        }
    }
    return ev;
}


