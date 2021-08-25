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

/**
 * @brief 
 */
class NoGrafo {
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
	NoGrafo(int id, int peso);

	bool operator < (const NoGrafo& other);
	friend std::ostream& operator << (std::ostream &out, const NoGrafo& other);

	int getId();
	int getPeso();

	void setId(int id);
	void setPeso(int peso);

	~NoGrafo();
};


#endif // NO_GRAFO
