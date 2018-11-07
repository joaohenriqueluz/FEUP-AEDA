#include <iostream>
#include "projeto.h"
#include "utilizador.h"
using namespace std;

unsigned int Commit::_lastC=0;


void sortCommits(vector<Commit> &commits);
Commit::Commit(Utilizador* user, int volume, int d, int m, int a): _userC(user){
	_idC=++_lastC;
    _volume = volume;
    _dataC.setData(d,m,a);
}

Utilizador* Commit::getUser () const{
	return _userC;
}

int Commit::getVolume () const{
	return _volume;
}

Data Commit::getData() const{
	return _dataC;
}


unsigned int Commit::getID() const{
	return _idC;
}
//---------------------------------------------------------------------

void Branch::adicionaCommit(Commit cm){ 
	_commits.push_back(cm);
	sortCommits(_commits);
}
void Branch::addCommitVec(vector<Commit> vec)
{
	_commits.insert(_commits.begin(), vec.begin(), vec.end());
	sortCommits(_commits);
}
//---------------------------------------------------------------------
unsigned int Projeto::lastId = 0;

Projeto::Projeto(string nome,string tipo){
    _nome = nome;
	_tipo = tipo;
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
	sortCommits(_commits);
	if(cm.getUser()->getCargo()== "Junior")
	{
		cm.getUser()->setReputacao(cm.getUser()->getReputacao() + cm.getVolume() / 10);
	}
	
}

void Projeto::addUtilizador (Utilizador * user){
	_ranking.push_back(user);
	//ordenar
}

void Projeto::imprimeUsers()
{
	cout << "Utilizadores do projeto com ID " << getId() << endl;
for (unsigned int i = 0; i < _ranking.size(); i++)
	{
		cout <<i+1<<"# "<< _ranking.at(i)->getNome()<<"     Cargo: "<<_ranking.at(i)->getCargo()<< endl;
	}
}

void Projeto::imprimeCoders()
{
	for (unsigned int i = 0; i < _ranking.size(); i++)
	{
		if (_ranking.at(i)->getCargo() == "Gestor")
			continue;
		cout << i + 1 << "# " << _ranking.at(i)->getNome() << _ranking.at(i)->getCargo() << endl;
	}
}

string Projeto::getChaveAcesso(){
	return _chaveAcesso;
}

void Projeto::setChaveAcesso(string chave){
	_chaveAcesso = chave;
}

int Projeto::getVolume(string nome_user, Data d1, Data d2) const {
	int volume = 0;
	for (unsigned int i = 0; i < _commits.size(); i++) {
		if (_commits.at(i).getUser()->getNome() == nome_user) {
			if (d1 == Data(0, 0, 0) && d2 == Data(0, 0, 0)) { //n�o quer de um periodo especifico
				volume += _commits.at(i).getVolume();
			}
			else if (_commits.at(i).getData() >= d1 && _commits.at(i).getData() <= d2) {
				volume += _commits.at(i).getVolume();
			}
		}
	}
	return volume;
}

void Projeto::imprimeHistorico()
{
	for (unsigned int i = 0;i < _commits.size(); i++)
	{
		cout << "Commit: " << _commits.at(i).getID()
			<< " Autor: " << _commits.at(i).getUser()->getNome()
			<< " Data: " << _commits.at(i).getData().getDia()
						<< "/" << _commits.at(i).getData().getMes()
						<< "/" << _commits.at(i).getData().getAno()
			<<" Volume: "<< _commits.at(i).getVolume()<<endl;
	}
	   	 
}

float Projeto::getFreq(string user, Data d1, Data d2) const {
	float userCommit = 0, totalCommits = 0;
	for (unsigned int i = 0; i < _commits.size(); i++) {
		if (d1 == Data(0, 0, 0) && d2 == Data(0, 0, 0)) {
			totalCommits = _commits.size();
			if (_commits.at(i).getUser()->getNome() == user) {
				userCommit++;
			}
		}
		else if (_commits.at(i).getData() >= d1 && _commits.at(i).getData() <= d2) {
			totalCommits++;
			if (_commits.at(i).getUser()->getNome() == user) {
				userCommit++;
			}
		}
	}
	return userCommit / totalCommits;
}


void sortCommits(vector<Commit> &commits)//por data
{
	for (unsigned int j = commits.size() - 1; j > 0; j--)
	{
		bool troca = false;
		for (unsigned int i = 0; i < j; i++)
			if (commits[i + 1].getData() < commits[i].getData())
			{
				std::swap(commits[i], commits[i + 1]);
				troca = true;
			}
		if (!troca) break;
	}

}


//---------------------------------------------------------------------

Avancado::Avancado(string nome): Projeto(nome,"Avancado"){}

bool Avancado::addBranch(string nome)
{
	Branch* newbranch= new Branch(nome);
	for (unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome)
			return false;
	}
	_branches.push_back(newbranch);
	return true;
}

bool Avancado::removeBranch(string nome)
{
	for(unsigned int i =0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome)
		{
			_branches.erase(_branches.begin() + i);
			return true;
		}
	}
	return false;
}

void Avancado::merge(string nome)
{
	vector<Commit> v;
	for(unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome)
		{
			v = _branches.at(i)->getCommits();
			_commits.insert(_commits.begin(),v.begin(), v.end());
			sortCommits(_commits);
			_branches.erase(_branches.begin() + i);
		}
	}
}

void Avancado::merge(string nome1, string nome2)
{
	int n1=0, n2=0;
	for (unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome1)
		{
			n1 = i;
		}
		if (_branches.at(i)->getNome() == nome2)
		{
			n2 = i;
		}
	}
	_branches.at(n1)->addCommitVec(_branches.at(n2)->getCommits());
	_branches.erase(_branches.begin() + n2);

}


void Avancado::imprimeBranches() {
	for(unsigned int i = 0; i < _branches.size(); i++)
	{
		cout<<i+1<<"#  " << _branches.at(i)->getNome()<< endl;
	}
}

