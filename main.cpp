#include <iostream>
#include "empresa.h"

using namespace std;

string opcao;

/*
 void Login(Empresa &emp){
 Utilizador* logger;
 string nome;
 cout << "Digite nome do utilizador: ";
 cin >> nome;
 if (emp.existeUser(nome,logger))
 {
 }

 }*/

int main() {
	cout << "Bases de codigo \n\n";
	cout << "Selecione o que pretende fazer: \n" << "1 - Ver rankings\n"
			// rankings de atividade mensal de cada elemento do projeto .....
			<< "2 - Ver salarios de todos o pessoal\n"
			//lista com sal�rios e valor total
			<< "3 - Adicionar utilizador\n" << "4-  Adicionar projeto\n"
			<< "5 - Entrar com utilizador\n"; //----|
	//ver informa��es (ranking, tipo de utilizador (e caracteristicas da classe utilizador), projetos, sal�rio, reputa�ao.
	//entrar num projeto (pedindo codigo de acesso) para : ver informa�oes (caracteristicas da classe projeto), fazer novos commits;
	//	criar, eliminar ou juntar (merge) branches (conforme tipo de utilizadors e projetos).

	cin >> opcao;
	int op = stoi(opcao);
	Empresa empresa;
	switch (op) {
	case 1:
		break;
	case 2:
		empresa.imprimeSalarios();
		break;
	case 3:
		empresa.novoUtilizador();
		break;
	case 4:
		empresa.novoProjeto();
		break;

	}
	return 0;
}

