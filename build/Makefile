# O Compilador usado
CC=g++
# flags das libs utilizadas
LIBS=-lm

CAMINHO=../src/

SRC=$(CAMINHO)main.cpp $(CAMINHO)grafo/*.cpp

# como compila o programa
all:
	$(CC) $(SRC) $(LIBS) -o main.out

run : all
	./main.out
