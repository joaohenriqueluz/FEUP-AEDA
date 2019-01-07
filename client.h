#ifndef PROJ_AEDA_CLIENT_H
#define PROJ_AEDA_CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "projeto.h"

using namespace std;

class Client {
    string _nome;
    string _email;
    int _numeroProj;
    unsigned _contacto;
    unsigned _NIF;
    vector<Projeto*> _projetos;

public:
    Client(string nome, string email, unsigned numero, unsigned nif);
    string getNome() const;
    string getEmail() const;
    unsigned getContacto() const;
    unsigned getNif() const;
    int getNProj() const;
    vector<Projeto*> getProjetos() const;
    void setNome(string nome);
    void setEmail(string email);
    void setContacto(unsigned numero);
    void setNIF(unsigned nif);
    void incrementaProj();
    void addProj(Projeto* proj);
    void removeProj (unsigned id);
    bool operator<(const Client& c1) const;
    bool operator==(const Client& c1) const;
    void printProjects();
    void setNProj(int n);

};


#endif //PROJ_AEDA_CLIENT_H
