#include "Population.hpp"

using namespace std;

Population::Population() : card(0) {
    pop.fill(nullptr);                 //remplit le tableau de la population de pointeurs NULL
}

Animal* Population::get(int a) const{
    for (int i = 0; i < TAILLEGRILLE*TAILLEGRILLE; i++){   //parcourt l'ensemble de la population
        if(pop[i]!=nullptr){                               //verifie si le pointeur ne pointe pas vers NULL, donc si la case n'est pas vide
            if (pop[i]->getId() == a){                     // regarde si l'identifiant correspondant à l'animal vaut a
                return pop[i];                             //renvoie l'animal
            }
        }
    }
     return nullptr;                 //renvoie un pointeur NULL
}

Ensemble Population::getIds() const{
	Ensemble res = Ensemble();  
	for (int i = 0; i < TAILLEGRILLE*TAILLEGRILLE; i++){
        if (pop[i] != nullptr){
            res.ajoute(pop[i]->getId());
        }
    }
    return res;
}

int Population::reserve(){
    int res;
    for (int i = 0; i < TAILLEGRILLE*TAILLEGRILLE;i++){     //parcourt l'ensemble de la population
        if (pop[i] == nullptr){                             //teste si le pointeur est NULL, donc si la case est vide
            pop[i] = (Animal*) malloc(sizeof(Animal));      //alloue la mémoire nécessaie à un Animal
            res = i;                             //affecte au résultat l'identifiant correspondant à l'indice dans le tableau de l'élement
            break;
        }
    }
    return res;           //renvoie l'identifiant nouvellement attribué
}


void Population::set(Animal* a, int id){
    pop[id] = a;     //range l'animal a d'identifiant id à l'indice id dans le tableau
    card ++;         //le cardinal de la population augmente d'un élément
}



void Population::supprime(int p){
    for (int i = 0; i<TAILLEGRILLE*TAILLEGRILLE; i++){      //parcourt l'ensemble de la population
        if(pop[i]!=nullptr){                                //teste si l'élement ne pointe pas vers NULL, donc si la case contient un Animal
            if (pop[i]->getId() == p){                      //teste si l'identifiant de l'Animal correspond à p
                pop[i] = nullptr;                           //affecte à l'élément le pointeur NULL
                free(pop[i]);                               //libère la mémoire précedemment allouée
                return;
            }
        }
    }
}

int Population::getCardRenard() const {
    int val = 0;
    for (int p = 0; p < TAILLEGRILLE * TAILLEGRILLE; p++) {
        if (pop[p] != nullptr and pop[p]->getEspece() == Espece::Renard) {
            val += 1;
        }
    }
    return val;
}
int Population::getCardLapin() const {
    int val = 0;
    for (int p = 0; p < TAILLEGRILLE * TAILLEGRILLE; p++) {
        if (pop[p] != nullptr and pop[p]->getEspece() == Espece::Lapin) {
            val += 1;
        }
    }
    return val;
}
