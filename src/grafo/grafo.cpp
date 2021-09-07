/**
 * @file grafo.cpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief Implementa todas as funcionalidade da classe Grafo
 * @version 0.1
 * @date 24/08/2021
 */

#include "grafo.hpp"
#include "no_grafo.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

template<class T> static void selectionSort(T *v, int tam) {
    int i, j, menor;
    for(i = 0; i < tam; i++) {
        menor = i;
        for(j = i + 1; j < tam; j++) {
            if (v[j] < v[menor]) {
                menor = j;
            }
        }
        std::swap(v[i], v[menor]);
    }
}

/**
 * @brief Construtor da classe Grafo
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
Grafo::Grafo() {
    debug("Construindo um grafo\n");
}

/**
 * @brief Constroi um grafo a partir de dados de entrada
 *
 * @param in uma stream, podendo ser cin ou um arquivo
 * @pre uma stream de entrada válida
 * @post Grafo alocado e contendo os dados da stream
 */
void Grafo::constroi(std::istream& file) {
    std::string line;
    getline(file, line);
    isOrientado = (line.substr(line.find_first_of('=') + 1) == "sim");

    getline(file, line);
    qnt_nos = atoi((line.substr(line.find_first_of('=') + 1)).c_str());

    this->grafo = new Lista<NoGrafo>[qnt_nos];

    NoGrafo temp;
    int index;
    while (getline(file, line)) {
        temp.id = atoi(&line[line.find_first_of(',') + 1]);
        temp.peso = atoi(&line[line.find_first_of(':') + 1]);
        index = atoi(&line[1]);
        grafo[index].insereOrdenado(temp);
        if (!isOrientado) {
            std::swap(index, temp.id);
            grafo[index].insereOrdenado(temp);
        }
    }
}

/**
 * @brief Cria o grafo com as informações contidas no arquivo
 *
 * ver a função constroi
 * @param filename o nome do arquivo a ser lido
 * @pre filename contem um nome de arquivo valido e grafo desalocado
 * @post Grafo inicializado com os dados
 */
void Grafo::ler(std::string filename) {
    std::ifstream file;
    file.open(filename);

    constroi(file);

    file.close();
}

/**
 * @brief Inicializa o vertice de origem
 *
 * Utilizado no algorítimo de Bellman-Ford
 * @pre predecessores e dist inicializados
 * @post vértice de origem e suas estruturas auxiliares
 * inicializadas
 */
void Grafo::inicializaOrigem(int origem) {
    for(int i = 0; i < qnt_nos; i++) {
        predecessores[i] = NIL;
        dist[i] = MAX_DIST;
    }
    dist[origem] = 0;
}

/**
 * @brief Diminui o limite superior do peso do menor caminho
 *
 * Devido a estrutura grafo
 * Utilizado no algorítimo de Bellman-Ford
 * @param inicio vertice que inicia o caminho
 * @param fim vertice que acaba o caminho
 * @pre Um algorítimo de menor caminho estar sendo executado
 * com suas estruturas alocadas
 * @post menor peso entre início e fim
 */
void Grafo::relax(const int inicio, const int fim, const int peso) {
    debug("Comparando " << dist[fim] << " > " << dist[inicio] << " + " << peso
                        << std::endl);
    if (dist[fim] > (dist[inicio] + peso)) {
        debug("Entrei no if de mudar\n");
        dist[fim] = dist[inicio] + peso;
        predecessores[fim] = inicio;
    }
}

/**
 * @brief Cria o grafo com as informações recebidas da entrada padrão
 *
 * @pre Grafo desalocado
 * @post Nenhuma
 */
void Grafo::ler() {
    debug("Informe os dados na mesma sintaxe do arquivo\n");
    constroi(std::cin);
}

/**
 * @brief Imprime os grafos, em um formato de lista de adjacencia
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
void Grafo::mostrar() {
    for (int i = 0; i < this->qnt_nos; i++) {
        std::cout << "Arestas que saem de " << i << ": ";
        grafo[i].mostrar();

        //for (auto const &iterator : grafo[i]) {
        //std::cout << iterator << ' ';
        //}
        //std::cout << '\n';
    }
}

int Grafo::qntArestas() {
    int qnt = 0;
    for (int i = 0; i < qnt_nos; i++) {
        qnt += grafo[i].tam();
    }
    return qnt;
}

/**
 * @brief Imprime a lista que contém a ordem de acesso dos vertices
 *
 * @pre lista ordem alocada
 * @post lista impressa na saída padrão
 */
void Grafo::printOrdemAcesso() {
    std::cout << "Ordem de acesso: ";
    auto it = ordem.cbegin();
    for (auto fim = std::prev(ordem.cend()); it != fim; it++) {
        std::cout << *it << " - ";
    }
    std::cout << *it << '\n';
}

/**
 * @brief Imprime o vetor de predecessores
 *
 * @pre vetor de predecessores alocada
 * @post vetor de predecessores impressa na saída padrão
 */
