#include <iostream>
#include <fstream>
#include "grafo/grafo.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    Grafo g;
    //g.ler("input");
    g.ler();
    g.ordena();
    g.buscaEmProfundidade(3);
    g.show();
    return 0;
}
