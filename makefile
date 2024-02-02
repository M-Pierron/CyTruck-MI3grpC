# Cible par défaut : traitements 't' et 's'
all: allt alls

##----------------------------------------------------- traitement t -----------------------------------------------------##

# Compilation des fichiers objet pour le traitement 't'
allt: exect

etape.o : etape.c headert.h
	gcc -c etape.c -o etape.o

calcult.o : calcult.c headert.h
	gcc -c calcult.c -o calcult.o

ville.o : ville.c headert.h
	gcc -c ville.c -o ville.o

traitementt.o : traitementt.c headert.h
	gcc -c traitementt.c -o traitementt.o

# Création de l'exécutable 'exect' pour le traitement 't'
exect : etape.o calcult.o ville.o traitementt.o
	gcc traitementt.o etape.o calcult.o ville.o -o exect

##----------------------------------------------------- traitement s -----------------------------------------------------##

# Compilation des fichiers objet pour le traitement 's'
alls: execs

route.o : route.c headers.h
	gcc -c route.c -o route.o

calculs.o : calculs.c headers.h
	gcc -c calculs.c -o calculs.o

traitements.o : traitements.c headers.h
	gcc -c traitements.c -o traitements.o

# Création de l'exécutable 'execs' pour le traitement 's'
execs : calculs.o route.o traitements.o
	gcc traitements.o calculs.o route.o -o execs

##--------------------------------------------------------- global ---------------------------------------------------------##

# Suppression de tous les fichiers objets et des exécutables
clean:
	rm -f *.o exect execs
