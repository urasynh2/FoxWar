#include "Animal.hpp"
#include "variable.hpp"
using namespace std;

Animal::Animal(int id, Coord coord, Espece espece, int foodLevel): 
id(id), coord(coord), espece(espece), foodLevel(foodLevel) {
}

int Animal::getId() const{
    return id;
}

Coord Animal::getCoord() const{
    return coord;
}
    
void Animal::setCoord(Coord c){
    coord = c;
}

Espece Animal::getEspece() const{
    return espece;
}

string Animal::toPixel() const{
    if(espece==Espece::Renard){
		return "255 165 0";
	}else {
		return "200 200 200";
	}
}

string Animal::toString() const{
    if(espece==Espece::Renard){
		return "○";
	}else {
		return "●";
	}
}

void Animal::addFL(int a){
    foodLevel+=a;
}

int Animal::getFL() const{
    return foodLevel;
}



bool Animal::meurt(){
    return foodLevel == 0;
}

bool Animal::seReproduit(int n){
	if(espece==Espece::Renard){
		if ((foodLevel > FoodReprod) and (rand()%100 < ProbBirthRenard*100)) {
			return true;
		}else{
			return false;
		}
	}else{
		if ((n>=MinFreeBirthLapin) and (rand()%100 < ProbBirthLapin*100)){
			return true;
		}else{
			return false;
		}
	}
}


void Animal::mange(){
    foodLevel += FoodLapin;
}
