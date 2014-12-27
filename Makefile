
program=neural_net
CC = gcc
OBJ= neuron.o neural_net.o main.o
OPT=-O2

${program}: ${OBJ}
	${CC} ${OBJ} -o ${program} ${OPT} -lm

	
neuron.o: neuron.c
	${CC} neuron.c -c ${OPT} -lm

neural_net.o: neural_net.c
	${CC} neural_net.c -c ${OPT} -lm

main.o: main.c neural_net.h
	${CC} main.c -c ${OPT} -lm
