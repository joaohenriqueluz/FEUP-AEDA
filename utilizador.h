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
	bool operator <=(const Data & other)const;
	bool operator >=(const Data & other)const;
	bool operator ==(const Data & other)const;

};



class Utilizador
{
protected:
    string _nome;
	string _cargo;
    Data dataNascimento;
    string _email;
    vector<int> _projetos;
    float _salario;
    int _NIF;

public:
    Utilizador(string nome, int d, int m, int a,string email, float salario, int NIF,string cargo);
	Utilizador() {_NIF = 0; _salario = 0;};
    virtual ~Utilizador(){};
    string getNome() const;
    Data getDataNascimento()const;
    string getEmail()const;
    void setEmail(string email);
    void addProjeto (int id);
    bool removeProjeto (int id);
	virtual string getCargo() const { return _cargo; }
    float getSalario()const {return _salario;}
    int getNIF()const;
    void setNIF(int NIF);
	void imprimeProjetos();
	vector<int> getProjetos() { return _projetos; }
	//bool operator <(const Utilizador & other)const;
	//virtual void instucoes(){};
	void getInfo();
	virtual void setReputacao(int reputacao){};
	virtual int getReputacao() const { return 0; }

};

class Coder: public Utilizador
{
public:
    Coder(string nome, int d, int m, int a,string email,int NIF, string cargo);

};



class Gestor: public Utilizador
{
public:
    Gestor(string nome, int d, int m, int a,string email, float salario,int NIF, string cargo);
	//void instrucoes();
	

};

class Senior:public Coder
{

public:
    Senior(string nome, int d, int m, int a,string email,float salario,int NIF, string cargo);
    void setSalario(float salario);
	//void instucoes();

};

class Junior :public Coder {
	int _reputacao;
public:
    Junior(string nome, int d, int m, int a,string email, int reputacao, int NIF, string cargo);
    void setSalario();
    int getReputacao() const;
    void setReputacao(int reputacao);
	//void instucoes();

};

#endif //PROJ_AEDA_UTILIZADOR_H
