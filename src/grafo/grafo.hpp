/**
 * @file grafo.hpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief Define a classe Grafo
 * 
 * Como representá-lo, seus algorítimos...
 * @version 0.1
 * @date 24/08/2021
 */

#ifndef GRAFO
#define GRAFO

#include <list>
#include <queue>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <climits>

#include "no_grafo.hpp"
#include "../utils/debug.hpp"

/**
 * @brief enumera todas as cores possiveis que um vértice
 * pode assumir, criando assim o tipo (cor)
 */
enum cor {
    BRANCO,
    CINZA,
    PRETO
};

/**
 * @brief define o valor que representa o Nulo para os algoritimos
 * 
 * utilizado em:
 *  - Busca em profundidade
 *  - Busca em largura
 */
#define NIL -1

/**
 * @brief Distancia máxima possível que não causa overflow em um int
 */
#define MAX_DIST ((INT_MAX/2) - 1)

/**
 * @brief Classe que representa um único grafo,
 * que sabe encapsula todos os métodos necessários
 * para a operação do mesmo
 * 
 * Utiliza a representação Listas de Adjacência
 */
class Grafo {
    private:
        bool isOrientado; /// booleano que indica se o grafo é orientado
        int qnt_nos;  /// inteiro que indica a quantidade de vértices do grafo
        std::list<NoGrafo> *grafo;  /// vetor de listas de vértices

        cor *cores;  /// vetor de cores, alocado somente quando tem busca em
                     /// profundidade ou largura

        int *predecessores;  /// vetor de predecessores, alocado somente quando
                             /// tem busca em profundidade ou largura

        int *dist;  /// vetor que informa a distância do vértice até a origem,
                    /// utilizado apenas na busca em largura

        std::list<int> ordem;  /// vetor que informa a ordem em que os vértices
                               /// foram acessados, alocado somente quando tem
                               /// busca em profundidade ou largura

        /**
         * @brief Constroi um grafo a partir de dados de entrada
         * 
         * @param in uma stream, podendo ser cin ou um arquivo
         * @pre uma stream de entrada válida
         * @post Grafo alocado e contendo os dados da stream
         */
        void constroi(std::istream& in);

        /**
         * @brief Explora um vértice de cor branca, visitando recursivamente
         * todos os vértices adjacentes
         *
         * @param index Vértice a ser explorado, cor branca
         * @pre Somente chamado pela buscaEmProfuntidade
         * @post Vértice index totalmente explorado, cor preto
         */
        void buscaEmProfundidadeVisit(int index);

        /**
         * @brief Imprime a lista que contém a ordem de acesso dos vértices
         *
         * @pre lista ordem alocada
         * @post lista impressa na saída padrão
         */
        void printOrdemAcesso();

        /**
         * @brief Imprime o vetor de predecessores
         * 
         * @pre vetor de predecessores alocada
         * @post vetor de predecessores impressa na saída padrão
         */
        void printPredecessores();

        void printDist();

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
        void printCaminho(int inicio, int fim);

        /**
         * @brief Inicializa o vertice de origem
         *
         * Utilizado no algorítimo de Bellman-Ford
         * @pre predecessores e dist inicializados
         * @post vértice de origem e suas estruturas auxiliares
         * inicializadas
         */
        void inicializaOrigem(int origem);

        /**
         * @brief Diminui o limite superior do peso do menor caminho
         * 
         * Utilizado no algorítimo de Bellman-Ford
         * @param inicio vertice que inicia o caminho
         * @param fim vertice que acaba o caminho
         * @pre Um algorítimo de menor caminho estar sendo executado
         * com suas estruturas alocadas
         * @post menor peso entre início e fim
         */
        void relax(int inicio, int fim);

    public:
        /**
         * @brief Construtor da classe Grafo
         * 
         * @pre Nenhuma
         * @post Nenhuma
         */
        Grafo();

        /**
         * @brief Cria o grafo com as informações contidas no arquivo
         * 
         * ver a função constroi
         * @param filename o nome do arquivo a ser lido
         * @pre filename contem um nome de arquivo valido e grafo desalocado
         * @post Grafo inicializado com os dados
         */
        void ler(std::string filename);

        /**
         * @brief Cria o grafo com as informações recebidas da entrada padrão
         *
         * @pre Grafo desalocado
         * @post Nenhuma
         */
        void ler();

        /**
         * @brief Imprime os grafos, em um formato de lista de adjacencia
         * 
         * @pre Nenhuma
         * @post Nenhuma
         */
        void mostrar();

        /**
         * @brief Ordena cada uma das Listas de Adjacência
         * 
         * Complexidade O(n^2 * n*lg(n))
         * @pre o vetor de listas (grafo), deve estar alocado
         * @post cada lista do grafo está ordenada
         */
        void ordena();

        //----------------- Algorítimos de um grafo -----------------//

        /**
         * @brief Visita os vértices a partir de um ponto inicial,
         * seguindo o algorítimo de busca em profundidade
         * 
         * @param vertice_inicio deve estar dentro dos limites do vértice
         * @pre Grafo inicializado com ler
         * @post ordem de visitação vértices impressa na saída padrão
         */
        void buscaEmProfundidade(int vertice_inicio);

        /**
         * @brief Visita os vértices a partir de um ponto inicial,
         * seguindo o algorítimo de busca em largura
         * 
         * @param vertice_inicio deve estar dentro dos limites do vértice
         * @pre Grafo inicializado com ler
         * @post ordem de visitação vértices impressa na saída padrão
         */
        void buscaEmLargura(int vertice_inicio);

        bool bellmanFord(int vertice_inicio);

        /**
         * @brief Destrutor da classe Grafo
         * 
         * @pre Nenhuma
         * @post Nenhuma
         */
        ~Grafo();
};

#endif // GRAFO
