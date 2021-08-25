/**
 * @file no_grafo.hpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 24/08/2021
 */

#ifndef NO_GRAFO
#define NO_GRAFO

#include <iostream>
#include "../utils/debug.hpp"

/**
 * @brief 
 */
class NoGrafo {
friend class Grafo;
private:
	int id, peso;
public:
	/**
	 * @brief Construtor da classe NoGrafo
	 * 
	 * @pre Nenhuma
	 * @post Nenhuma
	 */
	NoGrafo();

	/**
	 * @brief Construtor da classe No Grafo
	 * 
	 * @param id numero que representa o vertice
	 * @param peso peso da aresta que chega ao vertice
	 * @pre Nenhuma
	 * @post Nenhuma
	 */
	NoGrafo(int id, int peso);

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
	bool operator < (const NoGrafo& other);

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
	friend std::ostream& operator << (std::ostream &out, const NoGrafo& other);

	/**
	 * @brief Destrutor da classe NoGrafo
	 * 
	 * @pre Nenhuma
	 * @post Nenhuma
	 */
	~NoGrafo();
};


#endif // NO_GRAFO
