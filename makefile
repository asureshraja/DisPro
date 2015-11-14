BIN=./bin
SOURCE=./src
MASTER_SRC=|Master.c|utils.c|http_parser.c
MASTER_FLAGS= -g -w -lpthread
MASTER_BIN=master
SLAVE_SRC=|Slave.c|utils.c
SLAVE_BIN=slave
SLAVE_FLAGS= -ldl -lpthread
hellomake:
	gcc $(subst |, ${SOURCE}/,${MASTER_SRC}) -o ${BIN}/${MASTER_BIN} ${MASTER_FLAGS}
	gcc $(subst |, ${SOURCE}/,${SLAVE_SRC}) -o ${BIN}/${SLAVE_BIN} ${SLAVE_FLAGS}