void Grafo::printPredecessores() {
    int i;
    std::cout << "Predecessores:   ";
    for (i = 0; i < qnt_nos - 1; i++) {
        if (predecessores[i] == NIL) {
            std::cout << "NIL";
        } else {
            std::cout << predecessores[i];
        }
        std::cout << " - ";
    }
    std::cout << predecessores[i] << '\n';
}

void Grafo::printDist() {
    int i;
    std::cout << "dist.:   ";
    for (i = 0; i < qnt_nos - 1; i++) {
        if (dist[i] == MAX_DIST) {
            std::cout << "INF";
        } else {
            std::cout << dist[i];
        }
        std::cout << " - ";
    }
    std::cout << dist[i] << '\n';
}

/**
 * @brief Explora um vértice de cor branca, visitando recursivamente
 * todos os vertices adjacentes
 *
 * @param index Vértice a ser explorado, cor branca
 * @pre Somente chamado pela buscaEmProfuntidade
 * @post Vértice index totalmente explorado, cor preto
 */
void Grafo::buscaEmProfundidadeVisit(int index) {
    debug(index);
    debug('\n');
    ordem.push_back(index);
    cores[index] = CINZA;
    //for(auto it : grafo[index]) {
    for(auto it = grafo[index].inicio(); it; it = it->proximo) {
        if(cores[it->dado.id] == BRANCO) {
            predecessores[it->dado.id] = index;
            buscaEmProfundidadeVisit(it->dado.id);
        }
    }
    cores[index] = PRETO;
}

/**
 * @brief Visita os vértices a partir de um ponto inicial,
 * seguindo o algorítimo de busca em profundidade
 *
 * @param vertice_inicio deve estar dentro dos limites do vértice
 * @pre Grafo inicializado com ler
 * @post ordem de visitação vértices impressa na saída padrão
 */
void Grafo::buscaEmProfundidade(int vertice_inicio) {
    int i;
    //int NIL = std::numeric_limits<int>::max();

    predecessores = new(std::nothrow) int[qnt_nos];
    cores         = new(std::nothrow) cor[qnt_nos];

    // inicialização
    for(i = 0; i < qnt_nos; i++) {
        cores[i] = BRANCO;
        predecessores[i] = NIL;
    }

    for(i = vertice_inicio; i < qnt_nos; i++) {
        if (cores[i] == BRANCO) {
            buscaEmProfundidadeVisit(i);
        }
    }

    for(i = 0; i < vertice_inicio; i++) {
        if (cores[i] == BRANCO) {
            buscaEmProfundidadeVisit(i);
        }
    }

    printOrdemAcesso();
    printPredecessores();

    delete[] cores;
    delete[] predecessores;
    ordem.clear();
}

/**
 * @brief Visita os vértices a partir de um ponto inicial,
 * seguindo o algorítimo de busca em largura
 *
 * @param vertice_inicio deve estar dentro dos limites do vértice
 * @pre Grafo inicializado com ler
 * @post ordem de visitação vértices impressa na saída padrão
 */
