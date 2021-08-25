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

enum cor {
    BRANCO,
    CINZA,
    PRETO
};

#define NIL -1

class Grafo {
    private:
        bool isOrientado; /// booleando que indica se o grafo é orientado
        int qnt_nos; /// booleando que indica a quantidade de vertices do grafo
        std::list<NoGrafo> *grafo; /// vetor de listas de vertices

        cor *cores; /// vetor de cores, alocado somente quando tem busca em profundidade
        int *predecessores; /// vetor de predecessores, alocado somente quando tem busca em profundidade
        int *dist;
        std::list<int> ordem; /// vetor que informa a ordem em que os vertices foram acessados,
                    /// alocado somente quando tem busca em profundidade

        void constroi(std::istream& in);
        void buscaEmProfundidadeVisit(int index);

        void printOrdemAcesso();
        void printPredecessores();

    public:
        Grafo();

        void ler(std::string filename);
        void ler();
        void show();

        void ordena();

        //----- Algoritimos de um grafo -----//
        void buscaEmProfundidade(int vertice_inicio);
        void buscaEmLargura(int vertice_inicio);
        ~Grafo();
};

#endif // GRAFO
