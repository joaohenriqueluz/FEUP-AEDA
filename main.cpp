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
void addCommit(Utilizador* logger, Empresa & empresa);
void editarProjetos(Empresa & empresa, int ID, int opcao);
void editarUtilizador(Empresa & emp,Utilizador* logger, int opcao);


int main() {

	int opcao;
	Empresa empresa;
	cout << "#####################\n";
	cout << "#                   #\n";
	cout << "#  Bases de codigo  #\n";
	cout << "#                   #\n";
	cout << "#####################\n\n";
INICIO:
	cout << "Selecione a opcao: \n";
	cout << "1 - Nova Empresa(empresa sem projetos nem utilizadores)\n"
		<< "2 - Retomar uma empresa\n"
		<< "0 - Sair\n";

	cin >> opcao;
	if (opcao == 1){
		rotinaEmpresa(empresa);
	}
	else if (opcao == 2) {
		empresa.readUsers();
		empresa.readProjetos();
		rotinaEmpresa(empresa);
	}
	else
		if(((opcao != 0) && (opcao!= 1) && (opcao!= 2)) || (cin.fail()))
		{
			cin.clear();
			cin.ignore(100,'\n');
			cout << "Opçao inválida\n";
			goto INICIO;
		}
	exit(0);

	return 0;
}

void rotinaEmpresa(Empresa & empresa) {
	int op = 1;
	while (op != 0) {

		cout << "Selecione o que pretende fazer: \n"
				<< "1 - Ver rankings\n"
				// rankings de atividade mensal de cada elemento do projeto .....
				<< "2 - Ver salarios de todos o pessoal\n"
				// lista com salarios e valor total
				<< "3 - Adicionar utilizador\n"
				<< "4 - Remover utilizador\n"
				<< "5 - Entrar com utilizador\n"
				<< "6 - Guardar progresso e sair\n"
				<< "0 - Voltar atras\n"; //----|
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
			break;
		case 4:
			cout << "Nome do utilizador a remover: ";
			cin >> opcao;
			empresa.removeUtilizador(opcao);
			break;
		case 5:
			Login(empresa);
			break;
		case 6:
			empresa.writeUsers();
			empresa.writeCommits();
			empresa.writeProjetos();
			exit(0);
			break;

		default:
			break;
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
		if (dynamic_cast <Junior*>(logger)->getReputacao() < 5000)
			rotinaJunior(logger, emp);
		else
			rotinaSenior(logger, emp);
	}

}

