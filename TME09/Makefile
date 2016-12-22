2CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: directories ${BIN}/notifier_async ${BIN}/suspendre_async ${BIN}/temporiser_async ${BIN}/remonte_async ${BIN}/inverseur_async ${BIN}/creation_tr ${BIN}/remonte_signal ${BIN}/signale_barriere

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


${BIN}/notifier_async: ${OBJ}/notifier_async.o
	gcc -o ${BIN}/notifier_async ${OBJ}/notifier_async.o -lrt

${OBJ}/notifier_async.o: ${SRC}/notifier_async.c
	gcc -o ${OBJ}/notifier_async.o -c ${SRC}/notifier_async.c

${BIN}/suspendre_async: ${OBJ}/suspendre_async.o
	gcc -o ${BIN}/suspendre_async ${OBJ}/suspendre_async.o -lrt

${OBJ}/suspendre_async.o: ${SRC}/suspendre_async.c
	gcc -o ${OBJ}/suspendre_async.o -c ${SRC}/suspendre_async.c

${BIN}/temporiser_async: ${OBJ}/temporiser_async.o
	gcc -o ${BIN}/temporiser_async ${OBJ}/temporiser_async.o -lrt

${OBJ}/temporiser_async.o: ${SRC}/temporiser_async.c
	gcc -o ${OBJ}/temporiser_async.o -c ${SRC}/temporiser_async.c

${BIN}/remonte_async: ${OBJ}/remonte_async.o
	gcc -o ${BIN}/remonte_async ${OBJ}/remonte_async.o -lrt

${OBJ}/remonte_async.o: ${SRC}/remonte_async.c
	gcc -o ${OBJ}/remonte_async.o -c ${SRC}/remonte_async.c

${BIN}/inverseur_async: ${OBJ}/inverseur_async.o
	gcc -o ${BIN}/inverseur_async ${OBJ}/inverseur_async.o -lrt

${OBJ}/inverseur_async.o: ${SRC}/inverseur_async.c
	gcc -o ${OBJ}/inverseur_async.o -c ${SRC}/inverseur_async.c

${BIN}/creation_tr: ${OBJ}/creation_tr.o
	gcc -o ${BIN}/creation_tr ${OBJ}/creation_tr.o -lrt

${OBJ}/creation_tr.o: ${SRC}/creation_tr.c
	gcc -o ${OBJ}/creation_tr.o -c ${SRC}/creation_tr.c

${BIN}/remonte_signal: ${OBJ}/remonte_signal.o
	gcc -o ${BIN}/remonte_signal ${OBJ}/remonte_signal.o -lrt

${OBJ}/remonte_signal.o: ${SRC}/remonte_signal.c
	gcc -o ${OBJ}/remonte_signal.o -c ${SRC}/remonte_signal.c

${BIN}/signale_barriere: ${OBJ}/signale_barriere.o
	gcc -o ${BIN}/signale_barriere ${OBJ}/signale_barriere.o -lrt

${OBJ}/signale_barriere.o: ${SRC}/signale_barriere.c
	gcc -o ${OBJ}/signale_barriere.o -c ${SRC}/signale_barriere.c


clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
