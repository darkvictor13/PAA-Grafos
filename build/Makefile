# O Compilador usado
CC=g++
# flags das libs utilizadas
LIBS=-lm

CAMINHO=../src/

SRC=$(CAMINHO)main.cpp $(CAMINHO)grafo/*.cpp

# como compila o programa
release:
	$(CC) $(SRC) $(LIBS) -o main.out

debug:
	$(CC) $(SRC) $(LIBS) -D DEBUG_VAR -o main.out

run : debug
	./main.out
