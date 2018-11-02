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
    int getMes(){return mes;}
    int getAno(){return ano;}
    int getDia(){return dia;}
    bool operator <(Data & other);
};



class Utilizador
{
protected:
    string _nome;
    Data dataNascimento;
    string _email;
    vector<int> _projetos;
    float _salario;
    int _NIF;

public:
    Utilizador(string nome, int d, int m, int a,string email, float salario, int NIF);
    virtual ~Utilizador(){};
    string getNome();
    Data getDataNascimento();
    string getEmail();
    void setEmail(string email);
    void addProjeto (int id);
    bool removeProjeto (int id);
    virtual string getCargo()=0;
    float getSalario(){return _salario;}
    int getNIF();
    void setNIF(int NIF);

};

class Coder: public Utilizador
{

public:
    Coder(string nome, int d, int m, int a,string email);

};



class Gestor: public Utilizador
{
public:
    Gestor(string nome, int d, int m, int a,string email, float salario);
    string getCargo(){return "Gestor";}

};

class Senior:public Coder
{

public:
    Senior(string nome, int d, int m, int a,string email,float salario,int NIF);
    void setSalario(float salario);
    string getCargo(){return "Programador Senior";}
};

class Junior :public Coder {
	int _reputacao;
public:
    Junior(string nome, int d, int m, int a,string email, int reputacao, int NIF);
    void setSalario();
    float getReputacao();
    void setReputacao(int reputacao);
    string getCargo(){return "Programador Junior";}
};

#endif //PROJ_AEDA_UTILIZADOR_H
