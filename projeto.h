#ifndef PROJ_AEDA_PROJETO_H
#define PROJ_AEDA_PROJETO_H

#include <vector>
#include <string>
#include <utility>
#include "utilizador.h"

using namespace std;

/**
 * @brief Classe dos commits
 * @param _idC - id do commit
 * @param _userC - autor do commit
 * @param _volume - volume do commit
 * @param _dataC - data do commit
 */
class Commit {
	unsigned int _idC;
	static unsigned int _lastC;
    Utilizador * _userC;
    int _volume;
    Data _dataC;
public:

    /**
     * @brief Construtor da classe Commit
     * @param user - autor do commit
     * @param volume - volume do commit
     * @param d - dia da data do commit
     * @param m - mes da data do commit
     * @param a - ano da data do commit
     */
    Commit(Utilizador* user, int volume, int d, int m, int a);

    /**
	 * @brief Construtor da classe Commit utilizado na leitura de ficheiros
	 * @param user - autor do commit
	 * @param volume - volume do commit
	 * @param d - dia da data do commit
	 * @param m - mes da data do commit
	 * @param a - ano da data do commit
	 */
	Commit(Utilizador *user, int volume, int d, int m, int a, int ID);

	/**
	 * @brief Retorna autor do commit
	 * @return utilizador
	 */
    Utilizador* getUser ()const;

    /**
     * @brief Retorna volume do commit
     * @return volume
     */
    int getVolume () const;

    /**
     * @brief Retorna a data do commit
     * @return data
     */
    Data getData() const;

    /**
     * @brief Retorna ID do commit
     * @return ID
     */
	unsigned int getID() const;

	/**
	 * @brief Encontra o commit com o maior ID e atribui esse valor a variavel _lastC
	 * @param id - maior ID dos commits guardados em ficheiro
	 */
	void setLastID(int id);
};

/**
 * @brief Classe dos branches
 * @param _nome - nome do branch
 * @param _commits - commits do branch
 */
class Branch {
	string _nome;
	vector<Commit> _commits;
public:

	/**
	 * @brief Construtor da classe dos branches
	 * @param nome - nome do branch
	 */
	Branch(string nome) { _nome = nome;}

	/**
	 * @brief Retorna nome do branch
	 * @return nome
	 */
	string getNome() { return _nome;}

	/**
	 * @brief Retorna commits do branch
	 * @return commits
	 */
	vector<Commit> getCommits() { return _commits; }

	/**
	 * @brief Altera o nome do branch
	 * @param nome - nome do branch
	 */
	void setNome(string nome) { _nome = nome;}

	/**
	 * @brief Adiciona um commit ao branch
	 * @param cm - commit a ser adicionado ao branch
	 */
	void adicionaCommit(Commit cm);

	/**
	 * @brief Adiciona commits fornecidos por um vetor de commits ao branch
	 * @param vec - vetor de commits
	 */
	void addCommitVec(vector<Commit> vec);
};

/**
 * @brief Classe utilizada para lancar uma excecao quando nao e encontrado um branch com o nome fornecido
 * @param name - nome do branch que nao foi poss�vel encontrar
 */
class NoSuchBranch{
	string name;
public:
	/**
	 * @brief Construtor da classe da excecao
	 * @param n - nome do branch nao encontrado
	 */
	NoSuchBranch(string n){name = n;}

	/**
	 * @brief Retorna o nome do branch nao encontrado
	 * @return nome
	 */
	string getName() const {return name;}
};

/**
 * @brief Classe utilizada para lancar uma excecao quando e encontrado um branch repetido
 * @param name - nome do branch repetido
 */
class BranchRepetido {
	string name;
public:
	/**
	 * @brief Construtor da classe da excecao
	 * @param n - nome do branch repetido
	 */
	BranchRepetido(string n){name = n;}

	/**
	 * @brief Retorna nome do branch repetido
	 * @return nome
	 */
	string getName() const {return name;}
};

