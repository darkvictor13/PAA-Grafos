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
    this->grafo = nullptr;
    cores = nullptr;
    predecessores = nullptr;
    dist = nullptr;
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

    if(file.is_open()){
        constroi(file);
    }else{
        std::cout << "arquivo " << filename << " invalido\n";
    }
    

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
bool Grafo::relax(const int inicio, const int fim, const int peso) {
    if (dist[fim] > (dist[inicio] + peso)) {
        dist[fim] = dist[inicio] + peso;
        predecessores[fim] = inicio;
        return true;
    }
    return false;
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
        std::cout << "Vértices adjacentes a " << i << ": ";
        grafo[i].mostrar(" ");
    }
}

/**
 * @brief Conta a quantidade de arestas em um grafo
 * @return int A quantidade de Arestas presentes no Grafo
 * @pre Grafo inicializado
 * @post Nenhuma
 */
int Grafo::qntArestas() {
    int qnt = 0;
    for (int i = 0; i < qnt_nos; i++) {
        qnt += grafo[i].tam();
    }
    if (!this->isOrientado) {
        qnt /= 2;
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
    ordem.mostrar(" - ");
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
    ordem.insereFim(index);
    cores[index] = CINZA;
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

    predecessores = new int[qnt_nos];
    cores         = new cor[qnt_nos];

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

    delete[] cores;
    delete[] predecessores;
    ordem.limpar();
}

static int getGrau(int *pred, int index) {
    int count = 0;
    while(pred[index] != NIL) {
        index = pred[index];
        count++;
    }
    return count;
}

// problema: se u ou v forem o vértice inicial da busca
static int BFSPrimeiroAncestralComum(int *pred, int u, int v) {
    // encontra se qualquer um dos 2 não está contido na árvore
    if (pred[u] == NIL || pred[v] == NIL) {
        std::cout << "não tem caminhos\n";
    }
    // encontra o nível de profundidade na árvore
    int grau_u = getGrau(pred, u);
    int grau_v = getGrau(pred, v);
    // iguala a profundidade dos 2 para poder pesquisar
    // ancestrais comuns
    if (grau_u > grau_v) {
        while(grau_u != grau_v) {
            u = pred[u];
            grau_u--;
        }
    }else if (grau_u < grau_v){
        while(grau_u != grau_v) {
            v = pred[v];
            grau_v--;
        }
    }
    // caso u seja 
    do{
        u = pred[u];
        v = pred[v];
    }while(u != v);

    return u;
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
    Lista<int> fila;
    predecessores = new int[qnt_nos];
    cores         = new cor[qnt_nos];
    dist		  = new int[qnt_nos];

    // inicialização
    for(i = 0; i < qnt_nos; i++) {
        cores[i] = BRANCO;
        predecessores[i] = NIL;
        dist[i] = MAX_DIST;
    }
    cores[vertice_inicio] = CINZA;
    dist[vertice_inicio] = 0;
    fila.insereFim(vertice_inicio);
    ordem.insereFim(vertice_inicio);

    int cabeca;
    while(!fila.isVazia()) {
        cabeca = fila.inicio()->dado;
        for(auto it = grafo[cabeca].inicio(); it; it = it->proximo) {
            if (cores[it->dado.id] == BRANCO) {
                int salva_id = it->dado.id;
                cores[salva_id] = CINZA;
                dist[salva_id] = dist[cabeca] + 1;
                predecessores[salva_id] = cabeca;
                fila.insereFim(salva_id);
                ordem.insereFim(salva_id);
            }
        }
        fila.retiraInicio();
        cores[cabeca] = PRETO;
    }
    printOrdemAcesso();
    printPredecessores();
    int u, v;
    std::cout << "entre com 2 vértices: ";
    std::cin >> u >> v;
    std::cout << "Grau o vértice " << u <<  " = " << getGrau(this->predecessores, u) << '\n';
    std::cout << "Grau o vértice " << v <<  " = " << getGrau(this->predecessores, v) << '\n';

    std::cout << "Primeiro antecessor comum = " << BFSPrimeiroAncestralComum(this->predecessores, u, v) << '\n';

    delete[] cores;
    delete[] dist;
    delete[] predecessores;
    ordem.limpar();
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
        std::cout << fim;
        return;
    }
    if (inicio == NIL || predecessores[inicio] == NIL) {
        std::cout << "Inacessível";
        return;
    }
    printCaminho(predecessores[inicio], fim);
    std::cout << " - " << inicio;
}

