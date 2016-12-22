CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/max_calcul ${BIN}/nfork ${BIN}/chaine_proc ${BIN}/synchro_proc ${BIN}/kill_proc ${BIN}/stop_and_go


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



${BIN}/max_calcul: ${OBJ}/max_calcul.o ${OBJ}/max_func.o
	gcc -o ${BIN}/max_calcul ${OBJ}/max_calcul.o ${OBJ}/max_func.o

${OBJ}/max_calcul.o: ${SRC}/max_calcul.c ${SRC}/max_func.c 
	gcc -o ${OBJ}/max_calcul.o -c ${SRC}/max_calcul.c 

${OBJ}/max_func.o: ${SRC}/max_func.c
	gcc -o ${OBJ}/max_func.o -c ${SRC}/max_func.c -I${INC}


${BIN}/nfork: ${OBJ}/nfork.o
	gcc -o ${BIN}/nfork ${OBJ}/nfork.o

${OBJ}/nfork.o: ${SRC}/nfork.c
	gcc -o ${OBJ}/nfork.o -c ${SRC}/nfork.c 


${BIN}/chaine_proc: ${OBJ}/chaine_proc.o
	gcc -o ${BIN}/chaine_proc ${OBJ}/chaine_proc.o

${OBJ}/chaine_proc.o: ${SRC}/chaine_proc.c
	gcc -o ${OBJ}/chaine_proc.o -c ${SRC}/chaine_proc.c

#${BIN}/chaine_proc2: ${OBJ}/chaine_proc2.o
#	gcc -o ${BIN}/chaine_proc2 ${OBJ}/chaine_proc2.o

#${OBJ}/chaine_proc2.o: ${SRC}/chaine_proc2.c
#	gcc -o ${OBJ}/chaine_proc2.o -c ${SRC}/chaine_proc2.c


${BIN}/synchro_proc: ${OBJ}/synchro_proc.o
	gcc -o ${BIN}/synchro_proc ${OBJ}/synchro_proc.o

${OBJ}/synchro_proc.o: ${SRC}/synchro_proc.c
	gcc -o ${OBJ}/synchro_proc.o -c ${SRC}/synchro_proc.c 

${BIN}/kill_proc: ${OBJ}/kill_proc.o
	gcc -o ${BIN}/kill_proc ${OBJ}/kill_proc.o

${OBJ}/kill_proc.o: ${SRC}/kill_proc.c
	gcc -o ${OBJ}/kill_proc.o -c ${SRC}/kill_proc.c 

${BIN}/stop_and_go: ${OBJ}/stop_and_go.o
	gcc -o ${BIN}/stop_and_go ${OBJ}/stop_and_go.o

${OBJ}/stop_and_go.o: ${SRC}/stop_and_go.c
	gcc -o ${OBJ}/stop_and_go.o -c ${SRC}/stop_and_go.c 

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
