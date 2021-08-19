#include "grafo.hpp"

Grafo::Grafo() {
	std::cout << "Construindo um grafo" << std::endl;
}

void Grafo::ler(std::string filename) {
    std::ifstream file;
    file.open(filename);

	std::string line;
	getline(file, line);
	isOrientado = (line.substr(line.find_first_of('=') + 1) == "sim");

	getline(file, line);
	qnt_nos = atoi((line.substr(line.find_first_of('=') + 1)).c_str());

	this->grafo = new std::list<no> [qnt_nos];

	no temp;
	while (getline(file, line)) {
		temp.id   = atoi(&line[line.find_first_of(',') + 1]);
		temp.peso = atoi(&line[line.find_first_of(':') + 1]);
		int index = atoi(&line[1]);
		grafo[index].push_back(temp);
		if (!isOrientado) {
			std::swap(index, temp.id);
            grafo[index].push_back(temp);
        }
    }
}

void Grafo::show() {
	for (int i = 0; i < this->qnt_nos; i++) {
		std::cout << "Arestas que saem de " << i << ": ";
		for (auto iterator : grafo[i]) {
			std::cout << iterator.id << ' ';
		}
		std::cout << '\n';
	}
}

Grafo::~Grafo() {
	for(int i = 0; i < this->qnt_nos; i++) {
		grafo[i].clear();
	}
	delete []grafo;
	std::cout << "Destruindo um grafo" << std::endl;
}
