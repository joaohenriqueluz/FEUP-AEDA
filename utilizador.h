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
    int getMes()const {return mes;}
    int getAno()const {return ano;}
    int getDia()const{return dia;}
    bool operator <(const Data & other)const;
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
	Utilizador() {};
    virtual ~Utilizador(){};
    string getNome() const;
    Data getDataNascimento()const;
    string getEmail()const;
    void setEmail(string email);
    void addProjeto (int id);
    bool removeProjeto (int id);
	virtual string getCargo() const { return ""; };
    float getSalario()const {return _salario;}
    int getNIF()const;
    void setNIF(int NIF);
	bool operator <(const Utilizador & other)const;
	//virtual void instucoes(){};

};

class Coder: public Utilizador
{

public:
    Coder(string nome, int d, int m, int a,string email,int NIF);

};



class Gestor: public Utilizador
{
public:
    Gestor(string nome, int d, int m, int a,string email, float salario,int NIF);
    string getCargo(){return "Gestor";}
	void instucoes();

};

class Senior:public Coder
{

public:
    Senior(string nome, int d, int m, int a,string email,float salario,int NIF);
    void setSalario(float salario);
    string getCargo(){return "Programador Senior";}
	void instucoes();

};

class Junior :public Coder {
	int _reputacao;
public:
    Junior(string nome, int d, int m, int a,string email, int reputacao, int NIF);
    void setSalario();
    int getReputacao();
    void setReputacao(int reputacao);
    string getCargo(){return "Programador Junior";}
	void instucoes();

};

#endif //PROJ_AEDA_UTILIZADOR_H
