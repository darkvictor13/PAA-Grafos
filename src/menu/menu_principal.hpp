#ifndef MENU_PRINCIPAL
#define MENU_PRINCIPAL

#include "menu_defines.hpp"
#include "../utils/debug.hpp"
#include "../grafo/grafo.hpp"
#include <string>

class MenuPrincipal {
private:
	Grafo *g;
public:
	MenuPrincipal();
	MenuPrincipal(Grafo *g);

	void mostrar();

    char getChar();

	void loop();

	~MenuPrincipal();
};

#endif // MENU_PRINCIPAL
