#include "empresa.h"
using namespace std;

void Empresa::novoProjeto(){
	string nome;
    cout <<"Nome do Projeto? \n";
    cin >> nome; // Como é que implemento uma exception se ele der uma string vazia?
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
