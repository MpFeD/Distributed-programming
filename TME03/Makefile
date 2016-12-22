CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/thread_create ${BIN}/thread_rand ${BIN}/thread_wait ${BIN}/thread_detach ${BIN}/thread_setdetach ${BIN}/thread_broadcast


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


${BIN}/thread_create: ${OBJ}/thread_create.o
	gcc -o ${BIN}/thread_create ${OBJ}/thread_create.o -l pthread

${OBJ}/thread_create.o: ${SRC}/thread_create.c
	gcc -o ${OBJ}/thread_create.o -c ${SRC}/thread_create.c  

${BIN}/thread_rand: ${OBJ}/thread_rand.o
	gcc -o ${BIN}/thread_rand ${OBJ}/thread_rand.o -l pthread 

${OBJ}/thread_rand.o: ${SRC}/thread_rand.c
	gcc -o ${OBJ}/thread_rand.o -c ${SRC}/thread_rand.c

${BIN}/thread_wait: ${OBJ}/thread_wait.o
	gcc -o ${BIN}/thread_wait ${OBJ}/thread_wait.o -l pthread 

${OBJ}/thread_wait.o: ${SRC}/thread_wait.c
	gcc -o ${OBJ}/thread_wait.o -c ${SRC}/thread_wait.c

${BIN}/thread_detach: ${OBJ}/thread_detach.o
	gcc -o ${BIN}/thread_detach ${OBJ}/thread_detach.o -l pthread 

${OBJ}/thread_detach.o: ${SRC}/thread_detach.c
	gcc -o ${OBJ}/thread_detach.o -c ${SRC}/thread_detach.c

${BIN}/thread_setdetach: ${OBJ}/thread_setdetach.o
	gcc -o ${BIN}/thread_setdetach ${OBJ}/thread_setdetach.o -l pthread 

${OBJ}/thread_setdetach.o: ${SRC}/thread_setdetach.c
	gcc -o ${OBJ}/thread_setdetach.o -c ${SRC}/thread_setdetach.c

${BIN}/thread_broadcast: ${OBJ}/thread_broadcast.o
	gcc -o ${BIN}/thread_broadcast ${OBJ}/thread_broadcast.o -l pthread 

${OBJ}/thread_broadcast.o: ${SRC}/thread_broadcast.c
	gcc -o ${OBJ}/thread_broadcast.o -c ${SRC}/thread_broadcast.c

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
