#include <iostream>
#include <fstream>
#include "grafo/grafo.hpp"
#include "grafo/no_grafo.hpp"
#include "lista/lista.hpp"
#include "utils/debug.hpp"
#include "menu/menu_principal.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    Grafo g;
    string arq;
    char entrada;
    if (argc == 2) {
        arq = argv[1];
        g.ler(arq);
    }

    /*
    cout << "\nBusca em Profundidade:\n";
    g.buscaEmProfundidade(3);
    cout << "\nBusca em largura:\n";
    g.buscaEmLargura(3);
    cout << "\nBellMan-Ford:\n";
    g.bellmanFord(3);
    */
    cout << "\nKruskal:\n";
    return 0;
}
