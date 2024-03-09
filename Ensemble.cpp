#include "Ensemble.hpp"

using namespace std;

Ensemble::Ensemble(){
	card = 0;
}


int Ensemble::getCard(){
	return card;
}

array<int, MAXCARD> Ensemble::getT(){
	return t;
}

ostream& operator<<(ostream& out,Ensemble &e){
    if (e.estVide()){
        out << "{}";
        return out;
    }
	out << "{";
	for (int i=0; i<e.getCard()-1; i++){
		out << e.t[i] << ",";
	}	
    out << e.t[e.getCard()-1] << "}";
    return out;
}

bool operator==(Ensemble a, Ensemble b){
	return a.getT() == b.getT() and a.getCard()==b.getCard();
}

bool Ensemble::estVide(){
	return card==0;
}

void Ensemble::ajoute(int a){
    if (card < MAXCARD){
        t[card] = a;
        card ++;
    }else{
        throw runtime_error("ensemble plein");
    }
}

int Ensemble::tire(){
    int indice, res;
    indice = rand()%card;
    res = t[indice];
    for (int i = indice; i < card; i++){
    t[i] = t[i+1];
    }
    card--;
    return res;
}




