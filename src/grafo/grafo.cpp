#include "grafo.hpp"

Grafo::Grafo() {
    
}

void Grafo::ler() {
	std::string line;
    std::cout << "O grafo é ordenado: ";
	std::cin >> line;
	try {
		this->isOrientado = 
		(line.substr(line.find_first_of('='), line.size()) == "sim");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	this->isOrientado = true;
	

    std::cout << "Quantidade de nós: ";
	scanf("%d%*c", &qnt_nos);

	this->grafo = new std::list<no> [qnt_nos];

	while (getline(std::cin, line)) {
		std::cout << "String de entrada [" << line << "]\n";
		no temp;
		temp.id = atoi(&line[line.find_first_of(',') + 1]);
		temp.peso = atoi(&line[line.find_first_of(':') + 1]);
		int index = atoi(&line[1]);
		grafo[index].push_back(temp);
		if (isOrientado) {
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
}
