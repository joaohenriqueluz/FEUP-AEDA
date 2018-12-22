#include "empresa.h"
#include <fstream>

using namespace std;


bool inputValidation();

int Empresa::novoProjeto() {
	string nome, tipo,chave;
	Avancado* projA;
	Projeto* projB;
PROJ_NAME:
	cout << "Nome do Projeto? \n";
	cin >> nome;
	if (inputValidation()) {
		cout << "\n*Opcao invalida*\n\n";
		goto PROJ_NAME;
	}
	cout << "Chave de acesso do Projeto? \n";
	cin>>chave;
	if (inputValidation()) {
		cout << "\n*Opcao invalida*\n\n";
		goto PROJ_NAME;
	}
TIPO:
	cout << "Projeto Basico ou Avancado?(B/A)\n";
	cin >> tipo;

	if (inputValidation()) {
		cout << "\n*Opcao invalida*\n\n";
		goto TIPO;
	}
	if (tipo == "B") {
		projB = new Projeto(nome, "Basico");
		projB->setChaveAcesso(chave);
		_projetos.push_back(projB);
		cout << "Projeto " << nome << " criado com ID " << projB->getId()
				<< endl;
		return projB->getId();
	} else if (tipo == "A") {
		projA = new Avancado(nome);
		projA->setChaveAcesso(chave);
		_projetos.push_back(projA);
		cout << "Projeto " << nome << " criado com ID " << projA->getId()
				<< endl;
		return projA->getId();
	} else {
		cout << "Opcao invalida! Tenta outra vez. \n\n";
		goto TIPO;
	}

}

void Empresa::removeProjeto(Projeto* proj) {
	cout<< "\n"<< proj->getNome()<<" removido\n";
	removeObjeto<Projeto*>(_projetos, proj);
}


void Empresa::novoUtilizador() {

	Gestor* gestor;
	Senior* senior;
	Junior* junior;
	string nome, email, status;
	int d, m, a, NIF, reput;

NOME_UTI:
	cout << "Nome do Utilizador: ";
	cin>> nome;
	if (inputValidation()) {
		cout << "\n*Opcao invalida*\n\n";
		goto NOME_UTI;
	}

	try {
		repeteUser(nome);
	} catch (UserRepetido &e) {
		cout << e.getName() << " ja existe. Introduza outro nome.\n\n";
		goto NOME_UTI;

	}


	cout << "Data de Nascimento(d/m/a): ";
	cin >> d>>m>>a;
	if (inputValidation() || d < 0 || d > 31 || m < 0 || m > 12 || a < 0) {
		cout << "\n*Opcao invalida*\n\n";
		goto NOME_UTI;
	}
	cout << "Email: ";
	cin >> email;
	size_t at_index = email.find_first_of('@', 0);
	if (inputValidation() || !(at_index != std::string::npos && email.find_first_of('.', at_index) != std::string::npos)) {
		cout << "Invalid input, please try again!\n\n";
		goto NOME_UTI;
	}

NIF_UTI:
	cout << "Digite NIF: ";
	cin >> NIF;
	if (inputValidation() || NIF > 9999999999 || NIF < 99999999) {
		cout << "\n*Opcao invalida*\n\n";
		goto NIF_UTI;

	}


	try {
		existeNIF(NIF);
	} catch (NIFRepetido &e) {
		cout << e.getNIF()
				<< " ja existe. Introduza um utilizador com um NIF diferente.\n\n";
		goto NIF_UTI;

	}

TIPO_UNI:
	cout << "Tipo(Gestor(G)/Programador(S/J)): ";
	cin >> status;
	if (inputValidation()) {
			cout << "\n*Opcao invalida*\n\n";
			goto TIPO_UNI;
		}
	if (status == "G") {
		gestor = new Gestor(nome, d, m, a, email, 2500, NIF, "Gestor");
		cout << "\nGestor criado!\n";
		_utilizadores.push_back(gestor);
	} else if (status == "S") {

		senior = new Senior(nome, d, m, a, email, 1000, NIF, "Senior");
		cout << "\nSenior criado!\n";
		_utilizadores.push_back(senior);

	} else if (status == "J") {
		cout << "Reputacao: ";
		cin >> reput;
		if (inputValidation() || reput < 0 || reput > 10000) {
			cout << "\n*Opcao invalida*\n\n";
			goto TIPO_UNI;
		}
		junior = new Junior(nome, d, m, a, email, reput, NIF, "Junior");
		cout << "\nJunior criado!\n";
		_utilizadores.push_back(junior);
	}
	else
	{
		cout<<"Tipo de utilizador invalido. Volte a tentar.\n";
		goto TIPO_UNI;
	}

}

