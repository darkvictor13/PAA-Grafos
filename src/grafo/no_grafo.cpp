/**
 * @file no_grafo.cpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 24/08/2021
 */

#include "no_grafo.hpp"

NoGrafo::NoGrafo(int id, int peso) {
	std::cout << "Construindo um No, com parametros\n";
	this->id = id;
	this->peso = peso;
}

NoGrafo::NoGrafo() {
	std::cout << "Construindo um No, sem parametros\n";
	this->id = 0;
	this->peso = 0;
}

bool NoGrafo::operator<(const NoGrafo& other) {
	return this->id < other.id;
}

std::ostream& operator << (std::ostream &out, const NoGrafo& other) {
	out << '[' << other.id << ']';
	return out;
}

int NoGrafo::getId() {
	return id;
}

int NoGrafo::getPeso() {
	return peso;
}

void NoGrafo::setId(int id) {
    this->id = id;
}

void NoGrafo::setPeso(int peso) {
    this->peso = peso;
}

NoGrafo::~NoGrafo() {
	std::cout << "Destruindo o No\n";
}