/**
 * @brief Classe dos projetos
 * @param _nome - nome do projeto
 * @param _id - id do projeto
 * @param _chave de acesso - chave de acesso do projeto
 * @param _ranking - utilizadores do projeto
 * @param _tipo - tipo de projeto
 * @param _clientNIF - nif do cliente que encomendou o projeto
 */
class Projeto {
protected:
    string _nome;
    unsigned int _id;
    static unsigned int lastId;
    string _chaveAcesso;
    vector<Commit> _commits;
    vector<Utilizador *> _ranking;
	string _tipo; //Basico ou Avancado
    unsigned _clientNIF;
public:

	/**
	 * @brief Construtor da classe dos projetos
	 * @param nome - nome do projeto
	 * @param tipo - tipo do projeto
	 */
    Projeto(string nome,string tipo);

    /**
     * @brief Destrutor da classe dos projetos
     */
    virtual ~Projeto(){};

    /**
     * @brief Retorna nome do projeto
     * @return nome
     */
    string getNome ();

    /**
     * @brief Altera o nome do projeto
     * @param nome - novo nome
     */
    void setNome(string nome){_nome= nome;}

    /**
     * @brief Altera o tipo do projeto
     * @param tipo - novo tipo
     */
	void setTipo(string tipo) { _tipo = tipo; }

	/**
	 * @brief Retorna tipo de projeto
	 * @return tipo
	 */
	string getTipo() const { return _tipo; }

	/**
	 * @brief Retorna id do projeto
	 * @return id
	 */
    unsigned int getId() const;

    /**
     * @brief Altera o id do projeto;
     * @param id - novo id
     */
    void setID(int id);

    /**
     * @brief Retorna vetor de commits realizados nesse projeto
     * @return commits do projeto
     */
	vector<Commit> getCommits() const { return _commits; }

	/**
	 * @brief Adiciona o commit fornecido ao projeto
	 * @param cm - commit a ser adicionado
	 */
    void addCommit(Commit cm);

    /**
     * @brief Adiciona o utilizador fornecido ao projeto
     * @param user - utilizador a ser adicionado
     */
    void addUtilizador (Utilizador * user);

	/**
	 * @brief Verifica se o Utilizador com o nome dado ja existe no projeto
	 * @param nome - nome do utilizador;
	 * @return verdadeiro de o utilizador de nome "nome" pertence ao vetor de utilizadores do projeto, senao devolve falso
	 */
	bool existeUser(string nome);

	/**
	 * @brief Elimina do vetor de utilizadores do projeto o utilizador de nome "nome"
	 * @param nome - nome do utilizador a remover
	 */
	void removeUser(string nome);

	/**
	 * @brief Desassocia todos os utilizadores a este projeto;
	 */
	void removeAUsers();

	/**
	 * @brief Imprime, no ecra, os utilizadores do projeto
	 */
	void imprimeUsers();

	/**
	 * @brief atribui o valor id a variavel lastId
	 * @param id - maior ID dos projetos guardados em ficheiro
	 */
	void setLastID(int id);

	/**
	 * @brief Imprime, no ecra, os utilizadores juniores e seniores do projeto
	 */
	void imprimeCoders();


	/**
	 * @brief Retorna a chave de acesso do projeto
	 * @return chave de acesso
	 */
    string getChaveAcesso() const;

    /**
     * @brief Altera a chave de acesso do projeto
     * @param chave - nova chave de acesso
     */
    void setChaveAcesso(string chave);

    /**
     * @brief Retorna volume de commits realizados por um utilizador dado entre duas datas em espec�fico ou em todo o projeto conforme as datas que s�o recebidas
     * @param nome_user - nome do utilizador
     * @param d1 - primeiro limite do intervalo de datas a pesquisar
     * @param d2 - segundo limite do intervalo de datas a pesquisar
     * @return volume
     */
	virtual int getVolume(string nome_user, Data d1, Data d2) const;

	/**
	 * @brief Retorna volume adicionado entre duas datas em especifico ou o volume total conforme as datas que s�o recebidas
     * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return volume
	 */
	virtual int getVolumeTotal(Data d1, Data d2) const;


