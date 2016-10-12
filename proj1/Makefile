# Merci à INF224 pour ce makefile

##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du programme
#
PROG = friendly-computing-machine

#
# Fichiers sources (NE PAS METTRE les .h ni les .o seulement les .cpp)
#
SOURCES = src/addition.c \
		  src/multiplication.c
		  #src/main.c

#
# Fichiers objets (ne pas modifier sauf si l'extension n'est pas .cpp)
#
OBJETS = ${SOURCES:%.c=%.o}

#
# Compilateur C
#
CC  = clang

#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
# Example: CXXFLAGS= -std=c++11 -Wall -O -I/usr/local/qt/include
#
CFLAGS = -std=c11 -Wall -g -Wextra -Wpedantic 

#
# Options de l'editeur de liens
#
LDFLAGS = -lm

#
# Librairies a utiliser
# Example: LDLIBS = -L/usr/local/qt/lib -lqt
#
LDLIBS = 


##########################################
#
# Regles de construction/destruction des .o et de l'executable
# depend-${PROG} sera un fichier contenant les dependances
#
 
all: ${PROG}

run: ${PROG}
	./${PROG}

${PROG}: addition multiplication

clean:
	-@$(RM) src/*.o core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${PROG} 1>/dev/null 2>&1
  
tar:
	tar cvf ${PROG}.tar.gz ${SOURCES}


addition: src/addition.o
	${CC} -o $@ ${LDFLAGS} $<

multiplication: src/multiplication.o
	${CC} -o $@ ${LDFLAGS} $<



test: tests-addition

tests-addition: addition tests-unit
	@echo "== LANCEMENT DES TESTS UNITAIRES"
	@echo ""
	@./tests-unit
	@echo ""
	@echo "== TOUS LES TESTS SONT PASSES"
	make -f addition.tests

tests-multiplication: multiplication
	make -f multiplication.tests

tests-unit: src/tests.o src/addition.o 
	${CC} -o $@ ${LDFLAGS} $<




###########################################
#
# Regles implicites
#

.SUFFIXES: .c

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<
