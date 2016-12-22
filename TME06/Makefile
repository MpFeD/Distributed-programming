CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: directories ${BIN}/remonte_posix_partagee ${BIN}/posix_barrier ${BIN}/diner_philosophes ${BIN}/chat_client ${BIN}/chat_server

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

${BIN}/remonte_posix_partagee: ${OBJ}/remonte_posix_partagee.o
	gcc -o ${BIN}/remonte_posix_partagee ${OBJ}/remonte_posix_partagee.o -lrt

${OBJ}/remonte_posix_partagee.o: ${SRC}/remonte_posix_partagee.c
	gcc -o ${OBJ}/remonte_posix_partagee.o -c ${SRC}/remonte_posix_partagee.c

${BIN}/posix_barrier: ${OBJ}/posix_barrier.o
	gcc -o ${BIN}/posix_barrier ${OBJ}/posix_barrier.o -lpthread

${OBJ}/posix_barrier.o: ${SRC}/posix_barrier.c
	gcc -o ${OBJ}/posix_barrier.o -c ${SRC}/posix_barrier.c

${BIN}/diner_philosophes: ${OBJ}/diner_philosophes.o
	gcc -o ${BIN}/diner_philosophes ${OBJ}/diner_philosophes.o -lpthread -lrt

${OBJ}/diner_philosophes.o: ${SRC}/diner_philosophes.c
	gcc -o ${OBJ}/diner_philosophes.o -c ${SRC}/diner_philosophes.c

#${BIN}/chat_client: ${OBJ}/chat_client.o
#	gcc -o ${BIN}/chat_client ${OBJ}/chat_client.o -lpthread -lrt -l pthread -I/${INC}

#${OBJ}/chat_client.o: ${SRC}/chat_client.c
#	gcc -o ${OBJ}/chat_client.o -c ${SRC}/chat_client.c -lrt -l pthread -I/${INC}

#${BIN}/chat_server: ${OBJ}/chat_server.o
#	gcc -o ${BIN}/chat_server ${OBJ}/chat_server.o -lpthread -lrt -l pthread -I/${INC}

#${OBJ}/chat_server.o: ${SRC}/chat_server.c
#	gcc -o ${OBJ}/chat_server.o -c ${SRC}/chat_server.c -lrt -l pthread -I/${INC}

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