	/**
	 * @brief Imprime, no ecra, os historico dos commits do projeto
	 */
	virtual void imprimeHistorico();

	/**
	 * @brief Retorna a frequencia de commits realizados por um utilizador dado entre duas datas em espec�fico ou em todo o projeto conforme as datas que s�o recebidas
	 * @param user - nome do utilizador
	 * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return frequencia de commits
	 */
	float getFreq(string user, Data d1, Data d2) const;

	/**
	 * @brief Retorna copia do vetor de utilizadores que pertencem ao projeto
	 * @return utilizadores do projeto
	 */
	vector<Utilizador *> getUsers() const { return _ranking; };

	/**
	 * @brief Retorna referencia para o vetor de utilizadores que pertencem ao projeto
	 * @return utilizadores do projeto
	 */
	vector<Utilizador*>& getUserRef() { return _ranking;}

	/**
	 * @brief Procura o commit com id igual a id
	 * @param id - ID do commit procurado
	 * @return vector de commits
	 */
	vector <Commit> filterCommits(vector<int> id);


	/**
	 * @brief Mostra os valores de nome,ID,tipo,chave de Acesso e volume do projeto
	 */
	virtual void getInfo() const;

    /**
     * @brief Retorna nif do cliente que encomendou o projeto
     * @return nif do cliente
     */
    unsigned getClient() const;

    /**
     * @brief Altera o nif cliente que encomendou o projeto
     * @param cl_nif - novo nif cliente que passa a ter a encomenta do projeto associada a si
     */
    void setClient(unsigned cl_nif);

    void setUsers(vector<Utilizador*> newU);
};


/**
 * @brief Classe dos projetos avancados
 * @param _branches - branches do projeto avancado
 */
class Avancado : public Projeto {
	vector<Branch*> _branches;

public:
	/**
	 * @brief Construtor da classe dos projetos avancados
	 * @param nome - nome do projeto
	 */
    Avancado(string nome);

    /**
     * @brief Adiciona ao projeto avancado um branch com o nome fornecido
     * @param nome - nome do branch a ser adicionado
     */
	void addBranch(string nome);

	/**
	 * @brief Remove ao projeto avancado o branch com o nome fornecido
	 * @param nome - nome do branch a ser removido
	 */
	void removeBranch(string nome);

	/**
	 * @brief Faz o merge do branch com o nome fornecido com o MASTER (branch principal)
	 * @param nome - nome do branch
	 */
	void merge(string nome);

	/**
	 * @brief Faz o merge de dois branches
	 * @param nome1 - nome do primeiro branch (branch mantido)
	 * @param nome2 - nome do segundo branch (branch perdido)
	 */
	void merge(string nome1, string nome2);

	/**
	 * @brief Imprime os branches do projeto avancado
	 */
	void imprimeBranches();

	/**
	 *@brief Imprime os commits do projeto avancado tendo em conta os branches
	 */
	void imprimeHistorico();


	/**
	 * @brief Retorna volume de commits realizados por um utilizador dado entre duas datas em espec�fico ou em todo o projeto conforme as datas que s�o recebidas (inclui o volume dos branches)
	 * @param nome_user - nome do utilizador
	 * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return volume
	 */
	int getVolume(string nome_user, Data d1, Data d2) const;

	/**
	 * @brief Retorna volume adicionado entre duas datas em especifico ou o volume total conforme as datas que s�o recebidas (inclui o volume dos branches)
	 * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return volume
	 */
	int getVolumeTotal(Data d1, Data d2) const;


	/**
	 * @brief Lanca excecao se nao existir no projeto nenhum branch com o nome fornecido, senao devolve o branch pedido
	 * @param nome - nome do branch
	 * @return branch
	 */
	Branch* existeBranch(string nome);

	/**
	 * @brief Adiciona um branch ao projeto fornecido por argumento
	 * @param branch - branch a adicionar ao projeto
	 */
	void addBranch_ref(Branch *branch);

