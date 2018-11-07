#include <iostream>
#include "empresa.h"
#include <stdlib.h>
using namespace std;

string opcao;

void rotinaEmpresa(Empresa &empresa);
void Login(Empresa &emp);
void rotinaGestor(Utilizador* logger, Empresa &empresa);
void rotinaVerRanking(Empresa & emp);
void rotinaJunior(Utilizador* logger, Empresa & empresa);
void rotinaSenior(Utilizador* logger, Empresa& empresa);

int main() {
	int opcao;
	Empresa empresa;
	cout << "#####################";
	cout << "#                   #";
	cout << "#  Bases de codigo  #";
	cout << "#                   #";
	cout << "#####################\n\n";
	cout << "Selecione a opcao: \n";
	cout << "1 - Nova Empresa(empresa sem projetos nem utilizadores)\n"
			<< "2 - Retomar uma empresa\n";

	cin >> opcao;
	if (opcao == 1){
		rotinaEmpresa(empresa);
	}
	else if (opcao == 2) {
		empresa.readUsers();
		rotinaEmpresa(empresa);
	}

	return 0;
}
void rotinaEmpresa(Empresa & empresa) {
	int op = 1;
	while (op != 0) {

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
			empresa.readUsers();
			break;
		case 4:
			Login(empresa);

		}

	}
	return;
}

void Login(Empresa &emp) {

	string nome;
	cout << "Digite nome do utilizador: ";
	cin >> nome;
	Utilizador* logger;
	try {
		logger = emp.existeUser(nome);
	} catch (NoSuchUser &e) {
		cout << "Não existe um utilizador com nome " << e.getName() << endl
				<< endl;
		return;
	}

	if (logger->getCargo() == "Gestor") {
		rotinaGestor(logger, emp);
	}
	if (logger->getCargo() == "Senior") {
		rotinaSenior(logger, emp);
	}
	if (logger->getCargo() == "Junior") {
		rotinaJunior(logger, emp);
	}

}

void rotinaGestor(Utilizador* logger, Empresa & empresa) {
	int opcao, novoProjeto;
	string nome;
	Projeto * proj;
	Utilizador * user;
	do {
		cout << endl << "1-Criar novo projeto\n"
				<< "2- Adicionar utilizadores a Projeto.\n"
				<< "3- Remover utilizadores a projeto\n"
				<< "4- Remover projeto\n" << "5 -Ver projetos\n"
				<< "0- Voltar atrás\n";
		cin >> opcao;
		switch (opcao) {
		case 1:
			novoProjeto = empresa.novoProjeto();
			logger->addProjeto(novoProjeto);
			break;

			AD_UTI: case 2:

			if (logger->getProjetos().size() == 0) {
				system("CLS");

				cout << endl << "Este gestor nao possui projetos.\n";
				break;
			} else {
				cout << "Projetos: \n";
				logger->imprimeProjetos();
				cout << "Selecione um projeto: ";
				cin >> opcao;
				proj = empresa.editProj(opcao);
				proj->imprimeUsers();
				cout << "Utilizadores da empresa: " << endl;
				empresa.imprimeUser();
				cout << "Selecione o Utilizador: ";
				cin >> nome;
				if (proj->existeUser(nome)) {
					cout << nome << " ja pertence a este projeto.\n";
					goto AD_UTI;
				}
				try{
					user = empresa.existeUser(nome);
				}catch(NoSuchUser &u){
					cout << u.getName() << " nao existe.\n";
					goto AD_UTI;
				}

				proj->addUtilizador(user);
				user->addProjeto(proj->getId());
			}
			break;
			REM_UTI: case 3:
			cout << "Projetos: \n";
			logger->imprimeProjetos();
			cout << "Selecione um projeto: ";
			cin >> opcao;
			proj = empresa.editProj(opcao);
			proj->imprimeUsers();
			cout << "Utilizadores da empresa: " << endl;
			empresa.imprimeUser();
			cout << "Selecione o Utilizador: ";
			cin >> nome;
			if (!(proj->existeUser(nome))) {
				cout << nome << " nao pertence a este projeto.\n";
				goto REM_UTI;
			}
			try{
			user = empresa.existeUser(nome);
			}catch(NoSuchUser &u){
				cout << u.getName() << " nao existe.\n";
				goto REM_UTI;
			}
			user->removeProjeto(proj->getId());
			proj->removeUser(nome);
			break;
		case 4:
			cout << "Projetos: \n";
			logger->imprimeProjetos();
			cout << "Selecione um projeto: ";
			cin >> opcao;

			if (opcao == 0)
				break;

			proj = empresa.editProj(opcao);
			cout << "Projeto " << proj->getNome() << " de ID " << proj->getId()
					<< "removido\n";
			proj->removeAUsers();
			empresa.removeProjeto(proj);
			break;
		case 5:
			logger->imprimeProjetos();
			break;

		default:
			break;
		}
	} while (opcao != 0);

}

