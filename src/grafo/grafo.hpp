/**
 * @file grafo.hpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 24/08/2021
 */

#ifndef GRAFO
#define GRAFO

#include <list>
#include <queue>
#include <limits>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

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
 * @brief Classe que representa um único grafo,
 * que sabe encapsula todos os métodos necessários
 * para a operação do mesmo
 * 
 * Utiliza a representação Listas de Adjacência
 */
class Grafo {
    private:
        bool isOrientado; /// booleano que indica se o grafo é orientado
        int qnt_nos;  /// inteiro que indica a quantidade de vertices do grafo
        std::list<NoGrafo> *grafo;  /// vetor de listas de vertices

        cor *cores;  /// vetor de cores, alocado somente quando tem busca em
                     /// profundidade ou largura

        int *predecessores;  /// vetor de predecessores, alocado somente quando
                             /// tem busca em profundidade ou largura

        int *dist;  /// vetor que informa a distância do vertice até a origem,
                    /// utilizado apenas na busca em largura

        std::list<int> ordem;  /// vetor que informa a ordem em que os vertices
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
         * @brief Explora um vertice de cor branca, visitando recursivamente
         * todos os vertices adjacentes
         *
         * @param index Vertice a ser explorado, cor branca
         * @pre Somente chamado pela buscaEmProfuntidade
         * @post Vertice index totalmente explorado, cor preto
         */
        void buscaEmProfundidadeVisit(int index);

        /**
         * @brief Imprime a lista que contém a ordem de acesso dos vertices
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
         * @pre filename contem um nome de arquivo valido
         * @post Grafo inicializado com os dados
         */
        void ler(std::string filename);
        void ler();

        /**
         * @brief Imprime os grafos, em um formato de lista de adjacencia
         * 
         * @pre Nenhuma
         * @post Nenhuma
         */
        void show();

        /**
         * @brief Ordena cada uma das Listas de Adjacência
         * 
         * Complexidade O(n^2 * n*lg(n))
         * @pre o vetor de listas (grafo), deve estar alocado
         * @post cada lista do grafo está ordenada
         */
        void ordena();

        //----- Algoritimos de um grafo -----//
        void buscaEmProfundidade(int vertice_inicio);
        void buscaEmLargura(int vertice_inicio);

        /**
         * @brief Destrutor da classe Grafo
         * 
         * @pre Nenhuma
         * @post Nenhuma
         */
        ~Grafo();
};

#endif // GRAFO
