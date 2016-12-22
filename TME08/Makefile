2CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: directories ${BIN}/ftp_multi_server ${BIN}/ftp_multi_client ${BIN}/journal_client ${BIN}/journal_serveur ${BIN}/sonar ${BIN}/ponger ${BIN}/mychat

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


${BIN}/ftp_multi_server: ${OBJ}/ftp_multi_server.o
	gcc -o ${BIN}/ftp_multi_server ${OBJ}/ftp_multi_server.o

${OBJ}/ftp_multi_server.o: ${SRC}/ftp_multi_server.c
	gcc -o ${OBJ}/ftp_multi_server.o -c ${SRC}/ftp_multi_server.c

${BIN}/ftp_multi_client: ${OBJ}/ftp_multi_client.o
	gcc -o ${BIN}/ftp_multi_client ${OBJ}/ftp_multi_client.o

${OBJ}/ftp_multi_client.o: ${SRC}/ftp_multi_client.c
	gcc -o ${OBJ}/ftp_multi_client.o -c ${SRC}/ftp_multi_client.c

${BIN}/journal_client: ${OBJ}/journal_client.o
	gcc -o ${BIN}/journal_client ${OBJ}/journal_client.o

${OBJ}/journal_client.o: ${SRC}/journal_client.c
	gcc -o ${OBJ}/journal_client.o -c ${SRC}/journal_client.c

${BIN}/journal_serveur: ${OBJ}/journal_serveur.o
	gcc -o ${BIN}/journal_serveur ${OBJ}/journal_serveur.o

${OBJ}/journal_serveur.o: ${SRC}/journal_serveur.c
	gcc -o ${OBJ}/journal_serveur.o -c ${SRC}/journal_serveur.c

${BIN}/sonar: ${OBJ}/sonar.o
	gcc -o ${BIN}/sonar ${OBJ}/sonar.o -lpthread -lrt

${OBJ}/sonar.o: ${SRC}/sonar.c
	gcc -o ${OBJ}/sonar.o -c ${SRC}/sonar.c

${BIN}/ponger: ${OBJ}/ponger.o
	gcc -o ${BIN}/ponger ${OBJ}/ponger.o

${OBJ}/ponger.o: ${SRC}/ponger.c
	gcc -o ${OBJ}/ponger.o -c ${SRC}/ponger.c

${BIN}/mychat: ${OBJ}/mychat.o
	gcc -o ${BIN}/mychat ${OBJ}/mychat.o -lpthread -lrt

${OBJ}/mychat.o: ${SRC}/mychat.c
	gcc -o ${OBJ}/mychat.o -c ${SRC}/mychat.c

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
