CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/thread_upper ${BIN}/thread_uppermax ${BIN}/producteur_consommateur ${BIN}/producteurs_consommateurs ${BIN}/signal_thread ${BIN}/thread_arborescent ${BIN}/thread_arborescent_sync #${BIN}/test
directories: ${OBJ} ${BIN} ${LIB} ${SRC} ${INC}

${OBJ}:
	mkdir ${OBJ}
${BIN}:
	mkdir ${BIN}
${LIB}:
	mkdir ${LIB}
${SRC}:
	mkdir ${SRC}
${INC}:
	mkdir ${INC}


${BIN}/thread_upper: ${OBJ}/thread_upper.o
	gcc -o ${BIN}/thread_upper ${OBJ}/thread_upper.o -l pthread

${OBJ}/thread_upper.o: ${SRC}/thread_upper.c
	gcc -o ${OBJ}/thread_upper.o -c ${SRC}/thread_upper.c  

${BIN}/thread_uppermax: ${OBJ}/thread_uppermax.o
	gcc -o ${BIN}/thread_uppermax ${OBJ}/thread_uppermax.o -l pthread

${OBJ}/thread_uppermax.o: ${SRC}/thread_uppermax.c
	gcc -o ${OBJ}/thread_uppermax.o -c ${SRC}/thread_uppermax.c

${BIN}/producteur_consommateur: ${OBJ}/producteur_consommateur.o
	gcc -o ${BIN}/producteur_consommateur ${OBJ}/producteur_consommateur.o -l pthread

${OBJ}/producteur_consommateur.o: ${SRC}/producteur_consommateur.c
	gcc -o ${OBJ}/producteur_consommateur.o -c ${SRC}/producteur_consommateur.c -I${INC}

${BIN}/producteurs_consommateurs: ${OBJ}/producteurs_consommateurs.o
	gcc -o ${BIN}/producteurs_consommateurs ${OBJ}/producteurs_consommateurs.o -l pthread

${OBJ}/producteurs_consommateurs.o: ${SRC}/producteurs_consommateurs.c
	gcc -o ${OBJ}/producteurs_consommateurs.o -c ${SRC}/producteurs_consommateurs.c

${BIN}/signal_thread: ${OBJ}/signal_thread.o
	gcc -o ${BIN}/signal_thread ${OBJ}/signal_thread.o -l pthread

${OBJ}/signal_thread.o: ${SRC}/signal_thread.c
	gcc -o ${OBJ}/signal_thread.o -c ${SRC}/signal_thread.c

${BIN}/thread_arborescent: ${OBJ}/thread_arborescent.o
	gcc -o ${BIN}/thread_arborescent ${OBJ}/thread_arborescent.o -l pthread

${OBJ}/thread_arborescent.o: ${SRC}/thread_arborescent.c
	gcc -o ${OBJ}/thread_arborescent.o -c ${SRC}/thread_arborescent.c

${BIN}/test: ${OBJ}/test.o
	gcc -o ${BIN}/test ${OBJ}/test.o -l pthread

${OBJ}/test.o: ${SRC}/test.c
	gcc -o ${OBJ}/test.o -c ${SRC}/test.c

${BIN}/thread_arborescent_sync: ${OBJ}/thread_arborescent_sync.o
	gcc -o ${BIN}/thread_arborescent_sync ${OBJ}/thread_arborescent_sync.o -l pthread

${OBJ}/thread_arborescent_sync.o: ${SRC}/thread_arborescent_sync.c
	gcc -o ${OBJ}/thread_arborescent_sync.o -c ${SRC}/thread_arborescent_sync.c


clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
