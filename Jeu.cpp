#include "Jeu.hpp"

using namespace std;

int RatioInitLapin = 20;
int RatioInitRenard = 7;
int FoodInit = 5;
int MaxFood = 10;

Jeu::Jeu(): pop {} {                 
    int h;
    for (int i=0; i < TAILLEGRILLE; i++){               //parcourt la grille
        for (int j=0; j < TAILLEGRILLE; j++){
            h = rand()%99;                              // affecte à h une valeur aleatoire entre 0 et 99
            Coord c {i,j};
            if (h<RatioInitLapin){                      //ajoute un lapin et le place dans la grille aux coordonnées c si la valeur est en 
                ajouteAnimal(Espece::Lapin, c);         //dessous de 20 (20% de chance)
            }else if(h<RatioInitLapin+RatioInitRenard){ //ajoute un renard et le place dans la grille aux coordonnées c
                ajouteAnimal(Espece::Renard, c);        //si la valeur est en dessous de 27 (7% de chance)
            }else{
                grille.videCase(c);                //vide la case, il n'y a donc aucun animal dans cette case de la grille
            }
        }
    }
}

Grille Jeu::getGrille(){
    return grille;
}

Population Jeu::getPop(){
    return pop;
}

void Jeu::ajouteAnimal(Espece e, Coord c){
    int id = pop.reserve();
    grille.setCase(c, id);
    Animal *a = new Animal (id, c, e, FoodInit);
    pop.set(a, id);
}


void Jeu::afficheJeu(){
	system("clear");
	if (TAILLEGRILLE<=10){
		cout<<" ";
		for(int i=0; i<TAILLEGRILLE; i++){
			cout << " "<< i<< " ";
		}
	}else{
		cout<<" ";
		for(int i=0; i<10; i++){
			cout << " "<< i<< " ";
		}
		for(int i=10; i<TAILLEGRILLE; i++){
			cout << i<< " ";
		}
	}
    cout<<" "<<endl;
    for (int i=0; i<TAILLEGRILLE; i++){
		cout<< i;
        for (int j = 0; j < TAILLEGRILLE; j++){
            Coord c {i, j};
            int id = grille.getCase(c);
            if (id == -1){
                cout << "   ";
            }else{
                cout <<" "<< pop.get(id)->toString()<<" ";

            }
        }
        cout << endl;
        for(int i=0; i<TAILLEGRILLE * 4; i++){
            cout << " ";
        }     
        cout<<" "<<endl;
    }
}

void Jeu::dessine(int c){
	ostringstream filename;
	filename << "img" << setfill('0') << setw(3) << c << ".ppm";
	cout << "Ecriture dans le fichier : " << filename.str() << endl;
	ofstream fic(filename.str(), ios::out | ios::trunc);
	fic << "P3" << endl
    << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
    << 255 << " " << endl;
    for (int i=0; i<TAILLEGRILLE; i++){
		for (int j = 0; j < TAILLEGRILLE; j++){
			Coord c {i, j};
			int id = grille.getCase(c);
			if (id == -1){
				fic << "47 127 77"<< "    ";;
			}else{
				fic<< pop.get(id)->toPixel()<< "    ";
			}
		}
        fic<< endl;
    }
}
    

bool Jeu::verifieGrille(){
    for(int i=0; i<TAILLEGRILLE ; i++){            //parcourt la grille
        for(int j=0; j<TAILLEGRILLE ; j++){
            Coord c{i,j};                 
            int id = grille.getCase(c);            //affecte à id l'identifiant de la case de coordonnées c
            if(id != -1){                          //vérifie que la case n'est pas vide
                if( pop.get(id)->getCoord() != c){ //si les coordonnées dans la population ne correspondent pas aux coordonnées dans la
                    return false;                  //grille, renvoie false
                }
            }
        }
    }
    return true;                       //si la grille est parcourue sans problème, renvoie true
}

Ensemble Jeu::voisinsVide(Coord c){
    Ensemble res= Ensemble();          //initialise le résultat sous forme d'un ensemble vide
    Ensemble v = c.voisines();         //récupère les cases voisines de la case de coordonnées prises en paramètres
    array<int, MAXCARD> tab= v.getT(); //récupère les valeurs de l'ensemble
    for(int i=0; i< v.getCard();i++){  //parcourt le tableau
        if(grille.caseVide(Coord(tab[i]))){ //si la case est vide
            res.ajoute(tab[i]);             //alors ajoute l'élement à l'ensemble résultat
        }
    }
    return res;                           //renvoie l'ensemble résultat
}
          