bool Empresa::removeUtilizador(string nome) {
Utilizador* user = existeUser(nome);


		for(unsigned int i=0; i < user->getProjetos().size();i++)
		{
			if(user->getCargo()== "Gestor")
			{
				removeProjeto(editProj(user->getProjetos().at(i)));
			}
			else{
				editProj(user->getProjetos().at(i))->removeUser(nome);
			}
		}
		cout<<"\n"<<user->getNome()<<" removido\n";
	return removeObjeto<Utilizador*>(_utilizadores, user);
}


void Empresa::imprimeSalarios() {

	float Soma = 0;

	if(_utilizadores.size() == 0)
	 {
		 cout << "Nao existem utilizadores.\n";
		 return;
	 }


	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		cout << "Nome: " << _utilizadores.at(i)->getNome() << " Cargo: "
				<< _utilizadores.at(i)->getCargo() << " Salario: "
				<< _utilizadores.at(i)->getSalario() << endl;
		Soma += _utilizadores.at(i)->getSalario();
	}
	cout << "Soma total dos salarios: " << Soma << endl;
}

Utilizador* Empresa::existeUser(string nome) {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNome() == nome) {
			return _utilizadores.at(i);

		}
	}
	throw(NoSuchUser(nome));
}

void Empresa::repeteUser(string nome) {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNome() == nome) {
			throw(UserRepetido(nome));

		}
	}
	return;
}

void Empresa::existeNIF(int nif) {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNIF() == nif) {
			throw NIFRepetido(nif);

		}
	}
	return;
}

void Empresa::existeEmail(string email){
	for (unsigned int i = 0; i < _utilizadores.size(); i++)
	{
		if (_utilizadores.at(i)->getEmail() == email)
		{
			throw EmailRepetido(email);
		}
	}
return;
}

Utilizador* Empresa::existeUserID(int nif){
	Utilizador* u = new Utilizador();
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNIF() == nif) {
			u = _utilizadores.at(i);
		}
	}
	return u;
}


Projeto* Empresa::editProj(int id) {
	for (unsigned int i = 0; i < getProjetos().size(); i++) {
		if (getProjetos().at(i)->getId() == (unsigned int) id)
			return getProjetos().at(i);
	}
	throw(NoSuchProject((unsigned int) id));
}

int Empresa::getVolume(string nome, Data d1, Data d2) const {
	int volume = 0;
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		volume += _projetos.at(i)->getVolume(nome, d1, d2);
	}
	return volume;
}

float Empresa::getFreq(string nome, Data d1, Data d2) const {
	float freq = 0;
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		freq += _projetos.at(i)->getFreq(nome, d1, d2);
	}
	return freq;
}

void Empresa::imprimeUser() {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		cout << i + 1 << "# " << _utilizadores.at(i)->getNome()
				<< "     Cargo: " << _utilizadores.at(i)->getCargo() << endl;
	}
}

void Empresa::imprimeCoders() {
	int counter=1;
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getCargo() == "Gestor")
			continue;
		cout << counter << "# " << _utilizadores.at(i)->getNome()
				<< "     Cargo: " << _utilizadores.at(i)->getCargo() << endl;
		counter++;
	}
}

void Empresa::imprimeProjetos() {
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		cout << _projetos.at(i)->getNome() << " ID: "
				<< _projetos.at(i)->getId() << endl;
	}
}

