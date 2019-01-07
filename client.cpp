#include "client.h"

Client::Client(string nome, string email, unsigned numero, unsigned nif){
    _nome = nome;
    _email = email;
    _contacto = numero;
    _NIF = nif;
    _numeroProj = 0;
}

string Client::getNome() const{
    return _nome;
}

string Client::getEmail() const{
    return _email;
}

unsigned Client::getContacto() const{
    return _contacto;
}

unsigned Client::getNif() const{
    return _NIF;
}

int Client::getNProj() const{
    return _numeroProj;
}

vector<Projeto* > Client::getProjetos() const{
	return _projetos;
}

void Client::setNome(string nome){
    _nome = nome;
}

void Client::setEmail(string email){
    _email = email;
}

void Client::setContacto(unsigned numero){
    _contacto = numero;
}

void Client::setNIF(unsigned nif){
    _NIF = nif;
}

void Client::incrementaProj(){
    _numeroProj++;
}

void Client::addProj(Projeto* proj){
	_projetos.push_back(proj);
	incrementaProj();
}

void Client::removeProj (unsigned id){
	for (unsigned int i = 0; i < _projetos.size(); i++){
		if (_projetos.at(i)->getId() == id){
			_projetos.erase(_projetos.begin()+i);
			break;
		}
	}
}

bool Client::operator<(const Client& c1) const{
	if(_numeroProj == c1.getNProj()){
		return _nome < c1.getNome();
	}
	return _numeroProj < c1.getNProj();
}

bool Client::operator==(const Client& c1) const{
	return _NIF == c1.getNif();
}

void Client::printProjects()
{
	if(_projetos.size() == 0)
	{
		cout << "\n*Cliente sem projetos*\n\n";
		return;
	}
	for(unsigned int i = 0; i < _projetos.size(); i++)
	{
		cout<< i << "# - "<< _projetos.at(i)->getNome() << "		"
				<<"Tipo: " << _projetos.at(i)->getTipo()
				<<"	Volume: "<< _projetos.at(i)->getVolumeTotal(Data(0,0,0), Data(0,0,0)) << endl;
	}
}
