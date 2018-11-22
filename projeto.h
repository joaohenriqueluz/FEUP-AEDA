#ifndef PROJ_AEDA_PROJETO_H
#define PROJ_AEDA_PROJETO_H

#include <vector>
#include <string>
#include "utilizador.h"

using namespace std;

class Commit {
	unsigned int _idC;
	static unsigned int _lastC;
    Utilizador * _userC;
    int _volume;
    Data _dataC;
public:
    Commit(Utilizador* user, int volume, int d, int m, int a);
    Commit(Utilizador *user, int volume, int d, int m, int a, int ID);
    Utilizador* getUser ()const;
    int getVolume () const;
    Data getData() const;
	unsigned int getID() const;
};

class Branch {
	string _nome;
	vector<Commit> _commits;
public:
	Branch(string nome) { _nome = nome;}
	string getNome() { return _nome;}
	vector<Commit> getCommits() { return _commits; }
	void setNome(string nome) { _nome = nome;}
	void adicionaCommit(Commit cm);
	void addCommitVec(vector<Commit> vec);
};

class NoSuchBranch{
	string name;
public:
	NoSuchBranch(string n){name = n;}
	string getName() const {return name;}
};

class BranchRepetido{
	string name;
public:
	BranchRepetido(string n){name = n;}
	string getName() const {return name;}
};


class Projeto {
protected:
    string _nome;
    unsigned int _id;
    static unsigned int lastId;
    string _chaveAcesso;
    vector<Commit> _commits;
    vector<Utilizador *> _ranking;
	string _tipo; //Basico ou Avancado
public:
    Projeto(string nome,string tipo);
    virtual ~Projeto(){};
    string getNome ();
    /**
     * Atribui o valor (nome) ao atributo _nome;
     * @param nome
     */
    void setNome(string nome){_nome= nome;}
	void setTipo(string tipo) { _tipo = tipo; }
	string getTipo() const { return _tipo; }
    unsigned int getId();
    /**
     * Altera valor de _id para id;
     * @param id novo valor para _id
     */
    void setID(int id);
	vector<Commit> getCommits() const { return _commits; }
    void addCommit(Commit cm);
    void addUtilizador (Utilizador * user);
    /**
        * @brief Verifica se o Utilizador de nome "nome" ja existe no projeto;
        * @param nome - nome do utilizador;
        * @return verdadeiro de o utilizador de nome "nome" pertence ao vetor de utilizadores do projeto, senao devolve falso;
        */
       bool existeUser(string nome);
       /**
        * @brief Elimina do vetor de utilizadores do projeto o utilizador de nome "nome"
        * @param nome
        */
       void removeUser(string nome);
       /**
        * @brief Desassocia todos os utilizadores a este projeto;
        */
       void removeAUsers();
	void imprimeUsers();
	void imprimeCoders();
	/**
	 * Retorna a chave de acesso do projeto
	 * @return _chaveAcesso
	 */
    string getChaveAcesso();
    /**
     * Atribui o valor chave a _chaveAcesso
     * @param chave - novo valor para a _chaveAcesso
     */
    void setChaveAcesso(string chave);
    /**
     * Devolve o volume total dos commits do utilizador nome_user
     * Se d1 e d2 forem iguas a (0,0,0) devolve o volume total,caso contrario devolve o volume total dos commits feitos entre d1 e d2
     * @param nome_user
     * @param d1 - data mais antiga
     * @param d2 - data mais recente
     * @return volume - volume calculado
     */
	virtual int getVolume(string nome_user, Data d1, Data d2) const;

	/**
	 * Devolve o volume total dos commits do projeto.
     * Se d1 e d2 forem iguas a (0,0,0) devolve o volume total,caso contrario devolve o volume total dos commits feitos entre d1 e d2
	 * @param d1 - data mais antiga
	 * @param d2 - data mais recente
	 * @return volume - volume calculado
	 */
	virtual int getVolumeTotal(Data d1, Data d2) const;
	virtual void imprimeHistorico();

	float getFreq(string user, Data d1, Data d2) const;

	vector<Utilizador *> getUsers() { return _ranking; };

	vector<Utilizador*>& getUserRef() { return _ranking;}

	/**
	 * Procura o commit com id igual a id
	 * @param id ID do commit procurado
	 * @return vector de commits
	 */
	vector <Commit> filterCommits(vector<int> id);

	/**
	 * L� os commits a partir de um ficheiro
	 * @param users Autores dos commits
	 * @param id ID dos PROJETOS OU COMMITS
	 */
	void readCommits(vector <Utilizador *> users, vector <int> id);

	/**
	 * Mostra os valores de nome,ID,tipo,chave de Acesso e volume do projeto
	 */
	virtual void getInfo();

};

vector<Commit> readCommits(vector <Utilizador *> users);


class Avancado : public Projeto {
	vector<Branch*> _branches;

    //branches (cria/elimina/merge-senior)
public:
    Avancado(string nome);
	void addBranch(string nome);
	void removeBranch(string nome);
	void merge(string nome);
	void merge(string nome1, string nome2);
	void imprimeBranches();
	void imprimeHistorico();
	/**
	 * Devolve o volume total dos commits (incluindo nos branches) do utilizador nome_user
	 * Se d1 e d2 forem iguas a (0,0,0) devolve o volume total,caso contrario devolve o volume total dos commits feitos entre d1 e d2
	 * @param nome_user
	 * @param d1 - data mais antiga
	 * @param d2 - data mais recente
	 * @return volume - volume calculado
	 */
	int getVolume(string nome_user, Data d1, Data d2) const;

	/**
	 * Devolve o volume total dos commits (incluindo nos branches)
	 * Se d1 e d2 forem iguas a (0,0,0) devolve o volume total,caso contrario devolve o volume total dos commits feitos entre d1 e d2
	 * @param nome_user
	 * @param d1 - data mais antiga
	 * @param d2 - data mais recente
	 * @return volume - volume calculado
	 */
	int getVolumeTotal(Data d1, Data d2) const;

	Branch* existeBranch(string nome);

	/**
	 * Adiciona um branch ao projeto fornecido por argumento
	 * @param branch
	 */
	void addBranch_ref(Branch *branch);

	/**
	 * Devolve vetor de branches do projeto avancado
	 * @return vetor de branches
	 */
	vector<Branch *> getBranches() { return _branches; };

	/**
	 * Mostra os valores de nome, ID, tipo, chave de Acesso, volume e Branches do projeto
	 */
	void getInfo();

};


class NoSuchProject{
	unsigned int id;
public:
	NoSuchProject(unsigned int i){id = i;}
	unsigned int getId() const {return id;}
};


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
 * Devolve vetor de Utilizadores com NIFs do vetor de NIFs fornecido
 * @param id  - vetor de NIF dos utilizadores
 * @param users  - vetor de utilizadores a pesquisar
 * @return Utilizadores cujo o NIF pertence ao vetor fornecido
 */
vector <Utilizador *> findUtilizadores(vector <int> id, vector <Utilizador *> users);

#endif //PROJ_AEDA_PROJETO_H
