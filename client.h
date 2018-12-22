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
    vector<Projeto *> _projetos;

public:
    Client(string nome, string email, unsigned numero, unsigned nif);
    string getNome();
    string getEmail();
    unsigned getContacto();
    unsigned getNif();
    unsigned getNProj();
    void setNome(string nome);
    void setEmail(string email);
    void setContacto(unsigned numero);
    void setNIF(unsigned nif);
    void incrementaProj();
    void addProj(Projeto* proj);
    bool operator<(const Client& c1) const;
    bool operator==(const Client& c1) const;

};


#endif //PROJ_AEDA_CLIENT_H
