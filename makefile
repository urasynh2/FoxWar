#fichiers executables
test : test.o Ensemble.o Coord.o Animal.o Population.o Grille.o Jeu.o
	g++ -std=c++11 -g -Wall -o test test.o Ensemble.o Coord.o Animal.o Population.o Grille.o  Jeu.o

#fichiers objets

test.o : test.cpp
	g++ -std=c++11 -Wall -c test.cpp
	
Ensemble.o : Ensemble.hpp Ensemble.cpp 
	g++ -std=c++11 -Wall -c Ensemble.cpp

Coord.o : Coord.hpp Coord.cpp 
	g++ -std=c++11 -Wall -c Coord.cpp

Animal.o : Animal.hpp Animal.cpp 
	g++ -std=c++11 -Wall -c Animal.cpp
    
Population.o : Population.hpp Population.cpp 
	g++ -std=c++11 -Wall -c Population.cpp

    
Grille.o : Grille.hpp Grille.cpp 
	g++ -std=c++11 -Wall -c Grille.cpp
    
Jeu.o : Jeu.hpp Jeu.cpp 
	g++ -std=c++11 -Wall -c Jeu.cpp

clean :
	rm -f prog *.o core.* test img*.ppm *.gif
