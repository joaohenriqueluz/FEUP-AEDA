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


bool Data::operator <(const Data & other)const
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



bool Data::operator <=(const Data & other)const {
	if (getAno() < other.getAno())
		return true;
	if (getAno() == other.getAno() && getMes() < other.getMes())
		return true;
	if (getAno() == other.getAno() && getMes() == other.getMes() && getDia() <= other.getDia())
		return true;
	return false;
}

bool Data::operator >=(const Data & other)const {
	if (getAno() > other.getAno())
		return true;
	if (getAno() == other.getAno() && getMes() > other.getMes())
		return true;
	if (getAno() == other.getAno() && getMes() == other.getMes() && getDia() >= other.getDia())
		return true;
	return false;
}

bool Data::operator ==(const Data & other)const {
	return (getAno() == other.getAno() && getMes() == other.getMes() && getDia() == other.getDia());
}

//---------------------------------------------------------------------
Utilizador::Utilizador(string nome, int d, int m, int a,string email,float salario, int NIF, string cargo)
{
    _nome = nome;
    dataNascimento.setData(d,m,a);
    _email = email;
    _salario=salario;
    _NIF= NIF;
	_cargo = cargo;
}

string Utilizador::getNome()const {
	return _nome;
}

void Utilizador::setNome(string nome){_nome = nome;}
Data Utilizador::getDataNascimento()const {
	return dataNascimento;
}

string Utilizador::getEmail()const {
	return _email;
}

void Utilizador::setEmail(string email){
	_email = email;
}

void Utilizador::addProjeto (int id){
	_projetos.push_back(id);
}

void Utilizador::removeProjeto (int id){
	for (unsigned int i = 0; i < _projetos.size(); i++)
	{
		if (_projetos.at(i) == id)
		{
			_projetos.erase(_projetos.begin()+i);
		}
	}
}

Data* Utilizador::getDataNascimentoRef(){
	Data* dataPtr = & dataNascimento;
	return dataPtr;
}

int Utilizador::getNIF()const {
	return _NIF;
}

void Utilizador::setNIF(int NIF) {
	_NIF = NIF;
}

void Utilizador::setData(int d, int m, int a){
	getDataNascimentoRef()->setData(d,m,a);
}
void Utilizador::imprimeProjetos(){
	if(_projetos.size()==0)
	{
		cout << getNome() << " nao tem projetos.\n";
		return;
	}
	for (unsigned int i = 0; i < _projetos.size(); i++)
	{
		cout << i + 1 << "º" << _projetos.at(i) << endl;
	}
}


void Utilizador::getInfo() {
	cout <<" Nome: "<<getNome() <<endl
		 <<" Cargo: " << getCargo() <<endl
		 <<" Salario: " << getSalario() <<endl
		 <<" NIF: "<< getNIF() <<endl
		 << " Email: "<< getEmail() <<endl
		 << " Data de nascimento "
		 << getDataNascimento().getDia() << "/"
		 << getDataNascimento().getMes() << "/"
		 << getDataNascimento().getAno()<< endl;
}
//---------------------------------------------------------------------

Coder::Coder(string nome, int d, int m, int a,string email,int NIF, string cargo): Utilizador(nome,d,m,a,email,0,NIF,cargo){}




//---------------------------------------------------------------------

Gestor::Gestor(string nome, int d, int m, int a,string email,float salario,int NIF, string cargo): Utilizador(nome,d,m,a,email,salario,NIF,cargo){

}

//---------------------------------------------------------------------

Senior::Senior(string nome, int d, int m, int a,string email,float salario, int NIF, string cargo):
	Coder(nome, d, m, a, email, NIF, cargo) {
	_salario = salario;
}



//---------------------------------------------------------------------

Junior::Junior(string nome, int d, int m, int a,string email, int reputacao, int NIF, string cargo):
        Coder(nome,d,m,a,email, NIF,cargo){
	_reputacao = reputacao;
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

int Junior::getReputacao() const{
	return _reputacao;
}



void Junior::setReputacao(int reputacao){
	_reputacao = reputacao;
}


void Junior::getInfo(){
	Utilizador::getInfo();
	cout<< " Reputacao: " << getReputacao()<< endl;
}