void rotinaGestor(Utilizador* logger, Empresa & empresa) {
	int opcao, novoProjeto;
	string nome,chave;
	Projeto * proj;
	Utilizador * user;
	do {
		cout << endl << "1 - Criar novo projeto\n"
				<< "2 - Adicionar utilizadores a Projeto\n"
				<< "3 - Remover utilizadores a projeto\n"
				<< "4 - Remover projeto\n"
				<< "5 - Ver projetos\n"
				<< "6 - Ver informacoes de um projeto\n"
				<< "7 - Editar nome/chave de acesso de um projeto\n"
				<< "8 - Ver informacoes do utilizador\n"
				<< "9 - Editar informacoes do utilizador\n"
				<< "0 - Voltar atrás\n";
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
				cout << "Selecione um projeto: \n";
				cin >> opcao;
				proj = empresa.editProj(opcao);
				cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
				cin>>chave;
				if(chave != proj->getChaveAcesso())
				{
					cout<<"#Chave de acesso errada, volte tentar.\n";
					goto AD_UTI;
				}
				proj->imprimeUsers();
				cout << "Utilizadores da empresa: \n" << endl;
				empresa.imprimeUser();
				cout << "Selecione o Utilizador: \n";
				cin >> nome;

				if (proj->existeUser(nome)) {
					cout << nome << " ja pertence a este projeto.\n";
					goto AD_UTI;
				}
				try{
					user = empresa.existeUser(nome);
					if(user->getCargo()== "Gestor")
					{
						cout << "Não pode adicionar outro gestor.\n";
						goto AD_UTI;
					}
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
			cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
			cin>>chave;
			if(chave != proj->getChaveAcesso())
			{
				cout<<"#Chave de acesso errada, volte tentar.\n";
				goto REM_UTI;
			}
			proj->imprimeUsers();
			cout << "Utilizadores da empresa: " << endl;
			empresa.imprimeUser();
			cout << "Selecione o Utilizador: ";
			cin >> nome;
			if (!(proj->existeUser(nome))) {
				cout << nome << " nao pertence a este projeto.\n";
				goto REM_UTI;
			}
			if(nome== logger->getNome())
			{
				cout<< "Não pode eliminar o gestor do Projeto\n";
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
REM_PROJ:
		case 4:
			cout << "Projetos: \n";
			logger->imprimeProjetos();
			cout << "Selecione um projeto (ID): ";
			cin >> opcao;

			if (opcao == 0)
				break;

			proj = empresa.editProj(opcao);
			cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
			cin>>chave;
			if(chave != proj->getChaveAcesso())
			{
				cout<<"#Chave de acesso errada, volte tentar.\n";
				goto REM_PROJ;
			}
			cout << "Projeto " << proj->getNome() << " de ID " << proj->getId()
					<< "removido\n";
			proj->removeAUsers();
			logger->removeProjeto(proj->getId());
			empresa.removeProjeto(proj);
			break;
		case 5:
			logger->imprimeProjetos();
			break;

INFO_PROJ:
		case 6:
			cout << "Projetos: \n";
			logger->imprimeProjetos();
			cout << "Selecione um projeto: ";
			cin >> opcao;
			if (opcao == 0)
				break;
			proj = empresa.editProj(opcao);
			cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
			cin>>chave;
			if(chave != proj->getChaveAcesso())
			{
				cout<<"#Chave de acesso errada, volte tentar.\n";
				goto INFO_PROJ;
			}
			proj->getInfo();
			break;

EDITA_PROJ:
		case 7:
			cout << "Projetos: \n";
			logger->imprimeProjetos();
			cout << "Selecione um projeto: ";
			cin >> opcao;

			if (opcao == 0)
				break;

			proj = empresa.editProj(opcao);
			cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
			cin>>chave;
			if(chave != proj->getChaveAcesso())
			{
				cout<<"#Chave de acesso errada, volte tentar.\n";
				goto EDITA_PROJ;
			}
			cout<< "Selecione uma opcao: \n"
				<< "1 - Mudar nome;\n"
				<< "2 - Mudar chave de acesso;\n";
			cin >> opcao;
			editarProjetos(empresa,proj->getId(), opcao);
			break;

		case 8:
			logger->getInfo();
			break;

		case 9:
			cout<< "Selecione  o que deseja mudar: \n"
					<< "1 - Email\n"
					<< "2 - Data de nascimento\n";

			cin >> opcao;
			editarUtilizador(empresa,logger,opcao);
			break;

		case 0:
			break;

		default:
			cout << "Escolha uma opcao valida.\n";
			break;
		}
	} while (opcao != 0);

}

void rotinaJunior(Utilizador* logger, Empresa & empresa) {
	int opcao;
	Projeto* proj;
	string nome,chave;

//	vector<Utilizador*>* v;

	cout << endl << "1 - Ver projetos\n"
				 << "2 - Fazer commit\n"
				 << "3 - Ver historico de commits\n"
				 << "4 - Ver informacoes do utilizador\n"
				 << "5 - Editar informacoes do utilizador\n"
				 << "0 - Voltar atrás\n";

	cin >> opcao;

	switch (opcao) {
	case 0:
		Login(empresa);
		break;
	case 1:
		logger->imprimeProjetos();
		break;

	case 2:
		addCommit(logger, empresa);
		empresa.converteJunior(logger);
		break;

HIST_PROJ:
	case 3:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
		cin>>chave;
		if(chave != proj->getChaveAcesso())
		{
			cout<<"#Chave de acesso errada, volte tentar.\n";
			goto HIST_PROJ;
		}
		proj->imprimeHistorico();
		break;

	case 4:
		logger->getInfo();
		break;

	case 5:
		cout<< "Selecione  o que deseja mudar: \n"
				<< "1 - Email\n"
				<< "2 - Data de nascimento\n";


		cin >> opcao;
		editarUtilizador(empresa,logger,opcao);
		break;

	default:
		break;
	}
}

void rotinaSenior(Utilizador* logger, Empresa& empresa) {
	int opcao;
	Projeto * proj;
	string nomeBranch;
	string nome1, nome2,chave;


	cout <<"1 - Ver Projetos;\n"
		<< "2 - Fazer commit num projeto;\n"
		<< "3 - Ver historico de commits;\n"
		<< "4 - Criar um branch num projeto;\n"
		<< "5 - Apagar branch de um projeto;\n"
		<< "6 - Fazer merge de dois branches;\n"
		<< "7 - Ver informacoes do utilizador\n"
		<< "8 - Editar informacoes do utilizador\n"
		<< "0 - Voltar atras;\n";

	cin >> opcao;
	switch (opcao) {
	case 0:
		Login(empresa);
		break;
	case 1:
		logger->imprimeProjetos();
		break;
	case 2:
		addCommit(logger, empresa);
		break;

HIST:
	case 3:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
		cin>>chave;
		if(chave != proj->getChaveAcesso())
		{
			cout<<"#Chave de acesso errada, volte tentar.\n";
			goto HIST;
		}
		proj->imprimeHistorico();
		break;

CRIA_BRANCH:
	case 4:
		//cria branch
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
		cin>>chave;
		if(chave != proj->getChaveAcesso())
		{
			cout<<"#Chave de acesso errada, volte tentar.\n";
			goto CRIA_BRANCH;
		}
		if (proj->getTipo() == "Basico") {
			cout << "Este é do tipo Basico (sem branches)\n"
					" Selecione outro Projeto\n";
			goto CRIA_BRANCH;
		}
		cout << "Digite o nome do branch: ";
		cin >> nomeBranch;
		try{
			dynamic_cast <Avancado*>(proj)->addBranch(nomeBranch);
		}catch (BranchRepetido & r){
			cout << "Ja existe um branch com o nome " << r.getName() << endl;
			goto CRIA_BRANCH;
		}

		break;
APAGA_BRANCH:
	case 5:
		//apaga branch
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		proj = empresa.editProj(opcao);
		cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
		cin>>chave;
		if(chave != proj->getChaveAcesso())
		{
			cout<<"#Chave de acesso errada, volte tentar.\n";
			goto APAGA_BRANCH;
		}

		dynamic_cast <Avancado*>(proj)->imprimeBranches();
		cout << "Digite o nome do branch: ";
		cin >> nomeBranch;
		try{
			dynamic_cast <Avancado*>(proj)->removeBranch(nomeBranch);
		}catch(NoSuchBranch &b){
			cout << "Nao existe um branch com o nome " << b.getName() << endl;
			goto APAGA_BRANCH;
		}
		break;

	case 7:
		logger->getInfo();
		break;

	case 8:
	cout<< "Selecione  o que deseja mudar: \n"
		<< "1 - Email\n"
		<< "2 - Data de nascimento\n";

		cin >> opcao;
		editarUtilizador(empresa,logger,opcao);
		break;


	case 6:
		// Merge
SEL_PROJ:
		logger->imprimeProjetos();
		cout << "Selecione um projeto: ";
		cin >> opcao;

		if (opcao == 0)
			break;

		try
		{
		proj = empresa.editProj(opcao);
		}
		catch(NoSuchProject & e)
		{
			cout << "Projeto com ID "<< e.getId() << "nao existe.\n";
			goto SEL_PROJ;
		}
		cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
		cin>>chave;
		if(chave != proj->getChaveAcesso())
		{
			cout<<"#Chave de acesso errada, volte tentar.\n";
			goto SEL_PROJ;
		}

SEL_MERGE_BRANCH:

		dynamic_cast <Avancado*>(proj)->imprimeBranches();
		cout
				<< "Digite o nome do primeiro branch (MASTER para fazer merge com o branch principal) : ";
		cin >> nome1;
		cout
				<< "Digite o nome do segundo branch (MASTER para fazer merge com o branch principal) : ";
		cin >> nome2;
		try{
		if (nome1 == "MASTER" && nome2 != "MASTER")
			dynamic_cast <Avancado*>(proj)->merge(nome2);
		else if(nome1 != "MASTER" && nome2 == "MASTER")
			dynamic_cast <Avancado*>(proj)->merge(nome1);
		else if(nome1 != "MASTER" && nome2 != "MASTER")
			dynamic_cast <Avancado*>(proj)->merge(nome1, nome2);
		else
		{
			cout << "Pelo menos um dos branches deve ser diferente de MASTER.\n";
			goto SEL_MERGE_BRANCH;
		}
		}
		catch(NoSuchBranch &b){
			cout << "Nao existe um branch com o nome " << b.getName() << ". Tente outra vez.\n\n";
		}
		break;


	}
}

void verRanking(Empresa & emp) {
	if(emp.getUsers().size()==0)
	{
		cout<<"Ainda nao existem utilizadores nesta empresa.\n";
		rotinaEmpresa(emp);
	}
	sortRanking(emp.getUsers(), &emp);
	emp.imprimeCoders();
}

void verRanking(Empresa & emp, Data d1, Data d2) {

	if(emp.getUsers().size()==0)
		{
			cout<<"Ainda nao existem utilizadores nesta empresa.\n";
			rotinaEmpresa(emp);
		}
	sortRanking(emp.getUsers(), &emp, d1, d2);
	emp.imprimeCoders();
}

void verRanking(Projeto & proj) {
	if(proj.getUsers().size()==0)
	{
		cout<<"Ainda nao existem utilizadores nesta empresa.\n";
		return;
	}
	sortRanking(proj.getUserRef(), &proj);
	proj.imprimeCoders();

}

void verRanking(Projeto & proj, Data d1, Data d2) {
	if(proj.getUsers().size()==0)
	{
		cout<<"Ainda nao existem utilizadores nesta empresa.\n";
		return;
	}
	sortRanking(proj.getUserRef(), &proj, d1, d2);
	proj.imprimeCoders();
}

void rotinaVerRanking(Empresa & emp) {
	int opcao, dia, mes, ano;
	Projeto* proj;
	string chave;
	do{
VER_RANK:
	cout << endl
		<< "Ver ranking de utilizadores:\n"
		<< "1- Da empresa;\n"
		<< "2- De um projeto;\n"
		<< "0-Voltar atras;\n" << endl;
	cin >> opcao;

	switch (opcao) {
	case 1:
		cout << "1- Ranking geral;\n"
			 << "2- Ranking entre duas datas\n"
			 << "0-Voltar atras\n";

		cin >> opcao;
		if (opcao == 0)
			goto VER_RANK;
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
RANK_PROJ:
	case 2:
		if(emp.getProjetos().size()==0)
		{
			cout << "Não existem projetos.\n";
			break;
		}
		cout << "Projetos disponiveis:\n";
		emp.imprimeProjetos();
		cout << "Selecione o projeto por ID:\n"
			 << "0 - Voltar atras\n";
		cin >> opcao;

		if (opcao == 0)
			goto VER_RANK;
		proj = emp.editProj(opcao);
		cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
		cin>>chave;
		if(chave != proj->getChaveAcesso())
		{
			cout<<"#Chave de acesso errada, volte tentar.\n";
			goto RANK_PROJ;
		}

		cout << "1 - Ranking geral;\n"
			 << "2 - Ranking entre duas datas\n"
			 << "0 - Recomecar\n";
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
	}while(opcao!=0);

}

void addCommit(Utilizador* logger, Empresa & empresa){

	Branch * branch = new Branch("eras");
	Commit* newCommit;
	int opcao, volume, dia, mes, ano;
	string nome = "MASTER" , chave;
	Projeto* proj;


COMMIT_PROJ:
	logger->imprimeProjetos();
	cout << "Selecione um projeto(ID): ";
	cin >> opcao;
	if (opcao == 0)
		return;

	proj = empresa.editProj(opcao);
	cout<< "Digite a chave de acesso do projeto "<< proj->getNome()<<": \n";
	cin>>chave;
	if(chave != proj->getChaveAcesso())
	{
		cout<<"#Chave de acesso errada, volte tentar.\n";
		goto COMMIT_PROJ;
	}
	if(proj->getTipo()== "Avancado")
	{
SEL_BRANCH:
		cout <<endl<< "Selecione um Branch:\n";
		dynamic_cast <Avancado*> (proj)->imprimeBranches();
		cin >> nome;
		if(nome != "MASTER")
		{
			try
			{
			branch = dynamic_cast <Avancado*> (proj)->existeBranch(nome);
			}
			catch(NoSuchBranch &e)
			{
			cout << "Branch com nome "<< nome<< "não existe neste projeto.\n";
			goto SEL_BRANCH;
			}
		}

	}

	cout << "Volume do commit: ";
	cin >> volume;
	cout << "Data do commit(dd/mm/aa): ";
	cin >> dia >> mes >> ano;
	newCommit = new Commit(logger, volume, dia, mes, ano);
	if(nome == "MASTER")
		proj->addCommit(*newCommit);

	else
		branch->adicionaCommit(*newCommit);

	cout<<"Adicionado o commit com ID "<< newCommit->getID() << " ao branch " << nome << endl;


}




void editarProjetos(Empresa & empresa, int ID, int opcao){
	Projeto* proj;
	string nome, chave;

	proj = empresa.editProj(ID);

	switch(opcao)
	{
	case 1: //MUDAR O NOME
		cout<<"Digite o novo nome: ";
		cin>>nome;
		proj->setNome(nome);
		break;

	case 2:
		cout<<"Digite a nova chave de acesso: \n";
		cin>>chave;
		proj->setChaveAcesso(chave);
		break;

	}

}

void editarUtilizador(Empresa & emp,Utilizador* logger, int opcao){
	string email;
	int d,m,a;
	switch(opcao)
	{

	case 1://MUDAR EMAIL
		cout<<"Digite o novo email: ";
		cin>>email;
		try
		{
			emp.existeEmail(email);
		}
		catch(EmailRepetido &e)
		{
			cout<<"Ja existe um utilizador com o email "<< e.getEmail() << " atribuido.\n";
			break;
		}
		logger->setEmail(email);
		cout<< "Email " << logger->getEmail() << " atribuido a "<< logger->getNome() << endl;

		break;

	case 2:
		cout<< "Digite a data de Nascimento (dd/mm/aaaa)\n";
		cin >> d>>m>>a;
		logger->setData(d,m,a);
		break;
	}
}
