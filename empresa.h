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
	/**
	 *
	 */
	void novoUtilizador();
	bool removeUtilizador(string nome); //VER SE E PRECISO EXCECAO //FALTA IMPLEMENTAÇAO
	int novoProjeto();
	void removeProjeto(Projeto * proj);
	void imprimeSalarios();
	Utilizador* existeUser(string nome);
	void existeNIF(int nif);
	/**
	 * @brief Verifica se já existe esse email, lançando uma exceção se for verdade
	 * @param email - email para verificar se é repetido ou não
	 */
	void existeEmail(string email);
	void repeteUser(string nome);
	/**
	 * @brief Devolve endereço do projeto com id dado, lançando uma exceção no caso de não existir ou de o utilizador não pertencer a esse projeto
	 * @param id - id do projeto a ser retornado
	 * @return apontador para projeto com id pedido
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
	/**
	 * @brief Regista utilizadores num ficheiro de texto
	 */
	void writeUsers();
	/**
	 * @brief Regista projetos num ficheiro de texto
	 */
	void writeProjetos();
	/**
	 * @brief Regista commits num ficheiro de texto
	 */
	void writeCommits();
	void readProjetos();
	void converteJunior(Utilizador* junior);

};

/*
 * @brief Template para remover um objeto de um vetor
 * @param V - vetor do qual o objeto vai ser removido
 * @param objeto - objeto a remover
 * @return verdadeiro se encontrou objeto no vetor e eliminou-o, se não falso
 */
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
