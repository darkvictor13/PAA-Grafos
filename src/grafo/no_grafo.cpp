/**
 * @file no_grafo.cpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief Implementa todas as funcionalidade da classe NoGrafo
 * @version 0.1
 * @date 24/08/2021
 */

#include "no_grafo.hpp"

/**
 * @brief Construtor da classe NoGrafo
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
NoGrafo::NoGrafo() {
    debug("Construindo um No, sem parametros\n");
    this->id = 0;
    this->peso = 0;
}

/**
 * @brief Construtor da classe No Grafo
 *
 * @param id numero que representa o vertice
 * @param peso peso da aresta que chega ao vertice
 * @pre Nenhuma
 * @post Nenhuma
 */
NoGrafo::NoGrafo(int id, int peso) {
    debug("Construindo um No, com parametros\n");
    this->id = id;
    this->peso = peso;
}

/**
 * @brief Sobrecarga do operador < necessária para ordenação
 *
 * faz a comparação a partir do id do vértice
 * @param other
 * @return true se this->id é maior
 * @return false se other.id é maior
 * @pre Nenhuma
 * @post Nenhuma
 */
bool NoGrafo::operator<(const NoGrafo& other) {
    return this->id < other.id;
}

/**
 * @brief Sobrecarga do operador < necessária para std::find
 *
 * faz a comparação a partir do id do vértice
 * @param other
 * @return true se other é igual ao id do vertice
 * @return false se other é diferente ao id do vertice
 * @pre Nenhuma
 * @post Nenhuma
 */
bool NoGrafo::operator==(int other) {
    return this->id == other;
}

/**
 * @brief Sobrecarga do operador < necessária para std::find
 * 
 * faz a comparação a partir do id do vértice
 * @param other o outro no
 * @return true se other é igual ao id do vertice
 * @return false se other é diferente ao id do vertice
 * @pre Nenhuma
 * @post Nenhuma
 */
bool NoGrafo::operator == (const NoGrafo &other) {
    return this->id == other.id;
}

bool NoGrafo::operator >= (const NoGrafo &other) {
    return this->id >= other.id;
}

/**
 * @brief Sobrecarga do operador < necessária para impressão em stream
 *
 * @param out stream para escrita, podendo ser um arquivo ou o terminal
 * @param other A classe que contém os dados a serem impressos
 * @return std::ostream& ponteiro implicíto para a stram,
 * para continuar a impressão com <<
 * @pre Nenhuma
 * @post Nenhuma
 */
std::ostream& operator << (std::ostream &out, const NoGrafo& other) {
    //out << '[' << other.id << ", " << other.peso << ']';
    out << '[' << other.id << ']';
    return out;
}

/**
 * @brief Destrutor da classe NoGrafo
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
NoGrafo::~NoGrafo() {
    debug("Destruindo o No\n");
}
