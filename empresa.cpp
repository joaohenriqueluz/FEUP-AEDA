#include "empresa.h"
#include <fstream>

using namespace std;


bool inputValidation();

int Empresa::novoProjeto() {
	int d,m,a,u,nif;
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


	cout << "Data de estimada para a conclusao: ";
	cin >> d>>m>>a;
	while(inputValidation() || d < 0 || d > 31 || m < 0 || m > 12 || a < 0) {
		cout << "\n*Data invalida*\n\nVolte a tentar: ";
		cin >> d>>m>>a;
	}
	Data d1(d,m,a);


	cout << "Data de limite de conclusao: ";
	cin >> d>>m>>a;
	while(inputValidation() || d < 0 || d > 31 || m < 0 || m > 12 || a < 0) {
		cout << "\n*Data invalida*\n\nVolte a tentar: ";
		cin >> d>>m>>a;
	}

	Data d2(d,m,a);

	cout <<"Urgencia do Projeto 1-10 [muito urgente]-[pouco urgente]: ";
	cin >> u;
	while(inputValidation() || u <1 || u > 10) {
		cout << "\n*Valor invalido*\n\nVolte a tentar: ";
		cin >>u;
	}

	cout<< "NIF do cliente: "<<endl;
	cin>>nif;
	while(inputValidation() || nif >= 1000000000 || nif <= 99999999 || getClient(nif).getContacto()== 0) {
		cout << "\n*Valor invalido*\n\nVolte a tentar: [0 para voltar]";
		cin >>nif;
		if(nif == 0)
		{
			return 0;
		}
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
		projB->setClient(nif);
		_projetos.push_back(projB);
		cout << "Projeto " << nome << " criado com ID " << projB->getId()
				<< endl;
		Ticket T(d1,d2,u,projB);
		_tickets.push(T);
		addProjectToClient(nif, projB);
		return projB->getId();
	} else if (tipo == "A") {
		projA = new Avancado(nome);
		projA->setChaveAcesso(chave);
		projA->setClient(nif);
		_projetos.push_back(projA);
		addProjectToClient(nif, projA);
		cout << "Projeto " << nome << " criado com ID " << projA->getId()
				<< endl;
		Ticket T(d1,d2,u,projA);
		_tickets.push(T);
		return projA->getId();
	} else {
		cout << "Opcao invalida! Tenta outra vez. \n\n";
		goto TIPO;
	}

}

void Empresa::addProject (Projeto* proj){
	_projetos.push_back(proj);
}

void Empresa::removeProjeto(Projeto* proj) {
	cout<< "\n"<< proj->getNome()<<" removido\n";
	removeTicket(proj);
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

	removeUserFromPastProj(user->getNIF());
	for (unsigned int i = 0; i < user->getProjetos().size(); i++) {
		if (user->getCargo() == "Gestor") {
			removeProjeto(editProj(user->getProjetos().at(i)));
		} else {
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
	cout <<"\n("<<_projetos.size()<<")\n";
}

void Empresa::readUsers(string ficheiro) {
	Utilizador* _gestor;
	Utilizador* _junior;
	Utilizador* _senior;

	ifstream file;
	file.open(ficheiro);
	string nome, rank, email, data, n, ids, reputacao, money, stringProj;
	char /*ch,*/b;
	int d, m, a, /*id,*/nif, rep, proj;
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
			getline(file,stringProj);
			proj = stoi(stringProj);
			getline(file, n);

			if (rank == "G") {
				_gestor = new Gestor(nome, d, m, a, email, salario, nif,
						"Gestor");
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_gestor->addProjeto(projId.at(i));
				}
				_gestor->setNextProject(proj);
				_utilizadores.push_back(_gestor);
			}
			if (rank == "S") {
				_senior = new Senior(nome, d, m, a, email, salario, nif,
						"Senior");
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_senior->addProjeto(projId.at(i));
				}
				_senior->setNextProject(proj);
				_utilizadores.push_back(_senior);
			}

			if (rank == "J") {
				_junior = new Junior(nome, d, m, a, email, rep, nif, "Junior");
				dynamic_cast <Junior*>(_junior)->setSalario();
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_junior->addProjeto(projId.at(i));
				}
				_junior->setNextProject(proj);
				_utilizadores.push_back(_junior);
			}

		}
		file.close();

	} else {
		cout << "\n*Ficheiro de utilizadores nao encontrado*\n" << endl;
		exit(0);
	}
}

