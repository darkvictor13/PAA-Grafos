# O Compilador usado
CC=g++
# flags das libs utilizadas
LIBS=-std=c++17 -O2 -lm

CAMINHO=../src/

SRC=$(CAMINHO)main.cpp $(CAMINHO)grafo/*.cpp

# como compila o programa
release:
	$(CC) $(SRC) $(LIBS) -o main.out

debug:
	$(CC) $(SRC) $(LIBS) -D DEBUG_VAR -o main.out

run : debug
	./main.out
