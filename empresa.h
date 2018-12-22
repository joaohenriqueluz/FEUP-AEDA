#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include <unordered_set>
#include "projeto.h"
#include "client.h"
#include "BST.h"

using namespace std;

struct  ProjetoPtrHash
{
	int operator() (const ProjetoPtr& proj) const
	{
		int sum = 0;

		for(unsigned i = 0; i < proj.getName().size(); i++){
			sum = 37*sum + proj.getName().at(i);
		}

		return sum;
	}

	bool operator() (const ProjetoPtr& proj1, const ProjetoPtr& proj2) const
	{
		return proj1.getID() == proj2.getID();
	}
};

typedef unordered_set<ProjetoPtr, ProjetoPtrHash, ProjetoPtrHash> HashTabProjetos;

/**
 * @brief Classe da empresa
 * @param _projetos - projetos da empresa
 * @param _utilizadores - utilizadores da empresa
 */
class Empresa {
	vector<Projeto *> _projetos;
	vector<Utilizador *> _utilizadores;
	BST<Client> clients;
	HashTabProjetos pastProjects;
public:

	Empresa():clients(Client("","",0,0)){};f

	/**
	 * @brief Adiciona um novo utilizador a empresa
	 */
	void novoUtilizador();

	/**
	 * @brief Remove o utilizador identificado pelo nome fornecido
	 * @param nome - nome do utilizador
	 * @return verdadeiro se o utilizador � removido com sucesso
	 */
	bool removeUtilizador(string nome);

	/**
	 * @brief Adiciona um novo projeto a empresa
	 * @return id do projeto criado
	 */
	int novoProjeto();

	/**
	 * @brief Remove o projeto fornecido da empresa
	 * @param proj - projeto a remover
	 */
	void removeProjeto(Projeto * proj);

	/**
	 * @brief Imprime no ecra os utilizadores, os respetivos cargos e salarios e o total de todos os salarios
	 */
	void imprimeSalarios();

	/**
	 * @brief Retorna o utilizador identificado pelo nome fornecido
	 * @param nome - nome do utilizador
	 * @return utilizador
	 */
	Utilizador* existeUser(string nome);

	/**
	 * @brief Retorna utilizador com o NIF passado por argumento
	 * @param nif - NIF do utilizador procurado
	 * @return utilizador
	 */
	Utilizador* existeUserID(int nif);

	/**
	 * @brief Lanca excecao se nao existir na empresa nenhum utilizador com o NIF fornecido
	 * @param nif - NIF do utilizador
	 */
	void existeNIF(int nif);


	/**
	 * @brief Verifica se ja existe esse email, lan�ando uma excecao se for verdade
	 * @param email - email para verificar se e repetido ou nao
	 */
	void existeEmail(string email);

	/**
	 *
	 * @param nome
	 */
	void repeteUser(string nome);
	/**
	 * @brief Devolve endere�o do projeto com id dado, lan�ando uma excecao no caso de nao existir ou de o utilizador nao pertencer a esse projeto
	 * @param id - ID do projeto a ser retornado
	 * @return apontador para Projeto com ID pedido
	 */
	Projeto * editProj(int id);

	/**
	 * @brief Retorna o volume total das contribuicoes do utilizador ,identificado pelo nome fornecido, feitas entre duas datas
	 * @param nome - nome do utilizador
	 * @param d1 - primeira data
	 * @param d2 - segunda data
	 * @return volume
	 */
	int getVolume(string nome, Data d1, Data d2) const;

	/**
	 * @brief Retorna a frequencia de commits feitos  em todos os projetos pelo utilizador, identificado pelo nome fornecido, entre duas datas
	 * @param nome - nome do utilizador
	 * @param d1 - primeira data
	 * @param d2 - primeira data
	 * @return frequencia
	 */
	float getFreq(string nome, Data d1, Data d2) const;

	/**
	 * @brief Retorna os projetos da empresa
	 * @return projetos
	 */
	vector<Projeto *> getProjetos() const { return _projetos; }

	/**
	 * @brief Retorna os utilizadores da empresa
	 * @return utilizadores
	 */
	vector<Utilizador*>&  getUsers() { return _utilizadores; }

	/**
	 * @brief Imprime, no ecra, todos os utilizadores da empresa
	 */
	void imprimeUser();

	/**
	 * @brief Imprime, no ecra, todos os utilizadores juniores e seniores da empresa
	 */
	void imprimeCoders();

	/**
	 * @brief Imprime, no ecra, todos os projetos da empresa
	 */
	void imprimeProjetos();

	/**
	 * @brief Retira informacao sobre os utilizadores da empresa a partir de um ficheiro
	 * @param ficheiro - ficheiro lido
	 */
	void readUsers(string ficheiro);

	/**
	 * @brief Regista utilizadores num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeUsers(string ficheiro);

	/**
	 * @brief Regista projetos num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeProjetos(string ficheiro);

	/**
	 * @brief Regista commits num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeCommits(string ficheiro);

	/**
	 * @brief Retira informacao sobre os projetos da empresa a partir de um ficheiro
	 * @param ficheiroP - ficheiro de projetos
	 * @param ficheiroC - ficheiro de commits
	 */
	void readProjetos(string ficheiroP, string ficheiroC);

	/**
	 * @brief Converte um utilizador junior em senior
	 * @param junior - junior a ser convertido
	 */
	bool converteJunior(Utilizador* junior);

	/**
	 * @brief Encontra o projeto com o maior id e atribui esse valor a variavel lastId
	 */
	void setProjLastID();

	void addClient(Client c);

	void removeClient(Client c);
};

/**
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
