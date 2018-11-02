#include <iostream>
#include "projeto.h"
#include "utilizador.h"
using namespace std;

unsigned int Commit::_lastC=0;

void Projeto::sortRanking(vector<Utilizador> &vec){
	
	for (unsigned int j = vec.size() - 1; j > 0; j--)
	{
		bool troca = false;
		for (unsigned int i = 0; i < j; i++)
			if (getVolume(vec[i + 1].getNome()) >getVolume(vec[i].getNome()))
			{
				std::swap(vec[i], vec[i + 1]);
				troca = true;
			}
			else if (getVolume(vec[i + 1].getNome()) ==getVolume(vec[i].getNome()))
			{
				if (getFreq(vec[i + 1].getNome()) > getFreq(vec[i].getNome()))
				{
					std::swap(vec[i], vec[i + 1]);
					troca = true;
				}
			}
		if (!troca) break;
	}


}



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
	sortCommits(_commits);
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

int Projeto::getVolume(string nome_user) const
{
	int volume = 0;
	for (unsigned int i = 0; i < _commits.size(); i++)
	{
		if (_commits.at(i).getUser()->getNome() == nome_user) {
			volume += _commits.at(i).getVolume();
		}
	}
	return volume;
}

float Projeto::getFreq(string user) const
{
	 float n = 0;
	for (unsigned int i = 0; i < _commits.size(); i++)
	{
		if (_commits.at(i).getUser()->getNome() == user)
		{
			n++;
		}
	}
	return n/_commits.size();
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

Avancado::Avancado(string nome): Projeto(nome){}

bool Avancado::addBranch(string nome)
{
	Branch newbranch(nome);
	for (unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i).getNome() == nome)
			return false;
	}
	_branches.push_back(newbranch);
	return true;
}

bool Avancado::removeBranch(string nome)
{
	for(unsigned int i =0; i < _branches.size(); i++)
	{
		if (_branches.at(i).getNome() == nome)
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
		if (_branches.at(i).getNome() == nome)
		{
			v = _branches.at(i).getCommits();
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
		if (_branches.at(i).getNome() == nome1)
		{
			n1 = i;
		}
		if (_branches.at(i).getNome() == nome2)
		{
			n2 = i;
		}
	}
	_branches.at(n1).addCommitVec(_branches.at(n2).getCommits());
	_branches.erase(_branches.begin() + n2);

}



