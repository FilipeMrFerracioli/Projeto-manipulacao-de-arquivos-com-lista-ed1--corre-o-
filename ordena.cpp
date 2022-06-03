#include "ordena.h"

namespace minhaNamespace {

Ordena::Ordena():
    listaPessoas(),
    ePorNome(false),
    eDecrescente(false)
{

}

Pessoa Ordena::splitPessoa(QString linhaPessoa)
{
    QStringList pessoa = linhaPessoa.split(";");

    //    if(pessoa.length() != 2) throw QString("Arquivo mal formatado.");

    if(pessoa.length() != 2) return Pessoa();

    return Pessoa(pessoa[0].toInt(), pessoa[1], getEPorNome());
}

void Ordena::setLista(Pessoa pessoa)
{
    listaPessoas.inserirInicio(pessoa);
}

LLDE<Pessoa> Ordena::ordenarListaPorTipo()
{
    LLDE<Pessoa> aux = LLDE<Pessoa>();

    for(int i = 0; i < listaPessoas.getQuantidadeDeElementos(); i++) {
        aux.inserirOrdenado(Pessoa(listaPessoas[i].getMatricula(), listaPessoas[i].getNome(), getEPorNome()));
    }

    return aux;
}

QString Ordena::getLista(LLDE<Pessoa> lista) const
{
    QString res = "";
    if(getEDecrescente()) {
        for(int i = lista.getQuantidadeDeElementos() - 1; i >= 0; i--) {
            res += "Matricula: " + QString::number(lista[i].getMatricula());
            res += "\n";
            res += "Nome: " + lista[i].getNome();

            if(i > 0) res += "\n\n";
        }

        return res;
    }

    for(int i = 0; i < lista.getQuantidadeDeElementos(); i++) {
        res += "Matricula: " + QString::number(lista[i].getMatricula());
        res += "\n";
        res += "Nome: " + lista[i].getNome();

        if(i < (lista.getQuantidadeDeElementos() - 1)) res += "\n\n";
    }

    return res;
}

QString Ordena::getListaSemFormatacao(LLDE<Pessoa> lista) const
{
    QString res = "";
    if(getEDecrescente()) {
        for(int i = lista.getQuantidadeDeElementos() - 1; i >= 0; i--) {
            res += QString::number(lista[i].getMatricula());
            res += ";";
            res += lista[i].getNome();

            if(i > 0) res += "\n";
        }

        return res;
    }

    for(int i = 0; i < lista.getQuantidadeDeElementos(); i++) {
        res += QString::number(lista[i].getMatricula());
        res += ";";
        res += lista[i].getNome();

        if(i < (lista.getQuantidadeDeElementos() - 1)) res += "\n";
    }

    return res;
}

}
