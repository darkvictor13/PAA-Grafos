#include "aresta_kruskal.hpp"

Aresta::Aresta(int inicio, int fim, int peso) {
    this->inicio = inicio;
    this->fim = fim;
    this->peso = peso;
}

Aresta::Aresta() {
    this->inicio = 0;
    this->fim = 0;
    this->peso = 0;
}

bool Aresta::operator<(const Aresta &other) {
	return this->peso < other.peso; 
}

bool Aresta::operator==(const Aresta &other) {
    return peso == other.peso && inicio == other.inicio && fim == other.fim;
}

bool operator<(const Aresta &eu, const Aresta &outro) {
    return eu.peso < outro.peso;
}

std::ostream &operator<<(std::ostream &out, const Aresta &other) {
    out << '(' << other.inicio << ',' << other.fim << ')';
    return out;
}

bool Aresta::isSimetrica(const Aresta &other) {
    return this->inicio == other.fim && this->fim == other.inicio;
}