#ifndef PROJ_AEDA_PROJETO_H
#define PROJ_AEDA_PROJETO_H

#include <vector>
#include <string>
#include "utilizador.h"

using namespace std;

class Commit {
	unsigned int _idC;
	static unsigned int _lastC;
    Utilizador* _userC;
    int _volume;
    Data _dataC;
public:
    Commit(Utilizador* user, int volume, int d, int m, int a);
    Utilizador* getUser ()const;
    int getVolume () const;
    Data getData() const;
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
    void sortRanking(); //por fazer: ordenar conforme o volume e a frequencia de commits
    //remover utilizador e commits?
    string getChaveAcesso();
    void setChaveAcesso(string chave);
	int getVolume(string nome_user)const;
	float getFreq(string user) const;
	void sortRanking(vector<Utilizador> &vec);
	vector <Commit> getCommitVec() const;
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

#endif //PROJ_AEDA_PROJETO_H
