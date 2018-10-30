#ifndef PROJ_AEDA_UTILIZADOR_H
#define PROJ_AEDA_UTILIZADOR_H

#include <iostream>
#include <string>
#include <vector>
//#include "projeto.h"

using namespace std;

class Data {
    int dia, mes, ano;
public:
    Data();
    Data(int d, int m, int a);
    void setData(int d, int m, int a);
};

class Utilizador
{
protected:
    string _nome;
    Data dataNascimento;
    string _email;

public:
    Utilizador(string nome, int d, int m, int a,string email);
};

class Coder: public Utilizador
{
private:
    float _reputacao;
    vector<int *> _projetos;
    float _salario;

public:
    Coder(string nome, int d, int m, int a,string email, float salario, float reputacao);

};



class Gestor: public Utilizador
{
    vector<int *> _projetos;

public:
    Gestor(string nome, int d, int m, int a,string email);
};

class Senior:public Coder
{
    int _NIF;
public:
    Senior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF);
};

class Junior :public Coder {
public:
    Junior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF);

};

#endif //PROJ_AEDA_UTILIZADOR_H