void Empresa::readclients(string ficheiro){
	ifstream file;
	file.open(ficheiro);

 	string nome, email, nP, stringNif, stringCont, stringID;
	int nproj, id;
	vector<int> ids;
	unsigned nif, cont;

 	if(!file.is_open()){
		cout << "File not found" << endl;
		return;
	}

 	while(file.good()){
		getline(file,nome);
		if(nome.empty()){
			continue;
		}
		getline(file,email);

 		getline(file,nP);
		nproj = stoi(nP);

 		getline(file,stringNif);
		nif = stoi(stringNif);

 		getline(file,stringCont);
		cont = stoi(stringCont);

 		while(1){
			getline(file,stringID);
			if(stringID == "endP"){
				break;
			}
			id = stoi(stringID);
			ids.push_back(id);
		}

 		Client c(nome,email,cont,nif);

 		for( unsigned int i = 0; i < ids.size(); i++){
			for(unsigned int j = 0; j < _projetos.size(); j++){
				if((unsigned int)ids.at(i) == _projetos.at(j)->getId()){
					c.addProj(_projetos.at(j));
				}
			}
		}

 		c.setNProj(nproj);

 		addClient(c);
		ids.clear();
	}
}

 void Empresa::writeClients(string ficheiro){
	ofstream file;
	file.open(ficheiro);

 	BSTItrIn <Client> it (_clients);

 	while (!it.isAtEnd()){
		file << it.retrieve().getNome() << endl;
		file << it.retrieve().getEmail() << endl;
		file << it.retrieve().getNProj() << endl;
		file << it.retrieve().getNif() << endl;
		file << it.retrieve().getContacto() << endl;

 		for(unsigned int i = 0;  i < it.retrieve().getProjetos().size(); i++){
			file << it.retrieve().getProjetos().at(i)->getId() << endl;
		}

 		file << "endP" << endl;
		file << endl;

 		it.advance();
	}


 }

 void Empresa::readTickets(string ficheiro){
	ifstream file;
	file.open(ficheiro);

 	Projeto* proj =new Projeto("","");
	proj->setID(0);

 	int d1, m1, a1, d2, m2, a2, urgencia, IDP;
	string temp, stringU, stringIDP, n;
	char b;

 	if(!file.is_open()){
		cout << "File not found" << endl;
		return;
	}

 	while (file.good()){
		file >> d1 >> b >> m1 >> b >> a1;
		getline(file, n);
		file >> d2 >> b >> m2 >> b >> a2;
		getline(file, n);

 		getline(file, stringU);
		urgencia = stoi(stringU);

 		getline(file, stringIDP);
		IDP = stoi(stringIDP);


 		for (unsigned int i = 0; i < _projetos.size(); i++) {
			if ((unsigned int)IDP == _projetos.at(i)->getId()) {
				proj = _projetos.at(i);
			}
		}

 		Data ECT(d1, m1, a1);
		Data TTC(d2, a2, m2);

 		Ticket t(ECT, TTC, urgencia, proj);

 		_tickets.push(t);

 		getline(file,temp);
	}
}

 void Empresa::writeTickets(string ficheiro){
	ofstream file;
	file.open(ficheiro);

 	queue<Ticket> temp;

 	while(!_tickets.empty()){
		Ticket t = _tickets.top();
		_tickets.pop();

 		file << t.getECT().getDia() << "/"
				<< t.getECT().getMes() << "/"
				<< t.getECT().getAno() << endl;

 		file << t.getTTC().getDia() << "/"
				<< t.getTTC().getMes() << "/"
				<< t.getTTC().getAno() << endl;

 		file << t.getUrgencia() << endl;
		file << t.getProjeto()->getId() << endl;
		file << endl;

 		temp.push(t);
	}

 	while(!temp.empty()){
		_tickets.push(temp.front());
		temp.pop();
	}
}