void rotinaJunior(Utilizador* logger, Empresa & empresa) {
	int opcao, volume, dia, mes, ano;
	Projeto* proj;
	Commit* newCommit;
//	vector<Utilizador*>* v;
	cout << endl << "1-Ver projetos\n" << "2- Fazer commit\n"
			<< "3- Ver historico de commits\n";

	if (logger->getReputacao() >= 5000)
		cout << "4- Editar Branches\n";

	cout << "0- Voltar atrás\n";

	cin >> opcao;
	switch (opcao) {
	case 0:
		Login(empresa);
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

		proj = empresa.editProj(opcao);
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

		proj = empresa.editProj(opcao);
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
	//Branch* newBranch;
	string nomeBranch;

	cout << "1- Ver Projetos;\n" << "2- Fazer commit num projeto;\n"
			<< "3- Ver historico de commits;\n"
			<< "4- Criar um branch num projeto;\n"
			<< "5- Apagar branch de um projeto;\n"
			<< "6- Fazer merge de dois branches;\n" << "0- Voltar atras;\n";

	cin >> opcao;
	switch (opcao) {
	case 0:
		Login(empresa);
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

		proj = empresa.editProj(opcao);
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

		proj = empresa.editProj(opcao);
		proj->imprimeHistorico();
		break;

		CRIA_BRANCH: case 4:
		//cria branch
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		if (proj->getTipo() == "Basico") {
			cout << "Este é do tipo Basico (sem branches)\n"
					" Selecione outro Projeto\n";
			goto CRIA_BRANCH;
		}
		cout << "Digite o nome do branch: ";
		cin >> nomeBranch;
		try{
		proj->addBranch(nomeBranch);
		}catch (BranchRepetido & r){
			cout << "Ja existe um branch com o nome " << r.getName() << endl;
			goto CRIA_BRANCH;
		}

		break;
	case 5:
		//apaga branch
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		proj->imprimeBranches();
		cout << "Digite o nome do branch: ";
		cin >> nomeBranch;
		try{
			proj->removeBranch(nomeBranch);
		}catch(NoSuchBranch &b){
			cout << "Nao existe um branch com o nome " << b.getName() << endl;
		}
		break;

	case 6:
		// Merge
		string nome1, nome2;
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		proj->imprimeBranches();
		cout
				<< "Digite o nome do primeiro branch (MASTER para fazer merge com o branch principal) : ";
		cin >> nome1;
		cout
				<< "Digite o nome do segundo branch (MASTER para fazer merge com o branch principal) : ";
		cin >> nome2;
		try{
		if (nome1 == "MASTER" && nome2 != "MASTER")
			proj->merge(nome2);
		if (nome1 != "MASTER" && nome2 == "MASTER")
			proj->merge(nome1);
		if (nome1 != "MASTER" && nome2 != "MASTER")
			proj->merge(nome1, nome2);
		}catch(NoSuchBranch &b){
			cout << "Nao existe um branch com o nome " << b.getName() << ". Tente outra vez.\n\n";
		}
		break;

	}
}

void verRanking(Empresa & emp) {
	sortRanking(emp.getUsers(), &emp);
	emp.imprimeCoders();
}

void verRanking(Empresa & emp, Data d1, Data d2) {
	sortRanking(emp.getUsers(), &emp, d1, d2);
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
	int opcao, dia, mes, ano;
	Projeto* proj;
	cout << endl << "Ver ranking de utilizadores:\n" << "1- Da empresa;\n"
			<< "2- De um projeto;\n" << "0-Voltar atras;\n" << endl;
	cin >> opcao;

	switch (opcao) {
	case 1:
		cout << "1- Ranking geral;\n" << "2- Ranking entre duas datas\n"
				<< "0-Voltar atras\n";

		cin >> opcao;
		if (opcao == 0)
			rotinaVerRanking(emp);
		if (opcao == 1)
			verRanking(emp);
		else {
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
		cout << "Selecione o projeto por ID:" << "0- Voltar atras\n";
		cin >> opcao;

		if (opcao == 0)
			rotinaVerRanking(emp);

		proj = emp.editProj(opcao);
		cout << "1- Ranking geral;\n" << "2- Ranking entre duas datas\n"
				<< "0-Recomecar\n";
		cin >> opcao;
		if (opcao == 0)
			rotinaVerRanking(emp);
		if (opcao == 1)
			verRanking(*proj);
		else {
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
