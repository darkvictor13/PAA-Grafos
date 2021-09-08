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
    if (argc == 2) {
        arq = argv[1];
        g.ler(arq);
    }
    /*
    g.buscaEmLargura(3);
    g.buscaEmProfundidade(3);
    g.bellmanFord(3);
    g.kruskal();
    */
    MenuPrincipal menu (&g);
    menu.loop();
    return 0;
}
