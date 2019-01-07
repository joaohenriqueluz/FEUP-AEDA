#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include <list>
#include <queue>
#include <unordered_set>
#include "projeto.h"
#include "client.h"
#include "BST.h"
#include "ticket.h"


using namespace std;

//TODO: documentacao desta parte
struct  ProjetoPtrHash
{
	unsigned int operator() (const ProjetoPtr& proj) const
	{
		return proj.getID()*2654435761 % (2^32);
	}

	bool operator() (const ProjetoPtr& proj1, const ProjetoPtr& proj2) const
	{
		return proj1.getID() == proj2.getID();
	}
};
//TODO: documentacao desta parte
typedef unordered_set<ProjetoPtr, ProjetoPtrHash, ProjetoPtrHash> HashTabProjetos;


/**
 * @brief Classe da empresa
 * @param _projetos - projetos da empresa
 * @param _utilizadores - utilizadores da empresa
 * @param _clients - clientes da empresa
 * @param _pasteProjects - projetos da empresa terminados
 * @param _tickets - tickets dos projetos em desenvolvimento
 */
class Empresa {
	vector<Projeto *> _projetos;
	vector<Utilizador *> _utilizadores;
	BST<Client> _clients;
	HashTabProjetos _pastProjects;
	priority_queue<Ticket> _tickets;
public:

	Empresa():_clients(Client("","",0,0)){};

	/**
	 * @brief Adiciona um novo utilizador a empresa
	 */
	void novoUtilizador();

	/**
	 * @brief Remove o utilizador identificado pelo nome fornecido
	 * @param nome - nome do utilizador
	 * @return verdadeiro se o utilizador e removido com sucesso
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
	 * @brief Adiciona o projeto fornecido à empresa
	 * @param proj - projeto a adicionar
	 */
	void addProject (Projeto* proj);

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
	 * @brief Verifica se ja existe esse email, lancando uma excecao se for verdade
	 * @param email - email para verificar se e repetido ou nao
	 */
	void existeEmail(string email);

	/**
	 * @brief Verifica se o utilizador com nome fornecido já existe, lancando execeçao se não existir nenhum com esse nome
	 * @param nome - nome do utilizador a verigicar se já existe ou não
	 */
	void repeteUser(string nome);

	/**
	 * @brief Devolve endereco do projeto com id dado, lancando uma excecao no caso de nao existir ou de o utilizador nao pertencer a esse projeto
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
	 * @return verdadeiro se não conseguir realizar a conversão, caso contrário retorna falso
	 */
	bool converteJunior(Utilizador* junior);

	/**
	 * @brief Encontra o projeto com o maior id e atribui esse valor a variavel lastId
	 */
	void setProjLastID();

	/**
	 * @brief Adiciona cliente à árvore binária com os clientes da empresa
	 * @param c - cliente a adicionar à empresa
	 */
	void addClient(Client c);

	/**
	 * @brief Remove cliente da árvore binária com os clientes da empresa
	 * @param c - cliente a remover da empresa
	 */
	void removeClient(Client c);

	/**
	 * @brief Procura cliente fornecido e devolve os projetos encomendados por este
	 * @param c - cliente
	 * @return projetos encomendados pelo cliente
	 */
	vector<Projeto*> getProjectsOfClient(Client c);

	/**
	 * @brief Procura cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @return cliente
	 */
	Client getClient (unsigned nif);

	/**
	 * @brief Adiciona projeto ao cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @param proj - projeto a adicionar ao cliente
	 */
	void addProjectToClient (unsigned nif, Projeto * proj);

	/**
	 * @brief Remove projeto do cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @param id_proj - id do projeto a remover do cliente
	 */
	void removeProjectFromClient (unsigned nif, unsigned int id_proj);

	/**
	 * @brief Alterar numero do contacto do cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @param novo_num - novo numero de contacto
	 * @return verdadeiro se encontrou o cliente, caso contrario falso
	 */
	bool modifyContacto (unsigned nif, unsigned novo_num);