void Empresa::readUsers(string ficheiro) {
	Utilizador* _gestor;
	Utilizador* _junior;
	Utilizador* _senior;

	ifstream file;
	file.open(ficheiro);
	string nome, rank, email, data, n, ids, reputacao, money;
	char /*ch,*/b;
	int d, m, a, /*id,*/nif, rep;
	float salario;
	vector<int> dataV;
	vector<int> projId;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, nome);
			if(nome.empty()){
				continue;
			}
			getline(file, rank);
			if (rank == "J") {
				getline(file, reputacao);
				rep = stoi(reputacao);
			}
			file >> d >> b >> m >> b >> a;
			getline(file, n);
			cout << n;
			getline(file, email);
			projId.clear();
			while (1) {
				getline(file, ids);
				if (ids == "end")
					break;
				int id = stoi(ids);
				projId.push_back(id);
			}
			file >> nif;
			getline(file, n);
			if (rank != "J") {
				getline(file, money);
				salario = stof(money);
			}
			getline(file, n);

			if (rank == "G") {
				_gestor = new Gestor(nome, d, m, a, email, salario, nif,
						"Gestor");
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_gestor->addProjeto(projId.at(i));
				}
				_utilizadores.push_back(_gestor);
			}
			if (rank == "S") {
				_senior = new Senior(nome, d, m, a, email, salario, nif,
						"Senior");
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_senior->addProjeto(projId.at(i));
				}
				_utilizadores.push_back(_senior);
			}

			if (rank == "J") {
				_junior = new Junior(nome, d, m, a, email, rep, nif, "Junior");
				dynamic_cast <Junior*>(_junior)->setSalario();
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_junior->addProjeto(projId.at(i));
				}
				_utilizadores.push_back(_junior);
			}

		}
		file.close();

	} else {
		cout << "\n*Ficheiro de utilizadores nao encontrado*\n" << endl;
		exit(0);
	}
}

void Empresa::readProjetos(string ficheiroP, string ficheiroC){
	ifstream file;
	file.open(ficheiroP);

	string temp, tipo, nome, pass, stringIDP, stringIDU, nomeBranch;
	int IDP, IDU;

	vector <Commit> commits = readCommits(_utilizadores,ficheiroC);

	vector <string> vecStringIDU;
	vector <Utilizador *> users;
	vector <Commit> vecCommits;
	vector <Commit> vecCommitsBranch;
	vector <Branch *> branches;

	if(file.is_open()){
		while(file.good()){
			getline(file,tipo);
			if(tipo.empty()){
				continue;
			}
			vecStringIDU.clear();
			users.clear();
			vecCommits.clear();
			vecCommitsBranch.clear();
			branches.clear();
			getline(file,nome);
			getline(file,pass);
			getline(file,stringIDP);
			IDP = stoi(stringIDP);

			getline(file,temp);

			do{
				getline(file,stringIDU);
				vecStringIDU.push_back(stringIDU);
			}while(stringIDU != "endU");

			for(unsigned int i = 0; i < vecStringIDU.size()-1; i++){
				IDU = stoi(vecStringIDU.at(i));
				Utilizador* u = existeUserID(IDU);
				users.push_back(u);
			}

			getline(file,temp);

			vecStringIDU.clear();

			do{
				getline(file,stringIDU);
				vecStringIDU.push_back(stringIDU);
			}while(stringIDU != "endC");

			for(unsigned int i = 0; i < vecStringIDU.size()-1; i++){
				IDU = stoi(vecStringIDU.at(i));
				for(unsigned int j = 0; j < commits.size(); j++){
					if((unsigned int)IDU == commits.at(j).getID()){
						vecCommits.push_back(commits.at(j));
						break;
					}
				}
			}

			vecStringIDU.clear();

			if(tipo == "Avancado"){
				do{
				getline(file,nomeBranch);
				if(nomeBranch == "endB"){
					break;
				}
					do {
						getline(file,stringIDU);
						vecStringIDU.push_back(stringIDU);
					}while (stringIDU != "endC");

					for (unsigned int i = 0; i < vecStringIDU.size() - 1; i++) {
						IDU = stoi(vecStringIDU.at(i));
						for (unsigned int j = 0; j < commits.size(); j++) {
							if ((unsigned int)IDU == commits.at(j).getID()) {
								vecCommitsBranch.push_back(commits.at(j));
								break;
							}
						}
					}

					Branch *b = new Branch(nomeBranch);
					b->addCommitVec(vecCommitsBranch);
					vecCommitsBranch.clear();
					vecStringIDU.clear();
					branches.push_back(b);
				}while(1);
			}

			if(tipo == "Avancado"){
				Avancado *av = new Avancado(nome);
				av->setID(IDP);
				av->setChaveAcesso(pass);

				for(unsigned int i = 0; i < users.size(); i++){
					av->addUtilizador(users.at(i));
				}
				for(unsigned int i = 0; i < vecCommits.size(); i++){
					av->addCommit(vecCommits.at(i));
				}

				for(unsigned int i = 0; i < branches.size(); i++){
					av->addBranch_ref(branches.at(i));
				}
				_projetos.push_back(av);
			}
			else{
				Projeto *proj = new Projeto(nome,tipo);
				proj->setID(IDP);
				proj->setChaveAcesso(pass);

				for(unsigned int i = 0; i < users.size(); i++){
					proj->addUtilizador(users.at(i));
				}
				for(unsigned int i = 0; i < vecCommits.size(); i++){
					proj->addCommit(vecCommits.at(i));
				}

				_projetos.push_back(proj);
			}
		}
		file.close();
		setProjLastID();
	}
	else {
			cout << "\n*Ficheiro de projetos nao encontrado*\n" << endl;
			exit(0);
		}
}

