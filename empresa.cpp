#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "empresa.h"

using namespace std;

void Empresa::novoProjeto(){
	string nome;
    cout <<"Nome do Projeto? \n";
    cin >> nome; // Como � que implemento uma exception se ele der uma string vazia?
    Projeto* novoProjeto= new Projeto(nome);
    _projetos.push_back(novoProjeto);
    cout << "Projeto " << nome << "criado com ID " << novoProjeto->getId() << endl;

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

	Utilizador* novoUtilizador;
	string nome,email,status;
	int d,m,a,NIF,reput;

	cout << "Nome do Utilizador: ";
	cin >> nome;
	cout << "Data de Nascimento(d/m/a): ";
	cin >>d>>m>>a; //VERIFICACAO
	cout <<"Email: ";
	cin >> email;
	cout << "Digite NIF: ";
	cin >> NIF;
	cout << "Tipo(Gestor(G)/Programador(S/J)): ";
	cin>> status;
	if(status == "G")
		novoUtilizador = new Gestor(nome,d,m,a,email,2500,NIF);
	else if(status == "S"){
		
		novoUtilizador = new Senior(nome,d,m,a,email,1000,NIF);//string nome, int d, int m, int a,string email,float salario,int NIF
	}
		else if(status == "J")
		{
		cout << "Reputacao: ";
		cin >> reput;
		novoUtilizador = new Junior(nome,d,m,a,email,reput,NIF);
		}

	_utilizadores.push_back(novoUtilizador);
}

void Empresa::removeUtilizador(Utilizador * utilizador)
{
	removeObjeto<Utilizador*>(_utilizadores, utilizador);
}
/*
void Empresa::removeUtilizador(Utilizador * UtilizadorARemover){

	for(unsigned int i = 0; i < _utilizadores.size(); i++)
		if(_utilizadores.at(i)== UtilizadorARemover)
		{
			cout<< "Utilizador removido.\n";
			_utilizadores.erase(_utilizadores.begin()+i);
		}
}

*/

void Empresa::imprimeSalarios(){

	if(_utilizadores.size()== 0)
		{cout << "Nao existem utilizadores.\n";
		return;}
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

bool Empresa::existeUser(string nome, Utilizador* pointer)
{
	
	for (unsigned int i = 0; i < _utilizadores.size(); i++)
	{
		if (_utilizadores.at(i)->getNome() == nome)
		{
			pointer = _utilizadores.at(i);
			return true;
		}
	}
	return false;
}

int Empresa::getVolume(string nome) const {
    int volume = 0;
    for(unsigned int i = 0; i < _projetos.size(); i++){
        volume += _projetos.at(i)->getVolume(nome);
    }
    return volume;
}

int Empresa::getFreq(string nome) const {
    int volume = 0;
    for(unsigned int i = 0; i < _projetos.size(); i++){
        volume += _projetos.at(i)->getFreq(nome);
    }
    return volume;
}

void Empresa::sortRanking() {
    for (unsigned int j = _projetos.size() - 1; j > 0; j--)
    {
        bool troca = false;
        for (unsigned int i = 0; i < j; i++)
            if (getVolume(_utilizadores.at(i+1)->getNome()) > getVolume(_utilizadores.at(i)->getNome()))
            {
                std::swap(_utilizadores.at(i), _utilizadores.at(i + 1));
                troca = true;
            }
            else if (getVolume(_utilizadores.at(i + 1)->getNome()) == getVolume(_utilizadores.at(i)->getNome()))
            {
                if (getFreq(_utilizadores.at(i + 1)->getNome()) > getFreq(_utilizadores.at(i)->getNome()))
                {
                    std::swap(_utilizadores.at(i), _utilizadores.at(i + 1));
                    troca = true;
                }
            }
        if (!troca) break;
    }


}

void Empresa::readUsers(){
	ifstream file;
	file.open("utilizadores.txt");
	string nome, rank, email, data, n, ids;
	char ch, b;
    int d,m,a,id,nif;
    vector <int> dataV;
	vector <int> projId;

	if (file.is_open()){
	    while (file.good()) {
            getline(file, nome);
            cout << nome << endl;
            getline(file, rank);
            cout << rank << endl;
            file >> d >> b >> m >> b >> a;
            cout << d << b << m << b << a << endl;
            getline(file,n);
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
            getline(file,n);
            cout << n;
            getline(file,n);
            cout << n;
        }
		file.close();

	} else{
		cout << "File not found" << endl;
	}
}

void Empresa::readProjetos() {
    ifstream file;
    file.open("projetos.txt");
    string tipo, nome, pass, temp;
    vector <int> usersID;
    vector <int> commitID;
    if (file.is_open()){
        while (file.good()){
            getline(file,tipo);
            cout << tipo << endl;
            getline(file,nome);
            cout << nome << endl;
            getline(file,pass);
            cout << pass << endl;
            getline(file,temp);
            cout << temp << endl;
            while (1){ //ciclo para ler os usersID de um projeto
                getline(file, temp);
                if (temp == "endU") break;
                int id = stoi(temp);
                usersID.push_back(id);
            }
            for (int i = 0; i < usersID.size(); ++i) {
                cout << usersID.at(i) << endl;
            }
            getline(file,temp);
            cout << temp << endl;
            getline(file,)
            while (1){ //ciclo para ler os ID dos commits de um projeto
                getline(file, temp);
                if (temp == "endC") break;
                int id = stoi(temp);
                usersID.push_back(id);
            }

    }
}
