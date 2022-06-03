#ifndef PESSOA_H
#define PESSOA_H

#include <QString>

namespace minhaNamespace {
class Pessoa
{
private:
    QString nome;
    int matricula;
    bool ePorNome;
public:
    Pessoa():
        nome(""),
        matricula(0),
        ePorNome(false)
    {

    }

    Pessoa(int matricula, QString nome, bool ePorNome):
        nome(""),
        matricula(0),
        ePorNome(false)
    {
        this->nome = nome;
        this->matricula = matricula;
        this->ePorNome = ePorNome;
    }

    QString getNome() const {
        return nome;
    };

    void setNome(QString nome) {
        this->nome = nome;
    };

    int getMatricula() const {
        return matricula;
    };

    void setMatricula(int matricula) {
        this->matricula = matricula;
    };

    void setPorNome(bool ePorNome) {
        this->ePorNome = ePorNome;
    };

    bool getEPorNome() const {
        return ePorNome;
    }

    friend bool operator >(const Pessoa first, const Pessoa second) {
        if(first.getEPorNome()) {
            if(first.getNome() > second.getNome()) return true;
            return false;
        }

        if(first.getMatricula() > second.getMatricula()) return true;
        return false;
    }

    friend bool operator <(const Pessoa first, const Pessoa second) {
        if(first.getEPorNome()) {
            if(first.getNome() < second.getNome()) return true;
            return false;
        }

        if(first.getMatricula() < second.getMatricula()) return true;
        return false;
    }

    friend bool operator <=(const Pessoa first, const Pessoa second) {
        if(first.getEPorNome()) {
            if(first.getNome() <= second.getNome()) return true;
            return false;
        }

        if(first.getMatricula() <= second.getMatricula()) return true;
        return false;
    }

    friend bool operator >=(const Pessoa first, const Pessoa second) {
        if(first.getEPorNome()) {
            if(first.getNome() >= second.getNome()) return true;
            return false;
        }

        if(first.getMatricula() >= second.getMatricula()) return true;
        return false;
    }
};
}

#endif // PESSOA_H
