#include <iostream>
#include "projeto.h"

using namespace std;

Commit::Commit(Utilizador user, int volume, int d, int m, int a){
	_userC = user;
	_volume = volume;
	_dataC(d,m,a);
}


//---------------------------------------------------------------------
Projeto::Projeto(string nome){
	_nome = nome;
}

//---------------------------------------------------------------------
Basico::Basico(string nome): Projeto(nome){}

//---------------------------------------------------------------------
Avancado::Avancado(string nome): Projeto(nome){}
