#include <iostream>
#include "empresa.h"
using namespace std;


int opcao;

int main() {
	cout << "Bases de código \n\n";
	cout << "Selecione o que pretende fazer: \n"
			<< "1 - Ver rankings\n" // rankings de atividade mensal de cada elemento do projeto .....
			<< "2 - Ver salários de todos o pessoal\n" //lista com salários e valor total
			<< "3 - Adicionar utilizador\n"
			<< "4-  Adicionar projeto\n"
			<< "5 - Entrar com utilizador\n";//----|
	//ver informações (ranking, tipo de utilizador (e caracteristicas da classe utilizador), projetos, salário, reputaçao.
	//entrar num projeto (pedindo codigo de acesso) para : ver informaçoes (caracteristicas da classe projeto), fazer novos commits;
											 //	criar, eliminar ou juntar (merge) branches (conforme tipo de utilizadors e projetos).

	Empresa empresa;
	switch(opcao)
	{
	case 1:
		break;
	case 2:
		empresa.imprimeSalarios();
		break;
	case 3:
		empresa.novoUtilizador();

	}
	}


