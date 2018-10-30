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

//---------------------------------------------------------------------
Utilizador::Utilizador(string nome, int d, int m, int a,string email)
{
    _nome = nome;
    dataNascimento.setData(d,m,a);
    _email = email;
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

Coder::Coder(string nome, int d, int m, int a,string email, float salario, float reputacao): Utilizador(nome,d,m,a,email){
    _reputacao= reputacao;
    _salario = salario;

}

float Coder::getReputacao(){
	return _reputacao;
}

float Coder::getSalario(){
	return _salario;
}

void Coder::setReputacao(float reputacao){
	_reputacao = reputacao;
}
//---------------------------------------------------------------------

Gestor::Gestor(string nome, int d, int m, int a,string email): Utilizador(nome,d,m,a,email){}

//---------------------------------------------------------------------

Senior::Senior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF):
        Coder(nome,d,m,a,email,salario,reputacao){
    _NIF = NIF;
}

int Senior::getNIF(){
	return _NIF;
}

void Senior::setNIF(int NIF){
	_NIF = NIF;
}

void Senior::setSalario(float salario){
	_salario = salario;
}
//---------------------------------------------------------------------

Junior::Junior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF):
        Coder(nome,d,m,a,email,salario,reputacao){}

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


