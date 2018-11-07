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
    /**
     * Construtor da class Data, coloca dia, mes e ano iguais a zero;
     */
    Data();

    /**
     * Construtor da class Data, coloca dia, mes e ano iguais a d,m e a(respetivamente);
     * @param d - novo valor de dia;
     * @param m - novo valor de mes;
     * @param a - novo valor de ano;
     */
    Data(int d, int m, int a);

    /**
     * Coloca dia, mes e ano iguais a d,m e a(respetivamente);
     * @param d - novo valor de dia;
     * @param m - novo valor de mes;
     * @param a - novo valor de ano;
     */
    void setData(int d, int m, int a);

    /**
     * Retorna mes da data;
     * @return mes
     */
    int getMes()const {return mes;}

    /**
     * Retorna ano da data;
     * @return ano
     */
    int getAno()const {return ano;}
    /**
     * Retorna dia da data;
     * @return dia
     */
    int getDia()const{return dia;}

    /**
     * Comprara Data a outra data(other)
     * @param other - outra data;
     * @return verdadeiro se Data for mais antiga do que other
     */
    bool operator <(const Data & other)const;

    /**
     * Comprara Data a outra data(other)
     * @param other - outra data;
     * @return verdadeiro se Data for tao ou mais antiga do que other
     */
	bool operator <=(const Data & other)const;

	/**
	 * Comprara Data a outra data(other)
	 * @param other - outra data;
	 * @return verdadeiro se Data for tao ou menos antiga do que other
	 */
	bool operator >=(const Data & other)const;

	/**
	 *	Comprara Data a outra data(other)
	 * @param other - outra data;
	 * @return verdadeiro se Data for tao antiga como other
	 */
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
    /**
     * Construtor da class Utilizador
     * @param nome -nome do utilizador
     * @param d - dia da data de nascimento do utilizador;
     * @param m - mes da data de nascimento do utilizador;
     * @param a - ano da data de nascimento do utilizador;
     * @param email - email do utilizador;
     * @param salario - salario do utilizador
     * @param NIF - NIF do utilizador;
     * @param cargo -Cargo do Utilizador (Gestor/Senior/Junior)
     */
    Utilizador(string nome, int d, int m, int a,string email, float salario, int NIF,string cargo);
	Utilizador() {_NIF = 0; _salario = 0;};
	/**
	 * Destrutor da class Utilizador
	 */
    virtual ~Utilizador(){};

    /**
     * Retorna nome do utilizador
     * @return _nome
     */
    string getNome() const;

    /**
     * Retorna data de nascimento do utilizador
     * @return dataNascimento
     */
    Data getDataNascimento()const;

    /**
     * Retorna email do utilizador
     * @return _email
     */
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
