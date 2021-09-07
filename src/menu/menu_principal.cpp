#include "menu_principal.hpp"


MenuPrincipal::MenuPrincipal() {
    debug("Construindo Menu\n");
}

MenuPrincipal::MenuPrincipal(Grafo *g) {
    debug("Construindo Menu\n");
	this->g = g;
}

void MenuPrincipal::mostrar() {
	using namespace std;
	cout << "--------------------------------------------------\n";
	cout << "                  Opçoes do menu\n";
	cout << "--------------------------------------------------\n";
    cout << "                  Algoritmos em grafos: \n\n";
    cout << "                  1.  Busca em Profundidade\n";
    cout << "                  2.  Busca em Largura\n";
    cout << "                  3.  Bellmain-Ford\n";
    cout << "                  4.  Kruskal\n";
    cout << "                  5.  Sair\n";
}

#ifdef __gnu_linux__

/**
 * @brief Lê um caractere ASCII do teclado
 * 
 * @return char Valor ASCII do caractere lido
 * @pre Nenhuma
 * @post Nenhuma
 */
char MenuPrincipal::getChar() {
    char character = 0;
    struct termios old = {0};
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&character,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return character;
}

#else


/**
 * @brief Lê um caractere ASCII do teclado
 * 
 * @return char Valor ASCII do caractere lido
 * @pre Nenhuma
 * @post Nenhuma
 */
char MenuPrincipal::getChar() {
    DWORD mode, cc;
    HANDLE h = GetStdHandle( STD_INPUT_HANDLE );
    if (h == NULL)
        return 0; // console not found
    GetConsoleMode( h, &mode );
    SetConsoleMode( h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT) );
    TCHAR c = 0;
    ReadConsole( h, &c, 1, &cc, NULL );
    SetConsoleMode( h, mode );
    return c;
}

#endif //__gnu_linux__


void MenuPrincipal::loop() {
	using namespace std;
	char entrada = 0;
    int verticeInicial;
    while (entrada != ESC) {
		system(CLEAR);
		mostrar();
		entrada = getChar();
		switch (entrada)
		{
		case '1':
			cout << "Busca em profundidade\n";
            cout << "Digite o vértice inicial: ";
            cin >> verticeInicial;
            while (verticeInicial < 0 || verticeInicial > g->qnt_nos){
                cout << "Vertice inválido. Digite novamente: \n";
                cin >> verticeInicial;
            }
            g->buscaEmProfundidade(verticeInicial);
            cout << "\nDigite ENTER para sair\n";
            getChar();
            
			break;
		
        case '2':
			cout << "Busca em Largura\n";
            cout << "Digite o vértice inicial: ";
            cin >> verticeInicial;
            while (verticeInicial < 0 || verticeInicial > g->qnt_nos){
                cout << "Vertice inválido. Digite novamente: \n";
                cin >> verticeInicial;
            }
            g->buscaEmLargura(verticeInicial);
            cout << "\nDigite ENTER para sair\n";
            getChar();
			break;

        case '3':
			cout << "Bellman-Ford\n";
            cout << "Digite o vértice inicial: ";
            cin >> verticeInicial;
            while (verticeInicial < 0 || verticeInicial > g->qnt_nos){
                cout << "Vertice inválido. Digite novamente: \n";
                cin >> verticeInicial;
            }
            g->bellmanFord(verticeInicial);
            cout << "\nDigite ENTER para sair\n";
            getChar();
			break;
        
        case '4':
			cout << "Kruskal\n";
            g->kruskal();
            cout << "\nDigite ENTER para sair\n";
            getChar();
			break;
        
        case '5':
			cout << "Para sair digite ESC\n";
            getChar();
        
			break;

		default:
            cout << "Digite uma opção válida\n";
            getChar();
			break;
		}
	}
}

MenuPrincipal::~MenuPrincipal() {
    debug("Destruindo Menu\n");
}
