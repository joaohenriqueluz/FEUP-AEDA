//
// Created by Francisco Rodrigues on 30/10/2018.
//

#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include "utilizador.h"
#include "projeto.h"

using namespace std;

class Empresa {
    vector<Projeto *> projetos;
    vector<Utilizador *> utilizadores;
public:
    void novoUser(string nome);
    void removeUser();
    void novoProjeto();
    void removeProjeto();

};

#endif //PROJ_AEDA_EMPRESA_H
