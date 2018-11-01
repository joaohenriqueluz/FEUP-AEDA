#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include "utilizador.h"
#include "projeto.h"

using namespace std;

class Empresa {
    vector<Projeto *> _projetos;
    vector<Utilizador *> _utilizadores;
public:
    void novoUtilizador();
    void removeUtilizador(Utilizador * UtilizadorARemover);
    void novoProjeto();
    void removeProjeto(Projeto * proj);
    void imprimeSalarios();	 //Gestores têm salarios?

};

#endif //PROJ_AEDA_EMPRESA_H
