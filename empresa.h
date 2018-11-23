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
	bool removeUtilizador(string nome); //VER SE E PRECISO EXCECAO //FALTA IMPLEMENTAÇAO
	int novoProjeto();
	void removeProjeto(Projeto * proj);
	void imprimeSalarios();
	Utilizador* existeUser(string nome);
	/**
	 * @brief Retorna utilizador com o NIF passado por argumento
	 * @param nif - NIF do utilizador procurado
	 * @return utilizador
	 */
	Utilizador* existeUserID(int nif);
	void existeNIF(int nif);
	/**
	 * @brief Verifica se ja existe esse email, lançando uma excecao se for verdade
	 * @param email - email para verificar se e repetido ou nao
	 */
	void existeEmail(string email);
	void repeteUser(string nome);
	/**
	 * @brief Devolve endereço do projeto com id dado, lançando uma excecao no caso de nao existir ou de o utilizador nao pertencer a esse projeto
	 * @param id - ID do projeto a ser retornado
	 * @return apontador para Projeto com ID pedido
	 */
	Projeto * editProj(int id);
	int getVolume(string nome, Data d1, Data d2) const;
	float getFreq(string nome, Data d1, Data d2) const;
	vector<Projeto *> getProjetos() const { return _projetos; }
	vector<Utilizador*>&  getUsers() { return _utilizadores; }
	void imprimeUser();
	void imprimeCoders();
	void imprimeProjetos();
	void readUsers(string ficheiro);
	/**
	 * @brief Regista utilizadores num ficheiro de texto
	 */
	void writeUsers(string ficheiro);
	/**
	 * @brief Regista projetos num ficheiro de texto
	 */
	void writeProjetos(string ficheiro);
	/**
	 * @brief Regista commits num ficheiro de texto
	 */
	void writeCommits(string ficheiro);
	void readProjetos(string ficheiroP, string ficheiroC);
	void converteJunior(Utilizador* junior);
	void setProjLastID();
};

/*
 * @brief Template para remover um objeto de um vetor
 * @param V - vetor do qual o objeto vai ser removido
 * @param objeto - objeto a remover
 * @return verdadeiro se encontrou objeto no vetor e o eliminou, senao retorna falso
 */
template<class T>
bool removeObjeto(vector<T> & V, T objeto){
	for(unsigned int i = 0; i < V.size(); i++)
			if(V.at(i)== objeto)
			{
				V.erase(V.begin()+i);
				return true;
			}
	return false;
}


#endif //PROJ_AEDA_EMPRESA_H