void Grafo::buscaEmLargura(int vertice_inicio) {
    int i;
    //std::queue<int> fila;
    Lista<int> fila;
    predecessores = new(std::nothrow) int[qnt_nos];
    cores         = new(std::nothrow) cor[qnt_nos];
    dist		  = new(std::nothrow) int[qnt_nos];

    // inicialização
    for(i = 0; i < qnt_nos; i++) {
        cores[i] = BRANCO;
        predecessores[i] = NIL;
        dist[i] = MAX_DIST;
    }
    cores[vertice_inicio] = CINZA;
    dist[vertice_inicio] = 0;
    fila.insereFim(vertice_inicio);
    ordem.push_back(vertice_inicio);

    int cabeca;
    //while(!fila.empty()) {
    while(!fila.isVazia()) {
        //cabeca = fila.front();
        cabeca = fila.inicio()->dado;
        //for(auto it : grafo[cabeca]) { // eliminar copias
        for(auto it = grafo[cabeca].inicio(); it; it = it->proximo) {
            if (cores[it->dado.id] == BRANCO) {
                int salva_id = it->dado.id;
                cores[salva_id] = CINZA;
                dist[salva_id] = dist[cabeca] + 1;
                predecessores[salva_id] = cabeca;
                fila.insereFim(salva_id);
                ordem.push_back(salva_id);
            }
        }
        fila.retiraInicio();
        cores[cabeca] = PRETO;
    }
    printOrdemAcesso();
    printPredecessores();

    delete[] cores;
    delete[] dist;
    delete[] predecessores;
    ordem.clear();
    }

    /**
     * @brief Utilizado para mostrar na tela o caminho de um
     * vertice origem até um vertice fim utilizando a lista de
     * predecessores
     *
     * Utilizado no algoritimo de BellMan-Ford
     * @param inicio vertice que inicia o caminho
     * @param fim vertice que acaba o caminho
     * @pre vetor de predecessores alocado
     * @post Caminho impresso na tela
     */
    void Grafo::printCaminho(int inicio, int fim) {
        if (inicio == fim) {
            std::cout << inicio;
        }
        std::cout << fim << " - ";
        printCaminho(inicio, predecessores[fim]);
    }

    bool Grafo::bellmanFord(int vertice_inicio) {
        int i, qnt;
        bool ret = true;
        predecessores = new int[qnt_nos];
        dist		  = new int[qnt_nos];

        inicializaOrigem(vertice_inicio);

        printDist();
        for (qnt = 0; qnt < (qnt_nos - 3); qnt++) {
            // percorre cada uma das arestas
            for(i = 0; i < qnt_nos; i++) {
                for(auto it = grafo[i].inicio(); it; it = it->proximo) {
                    relax(i, it->dado.id, it->dado.peso);
                }
                printDist();
            }
            qnt++;
        }

        printDist();
        printPredecessores();

        // percorre cada uma das arestas
        //for(i = 0; i < qnt_nos; i++) {
            //for (auto it : grafo[i]) {
            //if (dist[it.id] > dist[i] + it.peso) {
            //ret = false;
            //break;
            //}
            //}
        //}

        //if (ret) {
        for(i = 0; i < qnt_nos; i++) {
            std::cout << "caminho: ";
            //printCaminho(vertice_inicio, i);
        }
        //}else {
        //std::cout << "O Grafo Possui ciclo negativo" << std::endl;
        //}
        //printPredecessores();
        //printDist();

        delete[] dist;
        delete[] predecessores;
        return ret;
    }

    bool Grafo::existeSimetrico(Aresta *v, int tam, Aresta &dado) {
        for (int i = 0; i < tam; i++) {
            if (v[i].isSimetrica(dado)) {
                return true;
            }
        }
        return false;
    }

        void Grafo::kruskal() {
        Aresta *arvore;
        int i, c, peso;
        int qnt_aresta = this->qntArestas();
        arvore = new Aresta[qnt_aresta];
        Lista<int> aux;
        Lista<int> *p;
        Lista<Aresta> A;
        Lista<Lista<int>*> conjuntoV;
        Lista<int> l_inicio;
        Lista<int> l_fim;

        //conjunto (v)
        for(i=0;i<qnt_nos;i++) {
            p = new Lista<int>;
            p->insereFim(i);
            conjuntoV.insereFim(p);
            p = nullptr;
        }
        //print
        debug("conjunto(v)\n\n");
        for(i = 0; i < qnt_nos; i++) {
            conjuntoV.naPos(i)->dado->mostrar();
        }
        // inserir as coisas Usando isSimetrica
        //inserindo todas as arestas para ordenar
        debug("\narestas de E\n");
        for(i = c = 0; i < qnt_nos; i++) {
            for (auto it = grafo[i].inicio(); it; it = it->proximo) {
                Aresta inserir(i, it->dado.id, it->dado.peso);
                if (!this->existeSimetrico(arvore, c, inserir)) {
                    arvore[c++] = inserir;
                }
            }
        }
        //print
        for(i = 0; i < c; i++) {
            debug(arvore[i] << std::endl);
        }
        debug("\n\n");

        //std::stable_sort(arvore, (arvore + qnt_aresta));
        debug("arestas ordenadas em ordem nao decrescente\n");
        selectionSort(arvore, c);

        for(i = 0; i < c; i++) {
            debug(arvore[i] << std::endl);
        }

        for (i = peso = 0; i < qnt_aresta; i++) {
            /*
               aux = *conjuntoV.inicio()->dado;
               for (c = 0; !aux.acha(arvore[i].inicio); c++) {
               aux = *conjuntoV.naPos(c)->dado;
               }
               l_inicio = aux;
               aux = *conjuntoV.inicio()->dado;
               for (c = 0; !aux.acha(arvore[i].inicio); c++) {
               aux = *conjuntoV.naPos(c)->dado;
               }   
               l_fim = aux;
               */
            
            //arvore tem os vertices ordenados pelas arestas
            //conjunto v tem os vertices em listas de listas
            auto conjU = conjuntoV.naPos(i);
            int conjV = arvore[i].fim;

            //!A.acha(arvore[i]) && !A.acha(*(new Aresta (arvore[i].fim, arvore[i].inicio, arvore[i].peso)))
            if (conjU != conjV) {
                peso += arvore[i].peso;
                A.insereFim(arvore[i]);
            }
        }

        std::cout << "peso total: " << peso << "\narestas: ";
        A.mostrar();
        delete[] arvore;
    }

    /**
     * @brief Destrutor da classe Grafo
     *
     * @pre Nenhuma
     * @post Nenhuma
     */
    Grafo::~Grafo() {
        delete []grafo;
        debug("Destruindo um grafo\n");
    }
