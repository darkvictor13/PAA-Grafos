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
                insereOrdenadoRec(cabeca->proximo, dado);
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

        void retiraFim() {
            //if (isVazia()) return ;

            /*
            No<T> *salva_cauda = this->cauda;
            this->cauda->anterior->proximo = nullptr;
            this->cauda = this->cauda->anterior;
            if (this->cauda == nullptr) {
                cabeca = cauda = nullptr;
            }else {
                this->cauda->proximo = nullptr;
            }

            salva_cauda->anterior = nullptr;
            debug("Antes do if\n");
            if (this->cauda->proximo == nullptr
                    && this->cauda->anterior == nullptr) {
                this->cabeca = cauda;
            }
            debug("Depois do if\n");
            delete salva_cauda;
            */
            No<T> *salva_cauda = this->cauda;
            this->cauda = this->cauda->anterior;
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
            if (this->cabeca->proximo == nullptr
                    && this->cabeca->anterior == nullptr) {
                this->cauda = cabeca;
            }
            delete salva_cabeca;
        }

        void mostrar() {
            if (isVazia()) {
                std::cout << "Lista Vazia\n";
                return;
            }

            No<T> *percorre = cabeca;
            while (percorre != cauda) {
                std::cout << percorre->dado << ' ';
                percorre = percorre->proximo;
            }
            std::cout << percorre->dado << '\n';
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

        No<T>& acha() {

        }

        ~Lista() {
            delete cabeca;
            delete cauda;
        }
};

#endif // LISTA
