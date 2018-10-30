#ifndef projeto
#define projeto
#include <vector>
#include <string>
#include "utilizador.h"
using namespace std;



class Commit {
	Utilizador _userC;
	int _volume;
	Data _dataC;
public:

	Commit(Utilizador user, int volume, int d, int m, int a);
};

class Projeto {
	string _nome;
	vector<Commit> _commits;
	vector<Utilizador> _ranking;
public:
	Projeto(string nome);



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


#endif
