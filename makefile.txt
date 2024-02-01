##----------------------------------------------------- traitement t -----------------------------------------------------##
# -- Toutes les cibles seront executées en même temps --
allt: exect

etape.o : etape.c headert.h
	gcc -c etape.c -o etape.o

calcult.o : calcult.c headert.h
	gcc -c calcult.c -o calcult.o

ville.o : ville.c headert.h
	gcc -c ville.c -o ville.o

traitementt.o : traitementt.c headert.h
	gcc -c traitementt.c -o traitementt.o

exect : etape.o calcult.o ville.o traitementt.o
	gcc traitementt.o etape.o calcult.o ville.o -o exect


##----------------------------------------------------- traitement s -----------------------------------------------------##
# -- Toutes les cibles seront executées en même temps --
alls: execs

route.o : route.c headers.h
	gcc -c route.c -o route.o

calculs.o : calculs.c headers.h
	gcc -c calculs.c -o calculs.o

traitements.o : traitements.c headers.h
	gcc -c traitements.c -o traitements.o

execs : calculs.o route.o traitements.o
	gcc traitements.o calculs.o route.o -o execs


##--------------------------------------------------------- global ---------------------------------------------------------##
# -- Supprime tous les fichiers objects
clean:
	rm -f *.o
	rm exect
