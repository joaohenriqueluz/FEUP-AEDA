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
    //get dia , mes e ano?
};

class Utilizador
{
protected:
    string _nome;
    Data dataNascimento;
    string _email;
    vector<int> _projetos;

public:
    Utilizador(string nome, int d, int m, int a,string email);
    string getNome();
    Data getDataNascimento();
    string getEmail();
    void setEmail(string email);
    void addProjeto (int id);
    bool removeProjeto (int id);

};

class Coder: public Utilizador
{
protected:
    float _reputacao;
    float _salario;

public:
    Coder(string nome, int d, int m, int a,string email);
    float getReputacao();
    float getSalario();
    void setReputacao(float reputacao);

};



class Gestor: public Utilizador
{
public:
    Gestor(string nome, int d, int m, int a,string email);

};

class Senior:public Coder
{
    int _NIF;
public:
    Senior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF);
    int getNIF();
    void setNIF(int NIF);
    void setSalario(float salario);
};

class Junior :public Coder {
public:
    Junior(string nome, int d, int m, int a,string email, float reputacao, int NIF);
    void setSalario();

};

#endif //PROJ_AEDA_UTILIZADOR_H