void Empresa::readProjetos(string ficheiroP, string ficheiroC){
	ifstream file;
	file.open(ficheiroP);

	string temp, tipo, nome, pass, stringIDP, stringIDU, stringIDC, nomeBranch, terminado;
	int IDP, IDU, IDC;

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
			getline(file,stringIDC);
			IDC = stoi(stringIDC);
			getline(file,terminado);
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
				av->setClient(IDC);
				for(unsigned int i = 0; i < users.size(); i++){
					av->addUtilizador(users.at(i));
				}
				for(unsigned int i = 0; i < vecCommits.size(); i++){
					av->addCommit(vecCommits.at(i));
				}

				for(unsigned int i = 0; i < branches.size(); i++){
					av->addBranch_ref(branches.at(i));
				}
				if(terminado == "ter"){
					addPastProject (av);
				}
				else{
					_projetos.push_back(av);
				}
			}
			else{
				Projeto *proj = new Projeto(nome,tipo);
				proj->setID(IDP);
				proj->setChaveAcesso(pass);
				proj->setClient(IDC);

				for(unsigned int i = 0; i < users.size(); i++){
					proj->addUtilizador(users.at(i));
				}
				for(unsigned int i = 0; i < vecCommits.size(); i++){
					proj->addCommit(vecCommits.at(i));
				}
				if(terminado == "ter"){
					addPastProject (proj);
				}
				else{
					_projetos.push_back(proj);
				}
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
		file << _utilizadores.at(i)->getNextProject() << endl;
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
		file << _projetos.at(i)->getClient() << endl;
		file << "des" << endl;
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
	HashTabProjetos::const_iterator it = _pastProjects.begin();

	 	while (it != _pastProjects.end()) {
			file << it->getProjeto()->getTipo() << endl;
			file << it->getProjeto()->getNome() << endl;
			file << it->getProjeto()->getChaveAcesso() << endl;
			file << it->getProjeto()->getId() << endl;
			file << it->getProjeto()->getClient() << endl;
			file << "ter" << endl;
			file << "Users" << endl;
			vector<Utilizador*> users = it->getProjeto()->getUsers();
			for (unsigned int j = 0; j < users.size(); j++) {
				file << users.at(j)->getNIF() << endl;
			}
			file << "endU" << endl;
			file << "Commits" << endl;
			vector<Commit> com = it->getProjeto()->getCommits();
			for (unsigned int j = 0; j < com.size(); j++) {
				file << com.at(j).getID() << endl;
			}
			file << "endC" << endl;
			if (it->getProjeto()->getTipo() == "Avancado") {
				vector<Branch*> branches =
						dynamic_cast<Avancado*>(it->getProjeto())->getBranches();
				if (branches.size() != 0) {
					for (unsigned int j = 0; j < branches.size(); j++) {
						file << branches.at(j)->getNome() << endl;
						com = branches.at(j)->getCommits();
						for (unsigned int k = 0; k < com.size(); k++) {
							file << com.at(k).getID() << endl;
						}
						file << "endC" << endl;
					}
				}
				file << "endB" << endl;
			}
			file << endl;
			it++;
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


//--------- BINARY TREE ----------------------------------------------------

void Empresa::addClient(Client c){
	_clients.insert(c);
}

void Empresa::removeClient(Client c){
	_clients.remove(c);
}

vector<Projeto*> Empresa::getProjectsOfClient(Client c){

	vector <Projeto*> projetos;

	Client ItemNotFound ("","",0, 0);
	Client tmp(c.getNome(), c.getEmail(), c.getContacto(), c.getNif());
	Client finder = _clients.find(tmp);

	if (finder == ItemNotFound){
		return projetos;
	}

	projetos = finder.getProjetos();

	return projetos;
}

Client Empresa::getClient (unsigned nif){
	Client cliente ("","",0, 0);
	BSTItrIn <Client> it (_clients);

	while (!it.isAtEnd()){
		if (it.retrieve().getNif() == nif){
			return it.retrieve();
		}
		it.advance();
	}

	return cliente;
}

void Empresa::addProjectToClient (unsigned nif, Projeto * proj){ //TODO: bool???????????????

	Client temp = getClient(nif);
	_clients.remove(temp);
	temp.addProj(proj);
	_clients.insert(temp);

}

void Empresa::removeProjectFromClient (unsigned nif, unsigned int id_proj){

	Client temp = getClient(nif);
	_clients.remove(temp);
	temp.removeProj(id_proj);
	_clients.insert(temp);

}

bool Empresa::modifyContacto (unsigned nif, unsigned novo_num){

	Client cl = getClient(nif);
	if (cl.getNome().empty()){
		return false;
	}
	_clients.remove(cl);
	cl.setContacto(novo_num);
	_clients.insert(cl);
	return true;
}



//--------- HASH TABLE ----------------------------------------------------

void Empresa::alterarChavePastProj (Projeto* proj, string novaChave){
	ProjetoPtr tmp_p (proj);
	HashTabProjetos::const_iterator it;

	it = _pastProjects.find(tmp_p);

	_pastProjects.erase(it);
	tmp_p.setChaveAcesso(novaChave);
	_pastProjects.insert (tmp_p);
}

void Empresa::alterarNomePastProj (Projeto* proj, string novoNome){
	ProjetoPtr tmp_p (proj);
	HashTabProjetos::const_iterator it;

	it = _pastProjects.find(tmp_p);

	_pastProjects.erase(it);
	tmp_p.setNome(novoNome);
	_pastProjects.insert (tmp_p);
}

void Empresa::toPastProject (unsigned int id){
	Projeto * proj = editProj(id); //TODO: ver excecao??
	removeProjeto(proj);
	addPastProject(proj);
	proj->removeAUsers();
	unsigned cl = proj->getClient();
	removeProjectFromClient(cl, id);
}

void Empresa::toWorkingProject (unsigned int id){
	Projeto * proj = getPastProject(id);
	removePastProject(id);
	this->addProject(proj);

	vector<Utilizador*> users = proj->getUsers();
	for (unsigned int i = 0; i < users.size(); i++){
		users.at(i)->addProjeto(id);
	}
	unsigned cl = proj->getClient(); //TODO: ver se n existe?? pode ja ter sido eliminado
	this->addProjectToClient(cl, proj);

}

void Empresa::addPastProject (Projeto* proj){
	_pastProjects.insert(proj);
}

bool Empresa::removePastProject (unsigned int id){
	HashTabProjetos::const_iterator it = _pastProjects.begin();

	while (it != _pastProjects.end()){
		if (it->getID() == id){
			it = _pastProjects.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

Projeto* Empresa::getPastProject (unsigned int id){
	HashTabProjetos::const_iterator it = _pastProjects.begin();

		while (it != _pastProjects.end()){
			if (it->getID() == id){
				return it->getProjeto();
			}
			it++;
		}
		throw NoSuchProject(id);
}

list<Projeto*> Empresa::pastProjectsWithUser (int NIF){
	list<Projeto*> res;
	HashTabProjetos::const_iterator it = _pastProjects.begin();

	while (it != _pastProjects.end()){
		vector<Utilizador*> users = it->getUsers();
		for (unsigned int i = 0; i < users.size(); i++){
			if (users.at(i)->getNIF() == NIF){
				res.push_back(it->getProjeto());
				break;
			}
		}
		it++;
	}

	return res;
}

list<Projeto*> Empresa::pastProjectsWithClient (unsigned int NIF){
	list<Projeto*> res;
	HashTabProjetos::const_iterator it = _pastProjects.begin();

	while (it != _pastProjects.end()){
		if (it->getClient() == NIF){
			res.push_back(it->getProjeto());
		}
		it++;
	}

	return res;
}



void Empresa::printPastproj()
{
	HashTabProjetos::iterator it = _pastProjects.begin();
	HashTabProjetos:: iterator ite = _pastProjects.end();
	int i = 0;
	while(it != ite)
	{	i++;
		cout<<"|ID: "<< it->getID()
			<<" Nome: "<< it->getName()
			<<" Tipo: "<< it->getProjeto()->getTipo() << endl;

		it++;

	}
	if(i == 0)
	{
		cout << "\n*Ainda nao existem projetos terminados*\n";
	}
}

bool Empresa::existePastProj(int id)
{
	HashTabProjetos::iterator it = _pastProjects.begin();
	HashTabProjetos:: iterator ite = _pastProjects.end();
	while(it != ite)
	{
	if(it->getID()== (unsigned)id)
		return true;
	}

	return false;
}


void Empresa::removeUserFromPastProj(int NIF)
{

	HashTabProjetos::const_iterator it = _pastProjects.begin();

	while (it != _pastProjects.end()) {
		vector<Utilizador*> users = it->getUsers();
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users.at(i)->getNIF() == NIF) {
				users.erase(i + users.begin());
				ProjetoPtr p(it->getProjeto());
				p.getProjeto()->setUsers(users);
				break;
			}
		}
		it++;
	}
}

void Empresa::removeClientFromPastProj(unsigned int NIF) {
	HashTabProjetos::const_iterator it = _pastProjects.begin();

	while (it != _pastProjects.end()) {
		if (it->getClient() == NIF) {
			_pastProjects.erase(it);

			break;
		}

		it++;
	}
}


void Empresa::printPPClient(list<Projeto*> lista)
{
	list<Projeto*>::iterator it = lista.begin();
	list<Projeto*>::iterator ite = lista.end();
	int i= 0;
	while(it!= ite)
	{
		cout<< i+1 << "# - "<< (*it)->getNome()<<"	"
			<<"Tipo: " << (*it)->getTipo()
			<<"	Volume: "<< (*it)->getVolumeTotal(Data(0,0,0), Data(0,0,0)) << endl;
		i++;
		it++;
	}
}
//--------------------PRIORITY_QUEUE---------------------------------------

Projeto* Empresa::getMostUrgent()
{
	return _tickets.top().getProjeto();
}

void Empresa::addTicket(Ticket t)
{
	_tickets.push(t);
}


int Empresa::getNextTicket(Utilizador* user)
{
	vector<int> projects = user->getProjetos();
	priority_queue<Ticket> temp = _tickets;
	while(!temp.empty())
	{
		for (unsigned int i = 0; i < projects.size(); i++){
			if (temp.top().getProjeto()->getId() == (unsigned)projects.at(i)){
				if(temp.top().feasible())
				{
					return projects.at(i);
				}
			}
		}
		temp.pop();
	}
	return 0;
}


bool Empresa::removeTicket(Projeto* P)
{	bool removed = false;
	priority_queue<Ticket> temp = _tickets;
	while(!_tickets.empty())
	{
		_tickets.pop();
	}
	while(!temp.empty())
	{
		if(temp.top().getProjeto() == P)
		{	temp.pop();
			removed= true;
			continue;
		}
		_tickets.push(temp.top());
		temp.pop();
	}
	return removed;
}


void Empresa::printClientNumProj()
{
	BSTItrIn <Client> it (_clients);
	int i= 1;
	if(_clients.isEmpty())
	{
		cout<<"\n*Não existem clientes*\n\n";
		return;
	}
	while(!it.isAtEnd())
	{
		cout <<i<<"# - "<<it.retrieve().getNome() <<"	"<< it.retrieve().getProjetos().size();
		i++;
		it.advance();
	}
}

void Empresa::printClientProj(unsigned NIF)
{
	BSTItrIn <Client> it (_clients);
	while(!it.isAtEnd())
	{	if(it.retrieve().getNif() == NIF)
		{
		cout <<"Projetos encomendados por "<< it.retrieve().getNome()<<endl;
		it.retrieve().printProjects();
		return;
		}
		it.advance();
	}

}



void Empresa::updateCurretProj(int id) {
	Projeto* proj = editProj(id);
	for (unsigned int i = 0; i < proj->getUsers().size(); i++) {

		id = getNextTicket(proj->getUsers().at(i));
		proj->getUsers().at(i)->setNextProject(id);
	}
}

void Empresa::removeClientEmp(unsigned int NIF)
{
/*
 * proj->removeAUsers();
	logger->removeProjeto(proj->getId());
	empresa.removeProjeto(proj);*/
	for(unsigned int i = 0; i < _projetos.size(); i++)
	{
		if(_projetos.at(i)->getClient() == NIF)
		{
			_projetos.at(i)->removeAUsers();
			for(unsigned int j = 0; j < _utilizadores.size();j++)
			{
				if(_utilizadores.at(j)->getCargo() == "Gestor")
				{

					removeProjFromGest( _utilizadores.at(j), _projetos.at(i)->getId());
				}
			}
			removeProjeto(_projetos.at(i));
			i--;

		}
	}
}

 void Empresa::removeProjFromGest(Utilizador* user, unsigned int id)
 {
	 for(unsigned int i = 0; i < user->getProjetos().size(); i++)
	 {
		 if((unsigned int)user->getProjetos().at(i) == id)
		 {
			 user->removeProjeto(id);
		 }
	 }

 }
 //--------------------------------------------------------------------------
//--------------------------------------------------------------------------

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


