#include <iostream>
#include "empresa.h"
#include <stdlib.h>
using namespace std;

string opcao;


void Login(Empresa &emp);
Projeto* editProj(int id, Empresa & emp);
void rotinaGestor(Utilizador* logger, Empresa &empresa);
void rotinaVerRanking(Empresa & emp);
void removeAUsers(Projeto * proj);
void rotinaJunior(Utilizador* logger, Empresa & empresa);

int main() {
	int op=1;
	Empresa empresa;
	while(op != 0)
	{
		cout << "Bases de codigo \n\n";
		cout << "Selecione o que pretende fazer: \n" << "1 - Ver rankings\n"
				// rankings de atividade mensal de cada elemento do projeto .....
				<< "2 - Ver salarios de todos o pessoal\n"
				//lista com salarios e valor total
				<< "3 - Adicionar utilizador\n"
				<< "4 - Entrar com utilizador\n"; //----|
		//ver informcoes (ranking, tipo de utilizador (e caracteristicas da classe utilizador), projetos, salario, reputacao.
		//entrar num projeto (pedindo codigo de acesso) para : ver informacoes (caracteristicas da classe projeto), fazer novos commits;
		//	criar, eliminar ou juntar (merge) branches (conforme tipo de utilizadors e projetos).

		cin >> opcao;
		op = stoi(opcao);
		
		switch (op) {
		case 1:
			rotinaVerRanking(empresa);
			break;
		case 2:
			empresa.imprimeSalarios();
			break;
		case 3:
			empresa.novoUtilizador();
			//empresa.readUsers();
			break;
		case 4:
			Login(empresa);

		}

	}
	return 0;
}


void Login(Empresa &emp) {
	bool existe=false;
	string nome;
	cout << "Digite nome do utilizador: ";
	cin >> nome;
	Utilizador* logger = emp.existeUser(nome, existe);

	if (existe)
	{
		
		if (logger->getCargo() == "Gestor")
		{
			rotinaGestor(logger,emp);
		}
			//if (logger->getCargo() == "Serior")
		if (logger->getCargo() == "Junior")
		{
			rotinaJunior(logger, emp);
		}
	}

}
void rotinaGestor(Utilizador* logger, Empresa & empresa) {
	int opcao,novoProjeto;
	string nome;
	Projeto * proj;
	Utilizador * user;
	do
	{
		cout <<endl<< "1-Criar novo projeto\n"
			<< "2- Adicionar/Remover utilizadores a Projeto.\n"
			<< "3- Remover projeto\n"
			<< "4 -Ver projetos\n"
			<< "0- Voltar atrás\n";
		cin >> opcao;
		switch (opcao)
		{
		case 1: 
			novoProjeto = empresa.novoProjeto();
			logger->addProjeto(novoProjeto);
			break;

		case 2:

			if (logger->getProjetos().size() == 0)
			{
				system("CLS");

				cout <<endl<< "Este gestor nao possui projetos.\n";
				break;
			}
			else {
				cout << "Projetos: \n";
				logger->imprimeProjetos();
				cout << "Selecione um projeto: ";
				cin >> opcao;
				proj = editProj(opcao,empresa);
				proj->imprimeUsers();
				cout << "Utilizadores da empresa: " << endl;
				empresa.imprimeUser();
				cout << "Selecione o Utilizador: ";
				cin >> nome;
				user = empresa.existeUser(nome);
				proj->addUtilizador(user);
				user->addProjeto(proj->getId());
			}
			break;
		case 3:
			cout << "Projetos: \n";
			logger->imprimeProjetos();
			cout << "Selecione um projeto: ";
			cin >> opcao;

			if (opcao == 0)
				break;

			proj = editProj(opcao, empresa);
			cout << "Projeto " << proj->getNome() << " de ID " << proj->getId() << "removido\n";
			removeAUsers(proj);
			empresa.removeProjeto(proj);
			break;
		case 4:
			logger->imprimeProjetos();
			break;

		default:
			break;
		}
	} while (opcao != 0);

}


void rotinaJunior(Utilizador* logger, Empresa & empresa) {
	int opcao,volume,dia,mes,ano;
	Projeto* proj;
	Commit* newCommit;
	vector<Utilizador*>* v;
	cout << endl << "1-Ver projetos\n"
		<< "2- Fazer commit\n"
		<< "3- Ver historico de commits\n";

	if(logger->getReputacao() >=5000)
		cout << "4- Editar Branches\n";

	cout<< "0- Voltar atrás\n";
	
	cin >> opcao;
	switch (opcao)
	{
	case 0: Login(empresa);
			break;
	case 1:
		logger->imprimeProjetos();
		break;
	case 2:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			rotinaJunior(logger, empresa);

		proj = editProj(opcao, empresa);
		cout << "Volume do commit: ";
		cin >> volume;
		cout << "Data do commit(dd/mm/aa): ";
		cin >> dia >> mes>> ano;
		newCommit= new Commit(logger, volume, dia, mes, ano);
		proj->addCommit(*newCommit);
		empresa.converteJunior(logger);

		break;
	
	case 3:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = editProj(opcao, empresa);
		proj->imprimeHistorico();
		break;

	default:
		break;
	}
}


