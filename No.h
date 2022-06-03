#ifndef NO_H
#define NO_H

#include <QString>

namespace minhaNamespace {

template<class T>
class No
{
private:
    T dado;
    No *proximo;
    No *anterior;
public:
    No():
        dado(0),
        proximo(0),
        anterior(0)
    {
        // erto?
        if(proximo) delete proximo;
        if(anterior) delete anterior;
    }

    No(T valor):
        dado(valor),
        proximo(0),
        anterior(0)
    {
        this->dado = valor;
    }

    ~No()
    {

    }

    void setDado(T newDado)
    {
        dado = newDado;
    }

    T getDado() const
    {
        return dado;
    }

    No *getProximo() const
    {
        return proximo;
    }

    void setProximo(No *Proximo)
    {
        this->proximo = Proximo;
    }

    No *getAnterior() const
    {
        return anterior;
    }

    void setAnterior(No *Anterior)
    {
        this->anterior = Anterior;
    }
};

}

#endif // NO_H
