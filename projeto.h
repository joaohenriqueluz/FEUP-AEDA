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
class Projeto {
protected:
    string _nome;
    unsigned int _id;
    static unsigned int lastId;
    string _chaveAcesso;
    vector<Commit> _commits;
    vector<Utilizador *> _ranking;
public:
    Projeto(string nome);
    string getNome ();
    unsigned int getId();
    void addCommit(Commit cm);
    void addUtilizador (Utilizador * user);
	void imprimeUsers();
	void imprimeCoders();
    string getChaveAcesso();
    void setChaveAcesso(string chave);
	int getVolume(string nome_user, Data d1, Data d2) const;
	void imprimeHistorico();
	float getFreq(string user, Data d1, Data d2) const;
	vector<Utilizador *> getUsers() { return _ranking; };
	vector<Utilizador*>& getUserRef() { return _ranking;}
	
};



class Avancado : public Projeto {
	vector<Branch> _branches;
    //branches (cria/elimina/merge-senior)
public:
    Avancado(string nome);
	bool addBranch(string nome);//nao deixa adicionar um nome repetido;
	bool removeBranch(string nome);
	void merge(string nome);
	void merge(string nome1, string nome2);
	Branch existeBranch(string nome);
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
