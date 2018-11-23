#ifndef PROJ_AEDA_PROJETO_H
#define PROJ_AEDA_PROJETO_H

#include <vector>
#include <string>
#include <utility>
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
	void setLastID(int id);
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
    unsigned int getId();

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
	 *
	 * @param cm
	 */
    void addCommit(Commit cm);

    /**
     *
     * @param user
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

	void imprimeUsers();

	void setLastID(int id);


	void imprimeCoders();


	/**
	 * @brief Retorna a chave de acesso do projeto
	 * @return chave de acesso
	 */
    string getChaveAcesso();

    /**
     * @brief Altera a chave de acesso do projeto
     * @param chave - nova chave de acesso
     */
    void setChaveAcesso(string chave);

    /**
     * @brief Retorna volume de commits realizados por um utilizador dado entre duas datas em específico ou em todo o projeto conforme as datas que são recebidas
     * @param nome_user - nome do utilizador
     * @param d1 - primeiro limite do intervalo de datas a pesquisar
     * @param d2 - segundo limite do intervalo de datas a pesquisar
     * @return volume
     */
	virtual int getVolume(string nome_user, Data d1, Data d2) const;

	/**
	 * @brief Retorna volume adicionado entre duas datas em especifico ou o volume total conforme as datas que são recebidas
     * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return volume - volume calculado
	 */
	virtual int getVolumeTotal(Data d1, Data d2) const;


	virtual void imprimeHistorico();

	/**
	 * @brief Retorna a frequencia de commits realizados por um utilizador dado entre duas datas em específico ou em todo o projeto conforme as datas que são recebidas
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
	vector<Utilizador *> getUsers() { return _ranking; };

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
	virtual void getInfo();

};



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
	 * @brief Retorna volume de commits realizados por um utilizador dado entre duas datas em específico ou em todo o projeto conforme as datas que são recebidas (inclui o volume dos branches)
	 * @param nome_user - nome do utilizador
	 * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return volume
	 */
	int getVolume(string nome_user, Data d1, Data d2) const;

	/**
	 * @brief Retorna volume adicionado entre duas datas em especifico ou o volume total conforme as datas que são recebidas (inclui o volume dos branches)
	 * @param d1 - primeiro limite do intervalo de datas a pesquisar
	 * @param d2 - segundo limite do intervalo de datas a pesquisar
	 * @return volume - volume calculado
	 */
	int getVolumeTotal(Data d1, Data d2) const;

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
	void getInfo();

};

/**
 * @brief Classe utilizada para lancar uma excecao quando nao e encontrado um projeto com o id fornecido
 * @param id - id do projeto que nao foi possível encontrar
 */
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
 * @brief Lê os commits de todos os utilizadores a partir de um ficheiro
 * @param users - autores dos commits
 * @return vetor de commits
 */
vector<Commit> readCommits(vector <Utilizador *> users,string ficheiroC);



#endif //PROJ_AEDA_PROJETO_H
