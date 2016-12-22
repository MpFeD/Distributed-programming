2CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: directories ${BIN}/remonte_udp ${BIN}/recvfile ${BIN}/sendfile ${BIN}/env_serveur ${BIN}/env_client ${BIN}/ftp_server ${BIN}/ftp_client

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

${BIN}/remonte_udp: ${OBJ}/remonte_udp.o
	gcc -o ${BIN}/remonte_udp ${OBJ}/remonte_udp.o

${OBJ}/remonte_udp.o: ${SRC}/remonte_udp.c
	gcc -o ${OBJ}/remonte_udp.o -c ${SRC}/remonte_udp.c

${BIN}/recvfile: ${OBJ}/recvfile.o
	gcc -o ${BIN}/recvfile ${OBJ}/recvfile.o

${OBJ}/recvfile.o: ${SRC}/recvfile.c
	gcc -o ${OBJ}/recvfile.o -c ${SRC}/recvfile.c

${BIN}/sendfile: ${OBJ}/sendfile.o
	gcc -o ${BIN}/sendfile ${OBJ}/sendfile.o

${OBJ}/sendfile.o: ${SRC}/sendfile.c
	gcc -o ${OBJ}/sendfile.o -c ${SRC}/sendfile.c

${BIN}/env_serveur: ${OBJ}/env_serveur.o
	gcc -o ${BIN}/env_serveur ${OBJ}/env_serveur.o

${OBJ}/env_serveur.o: ${SRC}/env_serveur.c
	gcc -o ${OBJ}/env_serveur.o -c ${SRC}/env_serveur.c

${BIN}/env_client: ${OBJ}/env_client.o
	gcc -o ${BIN}/env_client ${OBJ}/env_client.o

${OBJ}/env_client.o: ${SRC}/env_client.c
	gcc -o ${OBJ}/env_client.o -c ${SRC}/env_client.c

${BIN}/ftp_server: ${OBJ}/ftp_server.o
	gcc -o ${BIN}/ftp_server ${OBJ}/ftp_server.o

${OBJ}/ftp_server.o: ${SRC}/ftp_server.c
	gcc -o ${OBJ}/ftp_server.o -c ${SRC}/ftp_server.c

${BIN}/ftp_client: ${OBJ}/ftp_client.o
	gcc -o ${BIN}/ftp_client ${OBJ}/ftp_client.o

${OBJ}/ftp_client.o: ${SRC}/ftp_client.c
	gcc -o ${OBJ}/ftp_client.o -c ${SRC}/ftp_client.c


clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
