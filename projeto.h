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
	vector<Branch*> _branches;
	string _tipo; //Basico ou avançado
public:
    Projeto(string nome,string tipo);
    virtual ~Projeto(){};
    string getNome ();
	void setTipo(string tipo) { _tipo = tipo; }
	string getTipo() const { return _tipo; }
    unsigned int getId();
	vector<Commit> getCommits() const { return _commits; }
    void addCommit(Commit cm);
    void addUtilizador (Utilizador * user);
    /**
        * @brief Verifica se o Utilizador de nome "nome" ja existe no projeto;
        * @param nome
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
    string getChaveAcesso();
    void setChaveAcesso(string chave);
	int getVolume(string nome_user, Data d1, Data d2) const;
	void imprimeHistorico();
	float getFreq(string user, Data d1, Data d2) const;
	vector<Utilizador *> getUsers() { return _ranking; };
	vector<Utilizador*>& getUserRef() { return _ranking;}
	virtual void addBranch(string nome) {}
	virtual void removeBranch(string nome) {}
	virtual void merge(string nome) {}
	virtual void merge(string nome1, string nome2){}
	virtual void imprimeBranches(){}
};



class Avancado : public Projeto {
	
    //branches (cria/elimina/merge-senior)
public:
    Avancado(string nome);
	void addBranch(string nome);
	void removeBranch(string nome);
	void merge(string nome);
	void merge(string nome1, string nome2);
	void imprimeBranches();
	//Branch* existeBranch(string nome); /// VER EXCECAO
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

#endif //PROJ_AEDA_PROJETO_H