void rotinaSenior(Utilizador* logger, Empresa& empresa) {
	int opcao, volume, dia, mes, ano;
	Projeto * proj;
	Commit * newCommit;
	Branch* newBranch;
	string nomeBranch;

	cout << "1- Ver Projetos;\n"
		<< "2- Fazer commit num projeto;\n"
		<< "3- Ver historico de commits;\n"
		<< "4- Criar um branch num projeto;\n"
		<< "5- Apagar branch de um projeto;\n"
		<< "6- Fazer merge de dois branches;\n"
		<< "0- Voltar atras;\n";

	cin >> opcao;
	switch (opcao)
	{
	case 0: Login(empresa);
		break;
	case 1:
		logger->imprimeProjetos();
		break;
	case 2:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			rotinaJunior(logger, empresa);

		proj = editProj(opcao, empresa);
		cout << "Volume do commit: ";
		cin >> volume;
		cout << "Data do commit(dd/mm/aa): ";
		cin >> dia >> mes >> ano;
		newCommit = new Commit(logger, volume, dia, mes, ano);
		proj->addCommit(*newCommit);
		empresa.converteJunior(logger);

		break;

	case 3:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = editProj(opcao, empresa);
		proj->imprimeHistorico();
		break;

	case 4:
		//cria branch
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = editProj(opcao, empresa);
		cout << "Digite o nome do branch: ";
		cin >> nomeBranch;
		if (proj->getTipo() == "Basico")
		{
			proj = empresa.converteBasico(proj);
		}
		proj->addBranch(nomeBranch);
		
		break;
	case 5:
		//apaga branch
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = editProj(opcao, empresa);
		proj->imprimeBranches();
		cout << "Digite o nome do branch: ";
		cin >> nomeBranch;
		if (!proj->removeBranch(nomeBranch))
			cout << "Nao existe um branch com o nome " << nomeBranch << endl;
		break;

	case 6:
		// Merge
		string nome1, nome2;
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = editProj(opcao, empresa);
		proj->imprimeBranches();
		cout << "Digite o nome do primeiro branch (MASTER para fazer merge com o branch principal) : ";
		cin >> nome1;
		cout << "Digite o nome do segundo branch (MASTER para fazer merge com o branch principal) : ";
		cin >> nome2;
		if (nome1 == "MASTER" && nome2 != "MASTER")
			proj->merge(nome2);
		if (nome1 != "MASTER" && nome2 == "MASTER")
			proj->merge(nome1);
		if (nome1 != "MASTER" && nome2 != "MASTER")
			proj->merge(nome1, nome2);
		break;


	}
}



Projeto* editProj(int id, Empresa & emp) {
	for (unsigned int i = 0; i < emp.getProjetos().size(); i++)
	{
		if (emp.getProjetos().at(i)->getId() == id)
			return emp.getProjetos().at(i);
	}
}

void removeAUsers(Projeto * proj) {
	for (unsigned int i = 0; i < proj->getUsers().size(); i++)
		proj->getUsers().at(i)->removeProjeto(proj->getId());
}




void verRanking(Empresa & emp) {
	sortRanking(emp.getUsers(), &emp);
	emp.imprimeCoders();
}

void verRanking(Empresa & emp,Data d1, Data d2) {
	sortRanking(emp.getUsers(), &emp,d1,d2);
	emp.imprimeCoders();
}

void verRanking(Projeto & proj) {
	sortRanking(proj.getUserRef(), &proj);
	proj.imprimeCoders();

}

void verRanking(Projeto & proj, Data d1, Data d2) {
	sortRanking(proj.getUserRef(), &proj, d1, d2);
	proj.imprimeCoders();
}


void rotinaVerRanking(Empresa & emp) {
	int opcao,dia,mes,ano;
	Projeto* proj;
	cout << endl << "Ver ranking de utilizadores:\n"
		<< "1- Da empresa;\n"
		<< "2- De um projeto;\n"
		<< "0-Voltar atras;\n" << endl;
	cin >> opcao;
	
		switch (opcao)
		{
		case 1:
			cout << "1- Ranking geral;\n"
				<< "2- Ranking entre duas datas\n"
				<< "0-Voltar atras\n";

			cin >> opcao;
			if (opcao == 0)
				rotinaVerRanking(emp);
			if (opcao == 1)
				verRanking(emp);
			else
			{
				cout << "Defina a primeira data(dd/mm/aa):\n";
				cin >> dia >> mes >> ano;
				Data d1(dia, mes, ano);
				cout << "Defina a segunda data(dd/mm/aa):\n";
				cin >> dia >> mes >> ano;
				Data d2(dia, mes, ano);
				if (d1 < d2)
					verRanking(emp, d1, d2);
				else
					verRanking(emp, d2, d1);
			}
			
			break;
		case 2:
			emp.imprimeProjetos();
			cout << "Selecione o projeto por ID:"
				<<"0- Voltar atras\n";
			cin >> opcao;

			if (opcao == 0)
				rotinaVerRanking(emp);

			proj = editProj(opcao, emp);
			cout << "1- Ranking geral;\n"
				<< "2- Ranking entre duas datas\n"
				<<"0-Recomecar\n";
			cin >> opcao;
			if (opcao == 0)
				rotinaVerRanking(emp);
			if (opcao == 1)
				verRanking(*proj);
			else
			{
				cout << "Defina a primeira data(dd/mm/aa):\n";
				cin >> dia >> mes >> ano;
				Data d1(dia, mes, ano);
				cout << "Defina a segunda data(dd/mm/aa):\n";
				cin >> dia >> mes >> ano;
				Data d2(dia, mes, ano);
				if (d1 < d2)
					verRanking(*proj, d1, d2);
				else
					verRanking(*proj, d2, d1);
			}

		}

}