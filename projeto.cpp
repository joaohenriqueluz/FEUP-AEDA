#include <iostream>
#include "projeto.h"

using namespace std;

Commit::Commit(Utilizador user, int volume, int d, int m, int a): _userC(user){
    _volume = volume;
    _dataC.setData(d,m,a);
}

Utilizador Commit::getUser (){
	return _userC;
}

int Commit::getVolume (){
	return _volume;
}

Data Commit::getData(){
	return _dataC;
}
//---------------------------------------------------------------------
unsigned int Projeto::lastId = 0;

Projeto::Projeto(string nome){
    _nome = nome;
    _id = ++lastId;
}

string Projeto::getNome (){
	return _nome;
}

unsigned int Projeto::getId(){
	return _id;
}

void Projeto::addCommit(Commit cm){
	_commits.push_back(cm);
}

void Projeto::addUtilizador (Utilizador * user){
	_ranking.push_back(user);
	//ordenar
}

string Projeto::getChaveAcesso(){
	return _chaveAcesso;
}

void Projeto::setChaveAcesso(string chave){
	_chaveAcesso = chave;
}
//---------------------------------------------------------------------
Basico::Basico(string nome): Projeto(nome){}

//---------------------------------------------------------------------
Avancado::Avancado(string nome): Projeto(nome){}


