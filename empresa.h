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
	int novoProjeto();
	void removeProjeto(Projeto * proj);
	void imprimeSalarios();
	Utilizador* existeUser(string nome, bool & existe);
	Utilizador* existeUser(string nome);
	int getVolume(string nome, Data d1, Data d2) const;
	float getFreq(string nome, Data d1, Data d2) const;
	vector<Projeto *> getProjetos() const { return _projetos; }
	vector<Utilizador*>&  getUsers() { return _utilizadores; }
	void imprimeUser();
	void imprimeCoders();
	void imprimeProjetos();
	void readUsers();
	void readProjetos();
	void converteJunior(Utilizador* junior);
	Avancado* converteBasico(Projeto * proj);

};

template<class T>
void removeObjeto(vector<T> & V, T objeto){
	for(unsigned int i = 0; i < V.size(); i++)
			if(V.at(i)== objeto)
			{
				cout<< "Removido.\n";
				V.erase(V.begin()+i);
			}
}


#endif //PROJ_AEDA_EMPRESA_H