Ensemble Jeu::voisinsLapin(Coord c){
    Ensemble res=Ensemble();           //initialise le résultat sous forme d'un ensemble vide
    Ensemble v = c.voisines();         //récupère les cases voisines de la case de coordonnées prises en paramètres
    array<int, MAXCARD> tab= v.getT(); //récupère les valeurs de l'ensemble
    for(int i=0; i < v.getCard();i++){ //parcourt le tableau
        if(not (grille.caseVide(Coord(tab[i]))) and pop.get(grille.getCase(Coord(tab[i])))->getEspece() == Espece::Lapin){ // si la case     
            res.ajoute(tab[i]); //n'est pas vide et qu'elle contient un lapin, alors ajoute l'élement à l'ensemble résultat
        }
    }
    return res;                 //renvoie l'ensemble résultat
}






void Jeu::deplace(Animal *a){
    Ensemble e_vide = voisinsVide(a->getCoord());                //récupère l'ensemble des cases voisines vides de l'animal a
    Ensemble e_lap = voisinsLapin(a->getCoord());                //récupère l'ensemble de cases voisines de l'animal a contenant des lapins
    if (a->getEspece() == Espece::Lapin){                        //si l'animal est un lapin
        if (e_vide.getCard() > 0){                               //s'il y a des cases voisines vides
            Coord caseDepart = a->getCoord();                    //affecte à une variable les coordonnées de départ
            int caseArrivee = e_vide.tire();                     //tire dans l'ensemble des cases voisines vides un élément
            grille.videCase(a->getCoord());                      //On vide la case de départ
            a->setCoord(Coord(caseArrivee));                     //On remplace les coordonnées du lapin avec celles d'arrivées
            grille.setCase(a->getCoord(), a->getId());           //On place l'identifiant du lapin dans la grille à sa nouvelle place
            if (a->seReproduit(e_vide.getCard())){               //si le lapin peut se reproduire
                ajouteAnimal(Espece::Lapin, caseDepart);         //placer un nouveau lapin aux coordonnées de départ
            }
        }
    }else{                                                      //si l'animal est un renard
        a->addFL(-1);                                           //diminuer son niveau de nourriture de 1
        if(not(a->meurt())){                                    //s'il ne meurt pas
            if (e_lap.getCard() >= 1 and not(a->getFL() >= MaxFood)){   //S'il y a des lapins autour du renard et qu'il n'est pas rassasié 
                Coord caseDepart = a->getCoord();                       //affecte à une variable les coordonnées de départ
                int caseArrivee = e_lap.tire();                      //tire dans l'ensemble des cases voisines contenant un lapin un élément
                pop.supprime(grille.getCase( Coord(caseArrivee) ));     //On supprimme le lapin qui se fait manger
                grille.videCase(a->getCoord());                         //On vide la case de depart du renard
                a->setCoord(Coord(caseArrivee));                        //On change les coordonnées du renard au coordonnes d'arrivées
                grille.setCase(a->getCoord(), a->getId());            //On place l'identifiant du renard dans la grille a sa nouvelle place
                a->mange();                                           //On augmente son niveau de nourriture de 5
                if (a->seReproduit(0)){                               //si le renard peut se reproduire
                    ajouteAnimal(Espece::Renard, caseDepart);         //placer un nouveau renard aux coordonnées de départ
                }
            }else if (e_vide.getCard()  >= 1){ //s'il n'y a pas de lapins autour du renard, vérifie s'il y a des cases vides atour du renard
                    int caseArrivee = e_vide.tire();   //tire dans l'ensemble des cases voisines vides un élément
                    grille.videCase(a->getCoord());    //On vide la case de départ
                    a->setCoord(Coord(caseArrivee));   //On remplace les coordonnées du renard avec celles d'arrivées
                    grille.setCase(a->getCoord(), a->getId());     //On place l'identifiant du renard dans la grille à sa nouvelle place
                }
        }else{                                                  //s'il meurt
            grille.videCase(a->getCoord());                     //Le retirer de la grille
            pop.supprime(a->getId());                           //le retirer de la population
        }
    }
}
