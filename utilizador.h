#ifndef utilizador
#define utilizador
#include <iostream>
#include <string>
#include <vector>



/*TO DO LIST:

-construtores
-getters
-Adicionar/apagar/modificar objetos
*/

using namespace std;

typedef struct data {
	int dia, mes, ano;
}*dataD; 

class utilizador {
protected:
	string _nome;
	dataD dataNascimento;
	string email;

public:

};

class coders{
	int reputacao;
	vector<projeto *> projetos;
	int salario;
};
class gestor:public utilizador{
	vector<projeto *> projetos;
};

class senior : public utilizador, public coders{
	int NIF;
};

class junior : public utilizador, public coders {

};






#endif // !utilizador

