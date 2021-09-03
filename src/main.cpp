#include <iostream>
#include <fstream>
#include "grafo/grafo.hpp"
#include "menu/menu_principal.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    string filename;
    if (argc == 2) {
        filename = argv[1];
    }
    Grafo g;
    g.ler(filename);
    //g.ler();
    g.ordena();
    cout << "\nBusca em Profundidade:\n";
    g.buscaEmProfundidade(3);
    cout << "\nBusca em largura:\n";
    g.buscaEmLargura(3);
    cout << "\nBellMan-Ford:\n";
    g.bellmanFord(3);
    g.mostrar();
    return 0;
}
