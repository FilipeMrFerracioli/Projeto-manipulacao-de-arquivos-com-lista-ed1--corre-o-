#ifndef LLDE_H
#define LLDE_H

#include <QString>
#include <No.h>

namespace minhaNamespace {

template<class T>
class LLDE
{
private:
    int quantidadeDeElementos;
    No<T> *inicio;
    No<T> *fim;

public:
    LLDE<T>():
        quantidadeDeElementos(0),
        inicio(0),
        fim(0)
    {

    }

    ~LLDE<T>()
    {
        while(quantidadeDeElementos != 0) {
            retirarInicio();
        }
    }

    int getQuantidadeDeElementos() const {
        return quantidadeDeElementos;
    }

    T operator [](int pos) const
    {
        if(estaVazio()) throw QString("Lista está vazia!");

        if(pos < 0 || pos >= quantidadeDeElementos) throw QString("Posição inválida!");

        if(pos == 0) return inicio->getDado();

        if(pos == quantidadeDeElementos - 1) return fim->getDado();

        No<T> *aux = inicio;

        for(int i = 0; i < pos; i++) {
            aux = aux->getProximo();
        }

        return aux->getDado();
    }

    void inserirInicio(T elemento)
    {
        try {
            No<T> *novo = new No<T>(elemento);

            if(estaVazio()){
                quantidadeDeElementos++;
                inicio = fim = novo;
                return;
            }

            novo->setProximo(inicio);
            inicio->setAnterior(novo);
            inicio = novo;
            quantidadeDeElementos++;
        } catch (std::bad_alloc const&) {
            throw QString("Erro na alocação de memória");
        }
    }

    T retirarInicio()
    {
        try {
            if(estaVazio()) throw QString ("Lista Vazia, impossível retirar elemento.");

            if(quantidadeDeElementos == 1){
                T x = inicio->getDado();
                delete inicio;
                quantidadeDeElementos--;
                inicio = fim = 0;
                return x;
            }

            No<T> *aux = inicio;
            inicio = aux->getProximo();
            inicio->setAnterior(0);
            quantidadeDeElementos--;
            T x = aux->getDado();
            delete aux;
            return x;
        } catch (std::bad_alloc const&) {
            throw QString("Erro na alocação de memória");
        }
    }

    void inserirFim(T elemento)
    {
        try {
            No<T> *novo = new No<T>(elemento);

            if(estaVazio()) {
                inicio = fim = novo;
                quantidadeDeElementos++;
                return;
            }

            fim->setProximo(novo);
            novo->setAnterior(fim);
            fim = novo;
            quantidadeDeElementos++;
        } catch (std::bad_alloc const&) {
            throw QString("Erro na alocação de memória");
        }
    }

    T retirarFim()
    {
        if(estaVazio()) throw QString("Lista está vazia");

        if(quantidadeDeElementos == 1) {
            T valor = fim->getDado();
            delete fim;
            inicio = fim = 0;
            quantidadeDeElementos = 0;
            return valor;
        }

        No<T> *aux = fim;

        fim = aux->getAnterior();

        fim->setProximo(0);

        T valor = aux->getDado();

        delete aux;

        return valor;
    }

    void inserirPos(int pos, T elemento)
    {
        if(pos < 0) throw QString("Posição inválida!");

        if(pos == quantidadeDeElementos) {
            inserirFim(elemento);
            return;
        }

        if(pos == 0 || quantidadeDeElementos == 0) {
            inserirInicio(elemento);
            return;
        }

        try {
            No<T> *pAux = inicio;

            No<T> *novo = new No<T>(elemento);

            for(int cont = 0; cont < pos - 1; cont++) {
                pAux = pAux->getProximo();
            }

            novo->setProximo(pAux->getProximo());

            pAux->getProximo()->setAnterior(novo);

            pAux->setProximo(novo);
            quantidadeDeElementos++;
        }  catch (std::bad_alloc const&) {
            throw QString("Erro na alocação de memória!");
        }
    }

    T retirarPos(int pos)
    {
        if(estaVazio()) throw QString("Lista vazia!");

        if(pos < 0 || pos >= quantidadeDeElementos) throw QString("Posição inválida!");

        if(pos == 0) return retirarInicio();

        if(pos == quantidadeDeElementos) return retirarFim();

        No<T> *pAux = inicio;

        for(int cont = 0; cont < pos - 1; cont++) {
            pAux = pAux->getProximo();
        }

        No<T> *pAux2 = pAux->getProximo();

        pAux->setProximo(pAux2->getProximo());

        pAux2->getProximo()->setAnterior(pAux);

        T dado = pAux2->getDado();

        delete pAux2;

        quantidadeDeElementos--;

        return dado;
    }

    void inserirOrdenado(T elemento)
    {
        try {
            if(estaVazio()) {
                inserirInicio(elemento);
                return;
            }

            if(inicio->getDado() >= elemento) {
                inserirInicio(elemento);
                return;
            }

            if(fim->getDado() <= elemento) {
                inserirFim(elemento);
                return;
            }

            No<T> *pAux = inicio;

            int cont = 0;

            while(pAux->getDado() < elemento){
                pAux = pAux->getProximo();
                cont++;
            }

            inserirPos(cont, elemento);
        }  catch (std::bad_alloc const&) {
            throw QString("Erro na alocação de memória!");
        }
    }

    bool estaVazio() const
    {
        return (quantidadeDeElementos == 0);
    }
};

}

#endif // LLDE_H
