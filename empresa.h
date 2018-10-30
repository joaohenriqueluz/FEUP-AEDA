#ifndef empresa
#define empresa
#include <vector>
#include <string>
#include "utilizador.h"
#include "projeto.h"

class Empresa {
	vector<Projeto *> projetos;
	vector<Utilizador *> utilizadores;
public:
	void novoUser(string nome);
	void removeUser();
	void novoProjeto();
	void removeProjeto();

};





#endif
