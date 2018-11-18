#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include "projeto.h"

using namespace std;

class Empresa {
	vector<Projeto *> _projetos;
	vector<Utilizador *> _utilizadores;
public:
	void novoUtilizador();
	bool removeUtilizador(string nome); //VER SE E PRECISO EXCECAO //FALTA IMPLEMENTA�AO
	int novoProjeto();
	void removeProjeto(Projeto * proj);
	void imprimeSalarios();
	Utilizador* existeUser(string nome);
	void existeNIF(int nif);
	/**
	 * Lan�a exce��o se ja existe um utilizador com _email igual a email.
	 * @param email
	 */
	void existeEmail(string email);
	void repeteUser(string nome);
	/**
	 *
	 * @param id ID do projeto a ser retornado
	 * @return apontador para Projeto com ID igual a id
	*/
	Projeto * editProj(int id);
	int getVolume(string nome, Data d1, Data d2) const;
	float getFreq(string nome, Data d1, Data d2) const;
	vector<Projeto *> getProjetos() const { return _projetos; }
	vector<Utilizador*>&  getUsers() { return _utilizadores; }
	void imprimeUser();
	void imprimeCoders();
	void imprimeProjetos();
	void readUsers();
	void writeUsers();
	void readProjetos();
	void writeProjetos();
	void writeCommits();
	void converteJunior(Utilizador* junior);

};

template<class T>
bool removeObjeto(vector<T> & V, T objeto){
	for(unsigned int i = 0; i < V.size(); i++)
			if(V.at(i)== objeto)
			{
				cout<< "Removido.\n";
				V.erase(V.begin()+i);
				return true;
			}
	return false;
}


#endif //PROJ_AEDA_EMPRESA_H
