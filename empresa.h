#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include "utilizador.h"
#include "projeto.h"

using namespace std;

class Empresa {
    vector<Projeto *> _projetos;
    vector<Utilizador *> _utilizadores;
public:
    void novoUtilizador();
    void removeUtilizador(Utilizador * UtilizadorARemover);
    void novoProjeto();
    void removeProjeto(Projeto * proj);
    void imprimeSalarios();	
	bool existeUser(string nome, Utilizador* pointer);
	void sortRanking();



template<class T>
void removeObjeto(vector<T> & V, T objeto){
	for(unsigned int i = 0; i < V.size(); i++)
			if(V.at(i)== objeto)
			{
				cout<< "Removido.\n";
				V.erase(V.begin()+i);
			}
}


#endif //PROJ_AEDA_EMPRESA_H