	/**
	 * @brief Retorna vetor de branches do projeto avancado
	 * @return branches do projeto
	 */
	vector<Branch *> getBranches() { return _branches; };

	/**
	 * @brief Mostra os valores de nome, ID, tipo, chave de Acesso, volume e Branches do projeto
	 */
	void getInfo() const;

};

/**
 * @brief Classe de apontador de um projeto ??????????????????????????????????????
 * @param projeto - projeto para o qual aponta??????????????????????????????????????
 */
class ProjetoPtr{
	Projeto* projeto;
public:

	/**
	 * @brief Construtor da classe de apontador de um projeto ????????????????????????
	 * @param projeto - projeto para o qual aponta ????????????????????????????
	 */
	ProjetoPtr(Projeto* proj);

	/**
	 * @brief Devolve o projeto para o qual aponta????????
	 * @return projeto
	 */
	Projeto* getProjeto () const;

    /**
     * @brief Retorna nome do projeto
     * @return nome
     */
	string getName() const;

    /**
     * @brief Retorna id do projeto
     * @return id
     */
	unsigned int getID() const;

    /**
     * @brief Retorna nif do cliente que encomendou o projeto
     * @return nif do cliente
     */
	unsigned getClient() const;

	/**
	 * @brief Retorna copia do vetor de utilizadores que pertencem ao projeto
	 * @return utilizadores do projeto
	 */
	vector <Utilizador*> getUsers() const;

    /**
     * @brief Altera o nome do projeto
     * @param nome - novo nome
     */
    void setNome(string nome){projeto->setNome(nome);}

    /**
     * @brief Altera a chave de acesso do projeto
     * @param chave - nova chave de acesso
     */
    void setChaveAcesso(string chave);


};



/**
 * @brief Classe utilizada para lancar uma excecao quando nao e encontrado um projeto com o id fornecido
 * @param id - id do projeto que nao foi poss�vel encontrar
 */
class NoSuchProject{
	unsigned int id;
public:
	/**
	 * @brief Construtor da classe da excecao
	 * @param i - id do projeto nao encontrado
	 */
	NoSuchProject(unsigned int i){id = i;}

	/**
	 * @brief Retorna id do projeto nao encontrado
	 * @return id
	 */
	unsigned int getId() const {return id;}
};

/**
 * @brief Template para ordenar um vetor, tendo em conta as datas dos objetos fornecidas
 * @param vec - vetor a ser ordenado
 * @param objeto - tipo de vetor
 * @param d1 - data mais antiga
 * @param d2 - data mais recente
 */
template <class T>
void sortRanking(vector<Utilizador *> &vec, T *objeto, Data d1 = Data(0, 0, 0), Data d2 = Data(0, 0, 0)) {
	bool troca = false;
	for (unsigned int i = 0; i < vec.size() - 1; i++) {
		if (vec.at(i)->getCargo() == "Gestor")
			continue;
		if (objeto->getVolume(vec.at(i + 1)->getNome(), d1, d2) > objeto->getVolume(vec.at(i)->getNome(), d1, d2))
		{
			std::swap(vec.at(i), vec.at(i + 1));
			troca = true;
		}
		else if (objeto->getVolume(vec.at(i + 1)->getNome(), d1, d2) == objeto->getVolume(vec.at(i)->getNome(), d1, d2))
		{
			if (objeto->getFreq(vec.at(i + 1)->getNome(), d1, d2) > objeto->getFreq(vec.at(i)->getNome(), d1, d2))
			{
				std::swap(vec.at(i), vec.at(i + 1));
				troca = true;
			}
		}
		if (!troca) break;
	}
}


/**
 * @brief Le os commits de todos os utilizadores a partir de um ficheiro
 * @param users - autores dos commits
 * @return vetor de commits
 */
vector<Commit> readCommits(vector <Utilizador *> users,string ficheiroC);



#endif //PROJ_AEDA_PROJETO_H