/**
 * @brief Executa o algorítimo de BellMan-Ford
 *
 * Algorítimo que encontra o menor caminho de todos os vértices em
 * relação ao vertice passado como argumento
 * @param vertice_inicio o vértice para qual todos os outros devem
 * encontrar o menor caminho
 * @return true Caso o Grafo não possua um cíclo negativo
 * @return false Caso o Grafo possua um cíclo negativo
 * @pre vértice de início está contido no Grafo,
 *      Grafo deve ser orientado,
 * @post Nenhuma
 */
bool Grafo::bellmanFord(int vertice_inicio) {
    int i, qnt;
    bool ret;
    predecessores = new int[qnt_nos];
    dist		  = new int[qnt_nos];

    inicializaOrigem(vertice_inicio);

    for (qnt = 0; qnt < (qnt_nos - 2); qnt++) {
        ret = false;
        // percorre cada uma das arestas
        for(i = 0; i < qnt_nos; i++) {
            for(auto it = grafo[i].inicio(); it; it = it->proximo) {
                if (relax(i, it->dado.id, it->dado.peso)) {
                    ret = true;
                }
            }
        }
        // se não teve nenhum relax nessa interação por todas as arestas
        // pare de executar o algoritmo
        if (!ret) {
            break;
        }
    }

    // percorre cada uma das arestas, buscando ciclo negativo
    ret = true;
    for(i = 0; i < qnt_nos; i++) {
        for (auto it = grafo[i].inicio(); it; it = it->proximo) {
            if (dist[it->dado.id] > dist[i] + it->dado.peso) {
                ret = false;
                break;
            }
        }
    }

    if (ret) {
        for(i = 0; i < qnt_nos; i++) {
            std::cout   << "destino: "  << i        << ' '
                        << "dist: "     << dist[i]  << ' '
                        << "caminho: ";

            printCaminho(i, vertice_inicio);
            std::cout << std::endl;
        }
    }else {
        std::cout << "O Grafo Possui ciclo negativo" << std::endl;
    }

    delete[] dist;
    delete[] predecessores;
    return ret;
}

/**
 * @brief Busca no Vetor de Arestas uma Aresta simétrica
 *
 * somente utilizado para kruskal
 * @param v Vetor de Arestas
 * @param tam Tamanho do vetor
 * @param dado Referência para Aresta a ser buscada
 * @return true Existe Uma aresta simétrica no vetor
 * @return false Não existe Uma aresta simétrica no vetor
 * @pre Vetor de arestas carregado
 * @post Nenhuma
 */
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
    Lista<int> *p;
    Lista<Aresta> A;
    Lista<Lista<int>*> conjuntoV;
    Lista<int> *conj_u, *conj_v;
    int i, c, peso;
    int qnt_aresta = this->qntArestas();
    arvore = new Aresta[qnt_aresta];

    //conjunto (v), criando conjunto
    for(i=0;i<qnt_nos;i++) {
        p = new Lista<int>;
        p->insereFim(i);
        conjuntoV.insereFim(p);
        p = nullptr;
    }
    // inserindo todas as arestas para ordenar
    debug("\narestas de E\n");
    for(i = c = 0; i < qnt_nos; i++) {
        for (auto it = grafo[i].inicio(); it; it = it->proximo) {
            Aresta inserir(i, it->dado.id, it->dado.peso);
            if (!this->existeSimetrico(arvore, c, inserir)) {
                arvore[c++] = inserir;
            }
        }
    }

    debug("arestas ordenadas em ordem nao decrescente\n");
    selectionSort(arvore, c);

    for(i = 0; i < c; i++) {
        debug(arvore[i] << std::endl);
    }

    conj_u = conj_v = nullptr;
    for (i = peso = 0; i < qnt_aresta; i++) {
        // busca os conjuntos que tem os vértices correspondentes
        for (auto per = conjuntoV.inicio(); per; per = per->proximo) {
            if (!conj_u) {
                if (per->dado->acha(arvore[i].inicio)) {
                    conj_u = per->dado;
                }
            }
            if (!conj_v) {
                if (per->dado->acha(arvore[i].fim)) {
                    conj_v = per->dado;
                }
            }
        }

        // se os conjuntos são diferentes
        if (conj_u && conj_v && (conj_u != conj_v)) {
            // faz a união dos conjuntos (concatena as 2 listas e exclui a de índice maior)
            for (auto p = conj_v->inicio(); p; p = p->proximo) {
                conj_u->insereFim(p->dado);
            }
            for (auto it = conjuntoV.inicio(); it; it = it->proximo) {
                if (!(it->dado != conj_v)) {
                    conjuntoV.desencadeia(it);
                    break;
                }
            }
            // insere a aresta na árvore pois ela é segura, e guarda o peso dela
            peso += arvore[i].peso;
            A.insereFim(arvore[i]);
        }
        conj_u = conj_v = nullptr;
    }

    std::cout << "peso total: " << peso << "\narestas: ";
    A.mostrar(" ");
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
