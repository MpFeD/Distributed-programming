CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/forkwrite ${BIN}/forkfilemax ${BIN}/mycp ${BIN}/remonte ${BIN}/lectures ${BIN}/extended-grep  ${BIN}/inverser-fichier ${BIN}/inverser-pread



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


${BIN}/forkwrite: ${OBJ}/forkwrite.o
	gcc -o ${BIN}/forkwrite ${OBJ}/forkwrite.o

${OBJ}/forkwrite.o: ${SRC}/forkwrite.c
	gcc -o ${OBJ}/forkwrite.o -c ${SRC}/forkwrite.c 

${BIN}/forkfilemax: ${OBJ}/forkfilemax.o
	gcc -o ${BIN}/forkfilemax ${OBJ}/forkfilemax.o

${OBJ}/forkfilemax.o: ${SRC}/forkfilemax.c
	gcc -o ${OBJ}/forkfilemax.o -c ${SRC}/forkfilemax.c 

${BIN}/mycp: ${OBJ}/mycp.o
	gcc -o ${BIN}/mycp ${OBJ}/mycp.o

${OBJ}/mycp.o: ${SRC}/mycp.c
	gcc -o ${OBJ}/mycp.o -c ${SRC}/mycp.c 

${BIN}/remonte: ${OBJ}/remonte.o
	gcc -o ${BIN}/remonte ${OBJ}/remonte.o

${OBJ}/remonte.o: ${SRC}/remonte.c
	gcc -o ${OBJ}/remonte.o -c ${SRC}/remonte.c 

${BIN}/lectures: ${OBJ}/lectures.o
	gcc -o ${BIN}/lectures ${OBJ}/lectures.o

${OBJ}/lectures.o: ${SRC}/lectures.c
	gcc -o ${OBJ}/lectures.o -c ${SRC}/lectures.c 

${BIN}/extended-grep: ${OBJ}/extended-grep.o
	gcc -o ${BIN}/extended-grep ${OBJ}/extended-grep.o

${OBJ}/extended-grep.o: ${SRC}/extended-grep.c
	gcc -o ${OBJ}/extended-grep.o -c ${SRC}/extended-grep.c 

${BIN}/inverser-fichier: ${OBJ}/inverser-fichier.o
	gcc -o ${BIN}/inverser-fichier ${OBJ}/inverser-fichier.o

${OBJ}/inverser-fichier.o: ${SRC}/inverser-fichier.c
	gcc -o ${OBJ}/inverser-fichier.o -c ${SRC}/inverser-fichier.c 

${BIN}/inverser-pread: ${OBJ}/inverser-pread.o
	gcc -o ${BIN}/inverser-pread ${OBJ}/inverser-pread.o

${OBJ}/inverser-pread.o: ${SRC}/inverser-pread.c
	gcc -o ${OBJ}/inverser-pread.o -c ${SRC}/inverser-pread.c 




clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
