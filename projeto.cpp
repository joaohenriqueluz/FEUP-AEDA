#include <iostream>
#include "projeto.h"
#include "utilizador.h"
#include<bits/stdc++.h>
using namespace std;

unsigned int Commit::_lastC=0;
Commit::Commit(Utilizador* user, int volume, int d, int m, int a): _userC(user){
	_idC=++_lastC;
    _volume = volume;
    _dataC.setData(d,m,a);
}

Utilizador* Commit::getUser (){
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


/*
void Projeto::sortCommits(){
	for(unsigned int j=_commits.size()-1; j>0; j--)
	{
		bool troca=false;
		for(unsigned int i = 0; i<j; i++)
			if(_commits[i+1].getData() < _commits[i].getData()) {
				swap(_commits[i],_commits[i+1]);
				troca = true;
			}
		if (!troca) return;
}
}
*/


//---------------------------------------------------------------------
Basico::Basico(string nome): Projeto(nome){}

//---------------------------------------------------------------------
Avancado::Avancado(string nome): Projeto(nome){}


