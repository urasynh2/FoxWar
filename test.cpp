//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "Jeu.hpp"
#include <unistd.h>
#include <chrono>
#include <thread>
using namespace std;


void dessinefin(int c){
	ostringstream filename;
	filename << "img" << setfill('0') << setw(3) << c << ".ppm";
	ofstream fic(filename.str(), ios::out | ios::trunc);
	fic << "P3" << endl
    << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
    << 255 << " " << endl;
    for (int i=0; i<TAILLEGRILLE; i++){
		for (int j = 0; j < TAILLEGRILLE; j++){
				fic << "0 0 0"<< "    ";
		}
        fic<< endl;
    }
}

void start(int a){
	Jeu j =Jeu();
	j.verifieGrille();
    int c=0;
	j.afficheJeu();
    j.dessine(c);
	cout << "nombre de renard(○): " << j.getPop().getCardRenard() << endl;
    cout << "nombre de lapin(●): " << j.getPop().getCardLapin() << endl;
    while (j.getPop().getCardRenard() > 0 and j.getPop().getCardLapin() > 0 and c<a){
        for (int i = 0; i < TAILLEGRILLE*TAILLEGRILLE; i++){
			if (j.getPop().get(i) != nullptr and j.getPop().get(i)->getEspece() == Espece::Lapin){
                j.deplace(j.getPop().get(i));
            }
        }
		j.verifieGrille();
        for (int i = 0; i < TAILLEGRILLE*TAILLEGRILLE; i++){
            if (j.getPop().get(i) != nullptr and j.getPop().get(i)->getEspece() == Espece::Renard){
                j.deplace(j.getPop().get(i));
            }
        }
		j.verifieGrille();
		c++;
		j.afficheJeu();
		j.dessine(c);
		cout << "nombre de renard(○): " << j.getPop().getCardRenard() << endl;
		cout << "nombre de lapin(●):  " << j.getPop().getCardLapin() << endl;
		cout << "nombres de tours: " <<c << endl;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	c++;
	dessinefin(c);
}

TEST_CASE("Ensemble") {
	Ensemble e= Ensemble();
	CHECK(e.estVide());
	e.ajoute(5);
	e.ajoute(2);
	e.ajoute(6);
	CHECK_FALSE(e.estVide());
	//CHECK(e.tire() in (5,2,6));
}


TEST_CASE("Coordonnées") {
	Coord a = Coord(2,5);
	Coord b = Coord(5,2);
	CHECK_FALSE(a==b);
	CHECK(a!=b);
	CHECK(a.getLig()==2);
	CHECK(a.getCol()==5);
	CHECK(a.toInt()==75);  //pour TAILLEGRILLE=35
	CHECK(a==Coord(75));   //pour TAILLEGRILLE=35
	//CHECK(Coord(2,1).voisines()==Ensemble())
}

TEST_CASE("Animal") {
	Animal a = Animal(47, Coord(7,4), Espece::Renard, 0);
	Animal b = Animal(007, Coord(9,6), Espece::Lapin,5);
	CHECK(a.getId()==47);
	CHECK(b.getId()==007);
	CHECK(a.getCoord()==Coord(7,4));
	b.setCoord(Coord(6,8));
	CHECK(b.getCoord()==Coord(6,8));
	CHECK(a.getEspece()==Espece::Renard);
	CHECK(a.toPixel()=="255 165 0");
	//CHECK(a.toString()=="R");
	CHECK(a.toString()=="○");
	CHECK(a.meurt());
	a.addFL(3);
	CHECK(a.getFL()==3);
	a.mange();
	CHECK(a.getFL()==8);
}

TEST_CASE("Population"){
	Animal a = Animal(47, Coord(7,4), Espece::Renard, 0);
	Animal b = Animal(007, Coord(9,6), Espece::Lapin,5);
	Animal *r,*o;
	r=&a;
	o=&b;
	Population p= Population();
	p.set(r, 47);
	p.set(o, 007);
	CHECK(p.getCardRenard()==1);
	CHECK(p.getCardLapin()==1);
	Ensemble e= Ensemble();
	e.ajoute(47);
	e.ajoute(007);
	//CHECK(p.getIds()==e);
	p.supprime(47);
	Ensemble e2= Ensemble();
	e2.ajoute(007);
	//CHECK(p.getIds()==e2)
	CHECK(p.getCardRenard()==0);
}

TEST_CASE("Grille"){
	Grille g = Grille();
	CHECK(g.caseVide(Coord(4,7)));
	g.setCase(Coord(2,3), 47);
	CHECK_FALSE(g.caseVide(Coord(2,3)));
	CHECK(g.getCase(Coord(2,3))==47);
	g.videCase(Coord(2,3));
	CHECK(g.caseVide(Coord(2,3)));
}

TEST_CASE("Jeu"){
	Jeu j = Jeu();
	j.ajouteAnimal(Espece::Lapin, Coord(5,2));
	j.deplace(j.getPop().get(j.getGrille().getCase(Coord(5,2))));
	CHECK(j.verifieGrille());
}


int main(int argc, char **argv) {
	doctest::Context context(argc, argv);
	int res = context.run(); // run doctest
	if (context.shouldExit()) return res;

	srand(time(0));
	start(1000);
	system("convert -scale 300 -delay 10 img*.ppm movie.gif");
	system("rm -f prog img*.ppm");
    return 0;
}
