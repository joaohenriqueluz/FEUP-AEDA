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
    Utilizador* getUser ();
    int getVolume ();
    Data getData();
};

class Projeto {
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

};

class Basico : public Projeto {
public:
    Basico(string nome);

};

class Avancado : public Projeto {
    //branches (cria/elimina/merge-senior)
public:
    Avancado(string nome);
};

#endif //PROJ_AEDA_PROJETO_H
