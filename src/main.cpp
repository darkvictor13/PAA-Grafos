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

    Lista<int> l;
    //l.insereInicio(*new NoGrafo(1, 1));
    //l.insereInicio(*new NoGrafo(2, 2));
    //l.insereInicio(*new NoGrafo(3, 3));
    //l.insereInicio(*new NoGrafo(4, 4));
    l.insereFim(1);
    l.insereFim(2);
    l.mostrar();
    l.mostrarInvertido();
    l.retiraInicio();
    l.mostrar();
    l.mostrarInvertido();
    debug("Antes de retirar o fim\n");
    l.retiraFim();
    debug("Depois de retirar o fim\n");

    /*
    Grafo g;

    g.ler(filename);
    //g.ler("input");
    g.ler();
    cout << "Ola Mundo\n";
    g.ordena();
    g.mostrar();
    cout << "\nBusca em Profundidade:\n";
    g.buscaEmProfundidade(3);
    cout << "\nBusca em largura:\n";
    g.buscaEmLargura(3);
    cout << "\nBellMan-Ford:\n";
    g.bellmanFord(3);
    */
    return 0;
}
