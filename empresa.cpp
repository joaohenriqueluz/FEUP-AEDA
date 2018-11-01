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



void Empresa::novoUtilizador(){

	Utilizador* novoUtilizador;
	string nome,email;
	int d,m,a;
	cout << "Nome do Utilizador: ";
	cin >> nome;
	cout << "Data de Nascimento(d/m/a): ";
	cin >>d>>m>>a; //VERIFICACAO
	cout <<"Email: ";
	cin >> email;
	string status;
	cout << "Tipo(Gestor/Programador): ";
	cin>> status;
	if(status == "G")
		novoUtilizador = new Gestor(nome,d,m,a,email);
	else
		novoUtilizador = new Coder(nome,d,m,a,email);
	_utilizadores.push_back(novoUtilizador);
}


void Empresa::removeUtilizador(Utilizador * UtilizadorARemover){
	for(unsigned int i = 0; i < _utilizadores.size(); i++)
		if(_utilizadores.at(i)== UtilizadorARemover)
		{
			cout<< "Utilizador removido.\n";
			_utilizadores.erase(_utilizadores.begin()+i);
		}
}