void Empresa::writeUsers(string ficheiro) {
	ofstream file;
	file.open(ficheiro);
	string cargo;
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		file << _utilizadores.at(i)->getNome() << endl;
		file << _utilizadores.at(i)->getCargo().at(0) << endl;
		if (_utilizadores.at(i)->getCargo() == "Junior") {
			file << dynamic_cast <Junior*>(_utilizadores.at(i))->getReputacao() << endl;
		}
		file << _utilizadores.at(i)->getDataNascimento().getDia() << "/"
				<< _utilizadores.at(i)->getDataNascimento().getMes() << "/"
				<< _utilizadores.at(i)->getDataNascimento().getAno() << endl;
		file << _utilizadores.at(i)->getEmail() << endl;
		vector<int> ids = _utilizadores.at(i)->getProjetos();
		if (ids.size() != 0) {
			for (unsigned int j = 0; j < ids.size(); j++) {
				file << ids.at(j) << endl;
			}
		}
		file << "end" << endl;
		file << _utilizadores.at(i)->getNIF() << endl;
		if (_utilizadores.at(i)->getCargo() != "Junior") {
			file << _utilizadores.at(i)->getSalario() << endl;
		}
		file<<endl;
	}
	file.close();

}




void Empresa::writeProjetos(string ficheiro) {
	ofstream file;
	file.open(ficheiro);
	string cargo;
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		file << _projetos.at(i)->getTipo() << endl;
		file << _projetos.at(i)->getNome() << endl;
		file << _projetos.at(i)->getChaveAcesso()<< endl;
		file << _projetos.at(i)->getId() << endl;
		file << "Users" << endl;
 		vector<Utilizador*> users = _projetos.at(i)->getUsers();
		for (unsigned int j = 0; j < users.size(); j++){
			file << users.at(j)->getNIF() << endl;
		}
		file << "endU" << endl;
 		file << "Commits" << endl;
		vector<Commit> com = _projetos.at(i)->getCommits();
		for (unsigned int j = 0; j < com.size(); j++){
			file << com.at(j).getID() << endl;
		}
		file << "endC" << endl;
 		if (_projetos.at(i)->getTipo() == "Avancado"){
			vector<Branch*> branches = dynamic_cast <Avancado*> (_projetos.at(i))->getBranches();
			if (branches.size() != 0){
				for (unsigned int j = 0; j < branches.size(); j++){
					file << branches.at(j)->getNome() << endl;
 					com = branches.at(j)->getCommits();
					for (unsigned int k = 0; k < com.size(); k++){
						file << com.at(k).getID() << endl;
					}
					file << "endC" << endl;
				}
			}
			file << "endB" << endl;
 		}
			file << endl;
	}
	file.close();

 }
 void removeRepetidos(vector <Commit> & commits){
	for(unsigned int i = 0; i < commits.size(); i++){
		unsigned int id = commits.at(i).getID();
		for (unsigned int j = i+1; j < commits.size(); ++j) {
			if (id == commits.at(j).getID()){
				commits.erase(commits.begin()+j);
			}
		}
	}
}
 void Empresa::writeCommits(string ficheiro){
	ofstream file;
	file.open(ficheiro);
	vector <Projeto *> proj = getProjetos();
	vector <Commit> commits;
	vector <Commit> aux_commits;
 	if(proj.size() == 0){
		cout << "Nao existem projetos" << endl;
		return;
	}
 	for(unsigned int i = 0; i < proj.size(); i++){
		aux_commits = proj[i]->getCommits();
		for(unsigned int j = 0; j < aux_commits.size(); j++){
			commits.push_back(aux_commits.at(j));

		}
		if(proj.at(i)->getTipo() == "Avancado")
		{
			vector<Branch*> branchesss = dynamic_cast<Avancado*> (proj.at(i))->getBranches();
			for(unsigned int k =0;k < branchesss.size();k++)
			{
				vector<Commit> comitsss = branchesss.at(k)->getCommits();
				for(unsigned int l = 0; l< comitsss.size(); l++)
				{
					commits.push_back(comitsss.at(l));
				}
			}
		}

	}

 	removeRepetidos(commits);
 	for (unsigned int k = 0; k < commits.size(); ++k) {

		file << commits.at(k).getID() << endl;
		file << "Users" << endl;
		file << commits.at(k).getUser()->getNIF() << endl;
		file << "endU" << endl;
		file << commits.at(k).getVolume() << endl;
		file << commits.at(k).getData().getDia() << "/"
			 << commits.at(k).getData().getMes() << "/"
			 << commits.at(k).getData().getAno() << endl << endl;

	}
}




