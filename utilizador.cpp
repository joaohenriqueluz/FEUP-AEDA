#include "utilizador.h"

using namespace std;

//---------------------------------------------------------------------

Data::Data(){
    dia=0;
    mes=0;
    ano=0;
}

Data::Data(int d, int m, int a){
    dia=d;
    mes=m;
    ano=a;
}

void Data::setData(int d, int m, int a){
    dia=d;
    mes=m;
    ano=a;
}

//---------------------------------------------------------------------
Utilizador::Utilizador(string nome, int d, int m, int a,string email)
{
    _nome = nome;
    dataNascimento.setData(d,m,a);
    _email = email;
}

//---------------------------------------------------------------------

Coder::Coder(string nome, int d, int m, int a,string email, float salario, float reputacao): Utilizador(nome,d,m,a,email){
    _reputacao= reputacao;
    _salario = salario;

}
//---------------------------------------------------------------------

Gestor::Gestor(string nome, int d, int m, int a,string email): Utilizador(nome,d,m,a,email){}

//---------------------------------------------------------------------

Senior::Senior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF):
        Coder(nome,d,m,a,email,salario,reputacao){
    _NIF = NIF;
}

//---------------------------------------------------------------------

Junior::Junior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF):
        Coder(nome,d,m,a,email,salario,reputacao){}



