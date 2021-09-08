/**
 * @file lista.hpp
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief uma lista generica que utiliza templates
 * 
 * Podendo servir como fila, pilha ou uma lista simple
 * @version 0.1
 * @date 03/09/2021
 */

#ifndef LISTA
#define LISTA

#include <iostream>
#include "../utils/debug.hpp"

template<class T>
struct No {
    T dado;
    struct No *proximo;
    struct No *anterior;

    friend std::ostream& operator << (std::ostream &out, const No<T> &other) {
        out << other.dado;
        return out;
    }

    No(No<T> *a, No<T> *p, T d) {
        this->dado = d;
        this->anterior = a;
        this->proximo = p;
    }

    No(T d) {
        this->dado = d;
        this->anterior = nullptr;
        this->proximo = nullptr;
    }

    No() {
        this->dado = 0;
        this->anterior = nullptr;
        this->proximo = nullptr;
    }
};

template<class T>
/**
 * @brief Classe que implementa uma lista encadeada simples com cabeça e cauda
 * 
 * Podendo ser utilizada como Fila, Pilha, ou uma lista simples a partir das
 * inserções e remoções
 */
class Lista {
    private:
        No<T> *cabeca;
        No<T> *cauda;

        void encadeia(No<T> *anterior, No<T> *proximo, T dado) {
            No<T> *novo = new No<T>(anterior, proximo, dado);

            anterior->proximo = novo;
            proximo->anterior = novo;
        }

        

        void insereOrdenadoRec(No<T> *atual, T dado) {
            if (atual->dado >= dado) {
                encadeia(atual->anterior, atual, dado);
            } else if (atual == cauda) {
                insereFim(dado);
            } else {
                insereOrdenadoRec(atual->proximo, dado);
            }
        }

    public:
        Lista() {
            this->cabeca = nullptr;
            this->cauda = nullptr;
        }

        bool isVazia() {
            return (this->cabeca == nullptr);
        }

        No<T>* naPos(int num) {
            int pos = 0;
            No<T> *p = this->cabeca;
            while (p) {
                if (pos == num) {
                    return p;
                }
                pos++;
                p = p->proximo;
            }
            return nullptr;
        }

        bool operator != (const Lista<T> &other) {
            No<T> *atual = this->cabeca;
            No<T> *outra = other.cabeca;
            while (atual && outra) {
                if (atual->dado != outra->dado) {
                    return false;
                }
            }
            return true;
        }

        bool operator == (const Lista<T> &other) {
            return !(this != other);
        }
        
        No<T> *inicio() {
            return this->cabeca;
        }

        No<T> *fim() {
            return this->cauda;
        }

        No<T>* prox( No<T> *p) {
            return p->proximo;
        }

        No<T>* ant( No<T> *p) {
            return p->anterior;
        }
        No<T> *acha(T dado) {
            if (isVazia()) {
                return nullptr;
            }
            No<T> *p = cabeca;
            while(p && !(p->dado == dado)) {
                p = p->proximo;
            }
            return p;
        }

        void insereInicio(T dado) {
            No<T> *novo = new No<T>(dado);
            if (isVazia()) {
                this->cabeca = novo;
                this->cauda = novo;
            } else {
                novo->proximo = this->cabeca;
                this->cabeca->anterior = novo;
                this->cabeca = novo;
            }
        }

        void insereOrdenado(T dado) {
            if (isVazia() || this->cabeca->dado >= dado) {
                insereInicio(dado);
            } else {
                insereOrdenadoRec(cabeca, dado);
            }
        }

        // usar na fila
        void insereFim(T dado) {
            No<T> *novo = new No<T>(dado);
            if (isVazia()) {
                this->cabeca = novo;
                this->cauda = novo;
            } else {
                novo->anterior = this->cauda;
                this->cauda->proximo = novo;
                this->cauda = novo;
            }
        }
        
        void desencadeia(No<T> *elemento) {
            No<T> *ant = elemento->anterior;
            No<T> *prox = elemento->proximo;

            if (elemento == this->cabeca) {
                this->cabeca = prox;
                this->cabeca->anterior = nullptr;
            } else if (elemento == this->cauda) {
                this->cauda = ant;
                this->cauda->proximo = nullptr;
            } else {
                ant->proximo = prox;
                prox->anterior = ant;
            }

            elemento->anterior = elemento->proximo = nullptr;
            delete elemento;
        }

        void retiraFim() {
            if (isVazia()) return ;

            No<T> *salva_cauda = this->cauda;
            this->cauda = this->cauda->anterior;
            if (this->cauda == nullptr) {
                cabeca = cauda = nullptr;
            }else {
                this->cauda->proximo = nullptr;
            }

            salva_cauda->anterior = nullptr;
            if (this->cauda == nullptr) {
                this->cabeca = cauda;
            }
            delete salva_cauda;
        }

        // usar na fila
        void retiraInicio() {
            if (isVazia()) return ;

            No<T> *salva_cabeca = this->cabeca;
            this->cabeca = this->cabeca->proximo;
            if (this->cabeca == nullptr) {
                cabeca = cauda = nullptr;
            } else {
                this->cabeca->anterior = nullptr;
            }

            salva_cabeca->proximo = nullptr;
            if (this->cabeca == nullptr) {
                this->cauda = cabeca;
            }
            delete salva_cabeca;
        }

        void retira(T dado) {
            desencadeia(acha(dado));
        }

        void mostrar(const std::string sep) {
            if (isVazia()) {
                std::cout << "Lista Vazia\n";
                return;
            }

            No<T> *percorre = cabeca;
            while (percorre != cauda) {
                std::cout << percorre->dado << sep;
                percorre = percorre->proximo;
            }
            std::cout << percorre->dado << "\n";
        }

        void mostrarInvertido() {
            if (isVazia()) {
                std::cout << "Lista Vazia\n";
                return;
            }

            No<T> *percorre = cauda;
            while (percorre != cabeca) {
                std::cout << percorre->dado << ' ';
                percorre = percorre->anterior;
            }
            std::cout << percorre->dado << '\n';
        }

        int tam() {
            if (isVazia()) {
                return 0;
            }
            int qnt = 1;
            No<T> *p = cabeca;
            while(p != cauda) {
                qnt++;
                p = p->proximo;
            }
            return qnt;
        }

        void limpar() {
            delete cabeca;
            cabeca = cauda = nullptr;
        }

        
        ~Lista() {
            delete cabeca;
        }
};

#endif // LISTA
