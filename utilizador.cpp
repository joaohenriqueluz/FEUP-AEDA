#include "utilizador.h"

using namespace std;

//---------------------------------------------------------------------

Data::Data(){
    dia=0;
    mes=0;
    ano=0;
}

Data::Data(int d, int m, int a){
    dia=d;
    mes=m;
    ano=a;
}

void Data::setData(int d, int m, int a){
    dia=d;
    mes=m;
    ano=a;
}

/*
bool Data::operator <(Data & other)
{
	if (getAno() < other.getAno())
		return true;
	if (getAno() == other.getAno() && getMes() < other.getMes())
		return true;
	if (getAno() == other.getAno() && getMes() == other.getMes() &&
							getDia() < other.getDia())
		return true;
	return false;
}
*/


//---------------------------------------------------------------------
Utilizador::Utilizador(string nome, int d, int m, int a,string email,float salario, int NIF)
{
    _nome = nome;
    dataNascimento.setData(d,m,a);
    _email = email;
    _salario=salario;
    _NIF= NIF;
}

string Utilizador::getNome(){
	return _nome;
}

Data Utilizador::getDataNascimento(){
	return dataNascimento;
}

string Utilizador::getEmail(){
	return _email;
}

void Utilizador::setEmail(string email){
	_email = email;
}

void Utilizador::addProjeto (int id){
	_projetos.push_back(id);
}

bool Utilizador::removeProjeto (int id){
	for (unsigned int i = 0; i < _projetos.size(); i++){
		if (_projetos.at(i) == id){
			_projetos.erase(_projetos.begin()+i);
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------

Coder::Coder(string nome, int d, int m, int a,string email): Utilizador(nome,d,m,a,email,0){}




//---------------------------------------------------------------------

Gestor::Gestor(string nome, int d, int m, int a,string email,float salario): Utilizador(nome,d,m,a,email,salario){

}

//---------------------------------------------------------------------

Senior::Senior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF):
        Coder(nome,d,m,a,email){
    _NIF = NIF;
}

int Utilizador::getNIF(){
	return _NIF;
}

void Utilizador::setNIF(int NIF){
	_NIF = NIF;
}

void Senior::setSalario(float salario){
	_salario = salario;
}
//---------------------------------------------------------------------

Junior::Junior(string nome, int d, int m, int a,string email, float reputacao, int NIF):
        Coder(nome,d,m,a,email){
	setSalario();
}

void Junior::setSalario(){
	if (_reputacao <= 999){
		_salario = 50;
	}
	else if (_reputacao <= 1999){
		_salario = 100;
	}
	else if (_reputacao <= 2999){
		_salario = 150;
	}
	else if (_reputacao <= 3999){
			_salario = 200;
		}
	else if (_reputacao <= 4999){
			_salario = 250;
		}
	else if (_reputacao <= 5999){
			_salario = 300;
		}
	else if (_reputacao <= 6999){
			_salario = 350;
		}
	else if (_reputacao <= 7999){
			_salario = 400;
		}
	else if (_reputacao <= 8999){
			_salario = 450;
		}
	else if (_reputacao <= 9999){
			_salario = 500;
		}
}

float Junior::getReputacao(){
	return _reputacao;
}



void Junior::setReputacao(int reputacao){
	_reputacao = reputacao;
}

