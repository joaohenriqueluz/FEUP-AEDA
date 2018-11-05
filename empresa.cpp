#include "empresa.h"
#include <fstream>

using namespace std;

int Empresa::novoProjeto(){
	string nome;
    cout <<"Nome do Projeto? \n";
    cin >> nome; // Como � que implemento uma exception se ele der uma string vazia?
    Projeto* novoProjeto= new Projeto(nome);
    _projetos.push_back(novoProjeto);
    cout << "Projeto " << nome << "criado com ID " << novoProjeto->getId() << endl;
	return novoProjeto->getId();
}

void Empresa::removeProjeto(Projeto* proj){
	removeObjeto<Projeto*>(_projetos, proj);
}
/*
void Empresa::removeProjeto(Projeto * projetoARemover){
	for(unsigned int i = 0; i < _projetos.size(); i++)
	{
		if(_projetos.at(i) == projetoARemover)
		{
			cout << "Projeto " << projetoARemover->getNome() <<" removido. \n";
			_projetos.erase(_projetos.begin() + i);
			return;
		}
	}
}
*/


void Empresa::novoUtilizador(){

	Gestor* gestor;
	Senior* senior;
	Junior* junior;
	string nome,email;
	int d,m,a,NIF,reput;

	cout << "Nome do Utilizador: ";
	cin >> nome;
	cout << "Data de Nascimento(d/m/a): ";
	cin >>d>>m>>a; //VERIFICACAO
	cout <<"Email: ";
	cin >> email;
	string status;
	cout << "Digite NIF: ";
	cin >> NIF;
	cout << "Tipo(Gestor(G)/Programador(S/J)): ";
	cin>> status;
	if (status == "G")
	{
		gestor = new Gestor(nome, d, m, a, email, 2500, NIF,"Gestor");
		cout << "\nGestor criado!\n";
		_utilizadores.push_back(gestor);
	}
	else if(status == "S"){
		
		senior = new Senior(nome,d,m,a,email,1000,NIF,"Senior");
		cout << "\nSenior criado!\n";	//string nome, int d, int m, int a,string email,float salario,int NIF
		_utilizadores.push_back(senior);

	}
		else if(status == "J")
		{
		cout << "Reputacao: ";
		cin >> reput;
		junior = new Junior(nome,d,m,a,email,reput,NIF,"Junior");
		cout << "\nJunior criado!\n";
		_utilizadores.push_back(junior);
		}

	
}

void Empresa::removeUtilizador(Utilizador * utilizador)
{
	removeObjeto<Utilizador*>(_utilizadores, utilizador);
}

void Empresa::imprimeSalarios(){
	/*
	if(_utilizadores.size() == 0)
		{cout << "Nao existem utilizadores.\n";
		return;}*/
 float Soma=0;
 for(unsigned int i =0; i < _utilizadores.size();i++)
 {
	 cout <<"Nome: "<< _utilizadores.at(i)->getNome()
		  << " Cargo: " << _utilizadores.at(i)->getCargo()
		  << " Salario: "<< _utilizadores.at(i)->getSalario()<< endl;
	 Soma+= _utilizadores.at(i)->getSalario();
 }
 cout <<"Soma total dos salarios: "<<Soma<<endl;
}

Utilizador* Empresa::existeUser(string nome, bool &existe)
{
	
	for (unsigned int i = 0; i < _utilizadores.size(); i++)
	{
		if (_utilizadores.at(i)->getNome() == nome)
		{
			existe= true;
			return _utilizadores.at(i);

		}
	}
	existe = false;
}

Utilizador* Empresa::existeUser(string nome)
{

	for (unsigned int i = 0; i < _utilizadores.size(); i++)
	{
		if (_utilizadores.at(i)->getNome() == nome)
		{
			return _utilizadores.at(i);

		}
	}
	
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

void Empresa::imprimeUser()
{
	for (unsigned int i = 0; i < _utilizadores.size(); i++)
	{
		cout <<i+1<<"# "<< _utilizadores.at(i)->getNome()<<"     Cargo: "<<_utilizadores.at(i)->getCargo()<<endl;
	}
}

void Empresa::imprimeCoders()
{
	for (unsigned int i = 0; i < _utilizadores.size(); i++)
	{
		if (_utilizadores.at(i)->getCargo() == "Gestor")
			continue;
		cout << i + 1 << "# " << _utilizadores.at(i)->getNome() << "     Cargo: " << _utilizadores.at(i)->getCargo() << endl;
	}
}
	

void Empresa::imprimeProjetos()
{
	for (unsigned int i = 0; i < _projetos.size(); i++)
	{
		cout << _projetos.at(i)->getNome() << " ID: " << _projetos.at(i)->getId()<<endl;
	}
}



void Empresa::readUsers() {
	Gestor* _gestor;
	Junior* _junior;
	Senior* _senior;

	ifstream file;
	file.open("C:\\Users\\joaoh\\Desktop\\utilizadores.txt");
	string nome, rank, email, data, n, ids, reputacao, money;
	char ch, b;
	int d, m, a, id, nif, rep, salario;
	vector <int> dataV;
	vector <int> projId;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, nome);
			cout << nome << endl;
			getline(file, rank);
			cout << rank << endl;
			if (rank == "J") {
				getline(file, reputacao);
				rep = stoi(reputacao);
			}
			file >> d >> b >> m >> b >> a;
			cout << d << b << m << b << a << endl;
			getline(file, n);
			cout << n;
			getline(file, email);
			cout << email << endl;
			projId.clear();
			while (1) {
				getline(file, ids);
				if (ids == "end") break;
				int id = stoi(ids);
				projId.push_back(id);
			}
			for (int i = 0; i < projId.size(); ++i) {
				cout << projId.at(i) << endl;
			}
			file >> nif;
			cout << nif << endl;
			getline(file, n);
			cout << n;
			if (rank != "J") {
				getline(file, money);
				salario = stoi(money);
			}
			getline(file, n);
			cout << n;



			if (rank == "G")
			{
				_gestor = new Gestor(nome, d, m, a, email, salario, nif,"Gestor");
				_utilizadores.push_back(_gestor);
			}
			if (rank == "S")
			{
				_senior = new Senior(nome, d, m, a, email, salario, nif,"Senior");
				_utilizadores.push_back(_senior);
			}

			if (rank == "J")
			{
				_junior = new Junior(nome, d, m, a, email, rep,nif,"Junior");
				_junior->setSalario();
				_utilizadores.push_back(_junior);
			}
		
		}
		file.close();

	}
	else {
		cout << "File not found" << endl;
	}
}


void Empresa::converteJunior(Utilizador * junior)
{
	if (junior->getReputacao() > 9999)
	{
		string nome = junior->getNome();
		int dia = junior->getDataNascimento().getDia();
		int mes = junior->getDataNascimento().getMes();
		int ano = junior->getDataNascimento().getAno();
		int NIF = junior->getNIF();
		string email = junior->getEmail();
		Utilizador* novoSenior = new Senior(nome, dia, mes, ano, email, 1000, NIF, "Senior");
		removeUtilizador(junior);
		getUsers().push_back(novoSenior);

	}
}