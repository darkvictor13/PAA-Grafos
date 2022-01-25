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
    if (argc == 2) {
        g.ler(argv[1]);
    }
    MenuPrincipal menu (&g);
    menu.loop();

    return 0;
}