	/**
	 * @brief Altera chave de acesso do projeto terminado
	 * @param proj - projeto
	 * @param novaChave - nova chave de acesso
	 */
	void alterarChavePastProj (Projeto* proj, string novaChave);

	/**
	 * @brief Altera nome do projeto terminado
	 * @param proj
	 * @param novoNome
	 */
	void alterarNomePastProj (Projeto* proj, string novoNome);

	/**
	 * @brief Coloca projeto na tabela de dispersão dos projetos terminados, removendo-o dos projetos em desenvolvimento
	 * @param id - id do projeto em desenvolvimento a passar a projeto terminado
	 */
	void toPastProject (unsigned int id);

	/**
	 * @brief Coloca projeto no vetor de projetos em desenvolvimento, removendo-o dos projetos terminados
	 * @param id - id do projeto terminado a ser reativado
	 */
	void toWorkingProject (unsigned int id);

	/**
	 * @brief Adiciona projeto à tabela de dispersão dos projetos terminados
	 * @param proj - projeto a ser adicionado aos projetos terminados
	 */
	void addPastProject (Projeto* proj);

	/**
	 * @brief Remove projeto da tabela de dispersão dos projetos terminados, lançando exceção se não existir nenhum projeto com o id fornecido
	 * @param proj - projeto a ser removido dos projetos terminados
	 */
	void removePastProject (unsigned int id);

	/**
	 * @brief Procura o projeto terminado com id fornecido, lançando exceção se não o encontrar
	 * @param id - id do projeto a procurar
	 * @return projeto terminado com id fornecido
	 */
	Projeto* getPastProject (unsigned int id);

	/**
	 * @brief Procura os projetos terminados nos quais o utilizador com NIF fornecido participou
	 * @param NIF - NIF do utilizador
	 * @return lista dos projetos terminados
	 */
	list<unsigned int> pastProjectsWithUser (int NIF);

	/**
	 * @brief Procura os projetos terminados os quais o cliente com NIF fornecido encomendou
	 * @param NIF - NIF do cliente
	 * @return lista dos projetos terminados
	 */
	list<unsigned int> pastProjectsWithClient (unsigned int NIF);

	/**
	 * @brief Retorna o projeto mais urgente
	 * @return projeto
	 */
	Projeto* getMostUrgent();

	/**
	 * @brief Retorna o id do proximo proximo projeto com ticket exequivel para o utilizador fornecido
	 * @param user - utilizador a saber proximo projeto a realizar
	 * @return id do projeto a realizar a seguir
	 */
	int getNextTicket(Utilizador* user);

	/**
	 * @brief Remove o ticket correspondente ao projeto fornecido
	 * @param P - Projeto associado ao ticket a ser removido
	 * @return verdaderio se a operação é efetuada com sucesso, senao retorna falso
	 */
	bool removeTicket(Projeto* P);

	/**
	 * @brief Imprime todos os clientes e o numero de projetos encomendados por ordem descrecente;
	 */
	void printClientNumProj();

	/**
	 * @brief Imprime todos os projetos emcomendados pelo cliente identificado pelo NIF fornecido
	 * @param NIF - NIF do cliente
	 */
	void printClientProj(unsigned NIF);

	/**
	 * @brief Atualiza o projeto atual dos utilizadores do projeto identificado pelo id fornecido
	 * @param id - ID do projeto
	 */
	void updateCurretProj(int id);

	/**
	 * @brief Imprime todos os projetos terminados, presentes na tabela de dispersao
	 */
	void printPastproj();

	/**
	 * @brief Verifica se existe um projeto terminado com o id fornecido;
	 * @param id - id do projeto procurado
	 * @return Verdadeiro se existir projeto com o id dado, senao retorna falso;
	 */
	bool existePastProj(int id);

	/**
	 * @brief Adiciona novo ticket a fila de prioridade
	 * @param t - novo ticket a adicionar
	 */
	void addTicket(Ticket t);

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
