#ifndef ARESTA_KRUSKAL
#define ARESTA_KRUSKAL

#include <iostream>

/**
 * @brief Estrutura que armazena uma aresta do Grafo
 * 
 * Utilizado no algoritimo de de Kruskal
 */
struct Aresta {
    int inicio, fim, peso;

    Aresta(int inicio, int fim, int peso);

    Aresta();

    bool operator<(const Aresta &other);

    bool operator==(const Aresta &other);

    friend bool operator < (const Aresta &eu, const Aresta &outro);

	friend std::ostream& operator << (std::ostream &out, const Aresta &other);

    bool isSimetrica(const Aresta &other);
};

#endif // ARESTA_KRUSKAL
