CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/remonte_ipc ${BIN}/remonte_partagee ${BIN}/multi_remonte ${BIN}/multi_remonte_file_unique ${BIN}/wait_barrier ${BIN}/prod_conso_partagees

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


${BIN}/remonte_ipc: ${OBJ}/remonte_ipc.o
	gcc -o ${BIN}/remonte_ipc ${OBJ}/remonte_ipc.o

${OBJ}/remonte_ipc.o: ${SRC}/remonte_ipc.c
	gcc -o ${OBJ}/remonte_ipc.o -c ${SRC}/remonte_ipc.c

${BIN}/remonte_partagee: ${OBJ}/remonte_partagee.o
	gcc -o ${BIN}/remonte_partagee ${OBJ}/remonte_partagee.o

${OBJ}/remonte_partagee.o: ${SRC}/remonte_partagee.c
	gcc -o ${OBJ}/remonte_partagee.o -c ${SRC}/remonte_partagee.c

${BIN}/multi_remonte: ${OBJ}/multi_remonte.o
	gcc -o ${BIN}/multi_remonte ${OBJ}/multi_remonte.o

${OBJ}/multi_remonte.o: ${SRC}/multi_remonte.c
	gcc -o ${OBJ}/multi_remonte.o -c ${SRC}/multi_remonte.c

${BIN}/multi_remonte_file_unique: ${OBJ}/multi_remonte_file_unique.o
	gcc -o ${BIN}/multi_remonte_file_unique ${OBJ}/multi_remonte_file_unique.o

${OBJ}/multi_remonte_file_unique.o: ${SRC}/multi_remonte_file_unique.c
	gcc -o ${OBJ}/multi_remonte_file_unique.o -c ${SRC}/multi_remonte_file_unique.c

${BIN}/wait_barrier: ${OBJ}/wait_barrier.o
	gcc -o ${BIN}/wait_barrier ${OBJ}/wait_barrier.o

${OBJ}/wait_barrier.o: ${SRC}/wait_barrier.c
	gcc -o ${OBJ}/wait_barrier.o -c ${SRC}/wait_barrier.c

${BIN}/prod_conso_partagees: ${OBJ}/prod_conso_partagees.o
	gcc -o ${BIN}/prod_conso_partagees ${OBJ}/prod_conso_partagees.o -lpthread

${OBJ}/prod_conso_partagees.o: ${SRC}/prod_conso_partagees.c
	gcc -o ${OBJ}/prod_conso_partagees.o -c ${SRC}/prod_conso_partagees.c


clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
