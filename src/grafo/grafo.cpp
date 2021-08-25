/**
 * @file grafo.cpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 24/08/2021
 */

#include "grafo.hpp"

Grafo::Grafo() {
	std::cout << "Construindo um grafo" << std::endl;
}

void Grafo::constroi(std::istream& file) {
    std::string line;
    getline(file, line);
    isOrientado = (line.substr(line.find_first_of('=') + 1) == "sim");

    getline(file, line);
    qnt_nos = atoi((line.substr(line.find_first_of('=') + 1)).c_str());

    this->grafo = new std::list<NoGrafo>[qnt_nos];

    NoGrafo temp;
    int index;
    while (getline(file, line)) {
        temp.setId(atoi(&line[line.find_first_of(',') + 1]));
        temp.setPeso(atoi(&line[line.find_first_of(':') + 1]));
        index = atoi(&line[1]);
        grafo[index].push_back(temp);
        if (!isOrientado) {
			int troca = temp.getId();
			temp.setId(index);
            grafo[troca].push_back(temp);
        }
    }
}

void Grafo::ler(std::string filename) {
    std::ifstream file;
    file.open(filename);

	constroi(file);
	
	file.close();
}

void Grafo::ler() {
	std::cout << "Informe os dados na mesma sintaxe do arquivo\n";
	constroi(std::cin);
}

void Grafo::show() {
	for (int i = 0; i < this->qnt_nos; i++) {
		std::cout << "Arestas que saem de " << i << ": ";
		for (auto const &iterator : grafo[i]) {
			std::cout << iterator << ' ';
		}
		std::cout << '\n';
	}
}

void Grafo::ordena() {
	for(int i = 0; i < qnt_nos; i++) {
		grafo[i].sort();
	}
}

void Grafo::buscaEmProfundidadeVisit(int index) {
	std::cout << index << '\n';
	ordem.push_back(index);
	cores[index] = CINZA;
	for(auto it : grafo[index]) { // eliminar copias
		if(cores[it.getId()] == BRANCO) {
			predecessores[it.getId()] = index;
			buscaEmProfundidadeVisit(it.getId());
		}
	}
	cores[index] = PRETO;
}

void Grafo::buscaEmProfundidade(int vertice_inicio) {
	int i;
	//int nil = std::numeric_limits<int>::max();
	int nil = -1;

	predecessores = new(std::nothrow) int[qnt_nos];
	cores         = new(std::nothrow) cor[qnt_nos];

	// inicialização
	for(i = 0; i < qnt_nos; i++) {
		cores[i] = BRANCO;
		predecessores[i] = nil;
	}

	for(i = vertice_inicio; i < qnt_nos; i++) {
		if (cores[i] == BRANCO) {
			buscaEmProfundidadeVisit(i);
		}
	}

	for(i = 0; i < vertice_inicio; i++) {
		if (cores[i] == BRANCO) {
			buscaEmProfundidadeVisit(i);
		}
	}
	std::cout << "Ordem de acesso: ";
	auto it = ordem.cbegin();
	for (auto fim = std::prev(ordem.cend()); it != fim; it++) {
        std::cout << *it << " - ";
    }
    std::cout << *it << '\n';

    std::cout << "Predecessores:   ";
    for (i = 0; i < qnt_nos - 1; i++) {
        if (predecessores[i] == nil) {
            std::cout << "nil";
        } else {
            std::cout << predecessores[i];
        }
        std::cout << " - ";
	}
    std::cout << predecessores[i] << '\n';

	delete[] cores;
	delete[] predecessores;
	ordem.clear();
}


Grafo::~Grafo() {
	for(int i = 0; i < this->qnt_nos; i++) {
		grafo[i].clear();
	}
	delete []grafo;
	std::cout << "Destruindo um grafo" << std::endl;
}
