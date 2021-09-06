#include <iostream>
#include <fstream>
#include "grafo/grafo.hpp"
#include "grafo/no_grafo.hpp"
#include "lista/lista.hpp"
#include "utils/debug.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    string filename;
    if (argc == 2) {
        filename = argv[1];
    }

    /*
    Lista<NoGrafo> l;
    //Lista<int> l;
    l.insereOrdenado(*new NoGrafo(1, 1));
    l.insereOrdenado(*new NoGrafo(3, 3));
    l.insereOrdenado(*new NoGrafo(4, 4));
    l.insereOrdenado(*new NoGrafo(2, 2));
    //l.insereOrdenado(4);
    //l.insereOrdenado(2);
    //l.insereOrdenado(3);
    //l.insereOrdenado(1);
    debug(l.tam() << '\n');
    l.mostrar();
    l.mostrarInvertido();
    l.retiraInicio();
    l.retiraFim();
    l.mostrar();
    l.mostrarInvertido();
    */

    Grafo g;

    g.ler(filename);
    g.mostrar();
    cout << "\nBusca em Profundidade:\n";
    g.buscaEmProfundidade(3);
    cout << "\nBusca em largura:\n";
    g.buscaEmLargura(3);
    //cout << "\nBellMan-Ford:\n";
    //g.bellmanFord(3);
    return 0;
}