bool Empresa::converteJunior(Utilizador * junior) {
vector<int> projetoSenior;
	if (dynamic_cast <Junior*> (junior)->getReputacao() > 9999) {
		string nome = junior->getNome();
		int dia = junior->getDataNascimento().getDia();
		int mes = junior->getDataNascimento().getMes();
		int ano = junior->getDataNascimento().getAno();
		int NIF = junior->getNIF();
		projetoSenior = junior->getProjetos();
		string email = junior->getEmail();
		Utilizador* novoSenior = new Senior(nome, dia, mes, ano, email, 1000,
				NIF, "Senior");
		for(unsigned int i = 0; i < projetoSenior.size();i++)
			novoSenior->addProjeto(projetoSenior.at(i));
		for(unsigned int i = 0; i< novoSenior->getProjetos().size(); i++)
		{	try
			{
			editProj(novoSenior->getProjetos().at(i))->addUtilizador(novoSenior);
			}catch(NoSuchProject & e)
			{
				cout << "\n*Falha a converter Junior para Senior*\n";
				return false;
			}
		}
		removeUtilizador(junior->getNome());
		getUsers().push_back(novoSenior);
		return true;



	}
	return false;
}

void Empresa::setProjLastID(){
	unsigned int maior = 0;
	unsigned int i;
	for(i = 0; i < _projetos.size(); i++){
		if(_projetos.at(i)->getId() > maior){
			maior = _projetos.at(i)->getId();
		}
	}

	Projeto *p = new Projeto("p", "Basico");
	p->setLastID(maior);
}

void Empresa::addClient(Client c){
	clients.insert(c);
}

void Empresa::removeClient(Client c){
	clients.remove(c);
}


bool inputValidation(){
	if (cin.fail()) {
			cin.clear();
			cin.ignore(100000000, '\n');
			return true;
		}

		string buffer;
		getline(cin, buffer);
		if (!buffer.empty() && buffer.find_first_not_of(" ") != (size_t) -1) {
			return true;
		}

		return false;
}


