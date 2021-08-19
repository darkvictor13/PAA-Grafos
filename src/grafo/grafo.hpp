#ifndef GRAFO
#define GRAFO

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief 
 */
struct no {
    int id;
    int peso;
};

class Grafo {
    private:
        bool isOrientado; /// booleando que indica se o grafo é orientado
        int qnt_nos; /// booleando que indica a quantidade de vertices do grafo
        std::list<no> *grafo; /// vetor de listas de vertices

    public:
        Grafo();
        void ler(std::string filename);
        void show();
        friend std::ifstream& operator >> (std::ifstream &input, const Grafo &g);
        ~Grafo();
};

#endif
