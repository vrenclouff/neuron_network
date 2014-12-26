
program=neural_net

OBJ= neuron.o neural_net.o main.o

# Míra optimalizace překladače gcc
OPT=-O2

#clean:
#	rm -f *.o ${OBJ}

${program}: ${OBJ}
	gcc ${OBJ} -o ${program} ${OPT}

	
neuron.o: neuron.c
	gcc neuron.c -c ${OPT}

neural_net.o: neural_net.c
	gcc neural_net.c -c ${OPT}

main.o: main.c neural_net.h
	gcc main.c -c ${OPT}
