#ifndef GRAFO
#define GRAFO

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct no {
    int id;
    int peso;
};

class Grafo {
    private:
        bool isOrientado;
        int qnt_nos;
        std::list<no> *grafo;

    public:
        Grafo();
        void ler(std::string filename);
        void show();
        friend std::ifstream& operator >> (std::ifstream &input, const Grafo &g);
        ~Grafo();
};

#endif
