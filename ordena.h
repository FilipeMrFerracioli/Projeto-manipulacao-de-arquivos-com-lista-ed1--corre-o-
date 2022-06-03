#ifndef ORDENA_H
#define ORDENA_H

#include <QStringList>
#include <LLDE.h>
#include <pessoa.h>

namespace minhaNamespace {
class Ordena
{
private:
    LLDE<Pessoa> listaPessoas;
    bool ePorNome;
    bool eDecrescente;
public:
    Ordena();
    //    Ordena(QString linhaPessoa, bool ePorNome);

    void setPorNome(bool ePorNome) {
        this->ePorNome = ePorNome;
    };

    bool getEPorNome() const {
        return ePorNome;
    }

    void setEDecrescente(bool eDecrescente) {
        this->eDecrescente = eDecrescente;
    }

    bool getEDecrescente() const {
        return eDecrescente;
    }

    Pessoa splitPessoa(QString linhaPessoa);

    void setLista(Pessoa pessoa);

    LLDE<Pessoa> ordenarListaPorTipo();

    QString getLista(LLDE<Pessoa> lista) const;
    QString getListaSemFormatacao(LLDE<Pessoa> lista) const;
};
}

#endif // ORDENA_H
