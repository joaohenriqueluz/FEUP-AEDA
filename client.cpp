#include "client.h"

Client::Client(string nome, string email, unsigned numero, unsigned nif){
    _nome = nome;
    _email = email;
    _contacto = numero;
    _NIF = nif;
    _numeroProj = 0;
}

string Client::getNome(){
    return _nome;
}

string Client::getEmail(){
    return _email;
}

unsigned Client::getContacto(){
    return _contacto;
}

unsigned Client::getNif(){
    return _NIF;
}

unsigned Client::getNProj(){
    return _numeroProj;
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
}

bool Client::operator<(const Client& c1) const{
	if(_numeroProj == c1._numeroProj){
		return _nome < c1._nome;
	}
	return _numeroProj < c1._numeroProj;
}

bool Client::operator==(const Client& c1) const{
	return _email == c1._email;
}

