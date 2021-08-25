/**
 * @file grafo.cpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 24/08/2021
 */

#include "grafo.hpp"

/**
 * @brief Construtor da classe Grafo
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
Grafo::Grafo() {
	debug("Construindo um grafo\n");
}

/**
 * @brief Constroi um grafo a partir de dados de entrada
 *
 * @param in uma stream, podendo ser cin ou um arquivo
 * @pre uma stream de entrada válida
 * @post Grafo alocado e contendo os dados da stream
 */
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
        temp.id = atoi(&line[line.find_first_of(',') + 1]);
        temp.peso = atoi(&line[line.find_first_of(':') + 1]);
        index = atoi(&line[1]);
        grafo[index].push_back(temp);
        if (!isOrientado) {
			std::swap(index, temp.id);
            grafo[index].push_back(temp);
        }
    }
}

/**
 * @brief Cria o grafo com as informações contidas no arquivo
 *
 * ver a função constroi
 * @param filename o nome do arquivo a ser lido
 * @pre filename contem um nome de arquivo valido e grafo desalocado
 * @post Grafo inicializado com os dados
 */
void Grafo::ler(std::string filename) {
    std::ifstream file;
    file.open(filename);

	constroi(file);
	
	file.close();
}

/**
 * @brief Cria o grafo com as informações recebidas da entrada padrão
 *
 * @pre Grafo desalocado
 * @post Nenhuma
 */
void Grafo::ler() {
	debug("Informe os dados na mesma sintaxe do arquivo\n");
	constroi(std::cin);
}

/**
 * @brief Imprime os grafos, em um formato de lista de adjacencia
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
void Grafo::show() {
	for (int i = 0; i < this->qnt_nos; i++) {
		std::cout << "Arestas que saem de " << i << ": ";
		for (auto const &iterator : grafo[i]) {
			std::cout << iterator << ' ';
		}
		std::cout << '\n';
	}
}

/**
 * @brief Ordena cada uma das Listas de Adjacência
 *
 * Complexidade O(n^2 * n*lg(n))
 * @pre o vetor de listas (grafo), deve estar alocado
 * @post cada lista do grafo está ordenada
 */
void Grafo::ordena() {
	for(int i = 0; i < qnt_nos; i++) {
		grafo[i].sort();
	}
}

/**
 * @brief Imprime a lista que contém a ordem de acesso dos vertices
 *
 * @pre lista ordem alocada
 * @post lista impressa na saída padrão
 */
void Grafo::printOrdemAcesso() {
	std::cout << "Ordem de acesso: ";
	auto it = ordem.cbegin();
	for (auto fim = std::prev(ordem.cend()); it != fim; it++) {
        std::cout << *it << " - ";
    }
    std::cout << *it << '\n';
}

/**
 * @brief Imprime o vetor de predecessores
 *
 * @pre vetor de predecessores alocada
 * @post vetor de predecessores impressa na saída padrão
 */
void Grafo::printPredecessores() {
	int i;
    std::cout << "Predecessores:   ";
    for (i = 0; i < qnt_nos - 1; i++) {
        if (predecessores[i] == NIL) {
            std::cout << "NIL";
        } else {
            std::cout << predecessores[i];
        }
        std::cout << " - ";
    }
    std::cout << predecessores[i] << '\n';
}

/**
 * @brief Explora um vértice de cor branca, visitando recursivamente
 * todos os vertices adjacentes
 *
 * @param index Vértice a ser explorado, cor branca
 * @pre Somente chamado pela buscaEmProfuntidade
 * @post Vértice index totalmente explorado, cor preto
 */
void Grafo::buscaEmProfundidadeVisit(int index) {
	std::cout << index << '\n';
	ordem.push_back(index);
	cores[index] = CINZA;
	for(auto it : grafo[index]) { // eliminar copias
		if(cores[it.id] == BRANCO) {
			predecessores[it.id] = index;
			buscaEmProfundidadeVisit(it.id);
		}
	}
	cores[index] = PRETO;
}

/**
 * @brief Visita os vértices a partir de um ponto inicial,
 * seguindo o algorítimo de busca em profundidade
 *
 * @param vertice_inicio deve estar dentro dos limites do vértice
 * @pre Grafo inicializado com ler
 * @post ordem de visitação vértices impressa na saída padrão
 */
void Grafo::buscaEmProfundidade(int vertice_inicio) {
	int i;
	//int NIL = std::numeric_limits<int>::max();

	predecessores = new(std::nothrow) int[qnt_nos];
	cores         = new(std::nothrow) cor[qnt_nos];

	// inicialização
	for(i = 0; i < qnt_nos; i++) {
		cores[i] = BRANCO;
		predecessores[i] = NIL;
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

	printOrdemAcesso();
	printPredecessores();

	delete[] cores;
	delete[] predecessores;
	ordem.clear();
}

/**
 * @brief Visita os vértices a partir de um ponto inicial,
 * seguindo o algorítimo de busca em largura
 *
 * @param vertice_inicio deve estar dentro dos limites do vértice
 * @pre Grafo inicializado com ler
 * @post ordem de visitação vértices impressa na saída padrão
 */
void Grafo::buscaEmLargura(int vertice_inicio) {
	int i;
	std::queue<int> fila;
	int max_dist  = std::numeric_limits<int>::max();
	predecessores = new(std::nothrow) int[qnt_nos];
	cores         = new(std::nothrow) cor[qnt_nos];
	dist		  = new(std::nothrow) int[qnt_nos];

	// inicialização
	for(i = 0; i < qnt_nos; i++) {
		cores[i] = BRANCO;
		predecessores[i] = NIL;
		dist[i] = max_dist;
	}
	cores[vertice_inicio] = CINZA;
	dist[vertice_inicio] = 0;
	fila.push(vertice_inicio);
	ordem.push_back(vertice_inicio);

	int cabeca;
	while(!fila.empty()) {
		cabeca = fila.front();
		for(auto it : grafo[cabeca]) { // eliminar copias
			if (cores[it.id] == BRANCO) {
				int salva_id = it.id;
				cores[salva_id] = CINZA;
				dist[salva_id] = dist[cabeca] + 1;
				predecessores[salva_id] = cabeca;
				fila.push(salva_id);
				ordem.push_back(salva_id);
			}
		}
		fila.pop();
		cores[cabeca] = PRETO;
	}
	printOrdemAcesso();
	printPredecessores();

	delete[] cores;
	delete[] dist;
	delete[] predecessores;
	ordem.clear();
}

/**
 * @brief Destrutor da classe Grafo
 *
 * @pre Nenhuma
 * @post Nenhuma
 */
Grafo::~Grafo() {
	for(int i = 0; i < this->qnt_nos; i++) {
		grafo[i].clear();
	}
	delete []grafo;
	debug("Destruindo um grafo\n");
}