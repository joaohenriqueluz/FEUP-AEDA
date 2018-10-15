#ifndef projeto
#define projeto
#include <vector>
#include <string>
#include "utilizador.h"

class commit {
	utilizador userC;
	int volume;
	dataD dataC;

};

class projeto {
	vector<commit *> commits;
	vector<utilizador> ranking;

};

class basico : public projeto {
	
};

class avancado : public projeto {
	//branches (cria/elimina/merge-senior)
};


#endif