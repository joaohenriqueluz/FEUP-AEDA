#ifndef PROJ_AEDA_UTILIZADOR_H
#define PROJ_AEDA_UTILIZADOR_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Classe utilizada para guardar data
 * @param dia - dia da data
 * @param mes - mes da data
 * @param ano - ano da data
 */
class Data {
    int dia, mes, ano;
public:
    /**
     * @brief Construtor da class Data, coloca dia, mes e ano iguais a zero
     */
    Data();

    /**
     * @brief Construtor da class Data, coloca dia, mes e ano iguais a d,m e a(respetivamente)
     * @param d - novo valor de dia
     * @param m - novo valor de mes
     * @param a - novo valor de ano
     */
    Data(int d, int m, int a);

    /**
     * @brief Coloca dia, mes e ano iguais a d,m e a
     * @param d - novo valor de dia
     * @param m - novo valor de mes
     * @param a - novo valor de ano
     */
    void setData(int d, int m, int a);

    /**
     * @brief Retorna mes da data
     * @return mes
     */
    int getMes()const {return mes;}

    /**
     * @brief Retorna ano da data
     * @return ano
     */
    int getAno()const {return ano;}
    /**
     * @brief Retorna dia da data
     * @return dia
     */
    int getDia()const{return dia;}

    /**
     * @brief Comprara duas datas
     * @param other - data a comparar
     * @return verdadeiro se a data do objeto for mais antiga do que other
     */
    bool operator <(const Data & other)const;

    /**
     * @brief Comprara duas datas
     * @param other - data a comparar
     * @return verdadeiro se a data do objeto for tao ou mais antiga do que other
     */
	bool operator <=(const Data & other)const;

	/**
	 * @brief Comprara duas datas
	 * @param other - data a comparar
	 * @return verdadeiro se a data do objeto for tao ou menos antiga do que other
	 */
	bool operator >=(const Data & other)const;

	/**
	 * @brief Comprara duas datas
	 * @param other - data a comparar
	 * @return verdadeiro se a data do objeto for tao antiga como other
	 */
	bool operator ==(const Data & other)const;

};






/**
 * @brief Classe do utilizador
 * @param _nome - nome do utilizador
 * @param _cargo - cargo do utilizador
 * @param dataNascimento - data de nascimento do utilizador
 * @param _email - email do utilizador
 * @param _projetos - vetor de projetos do utilizador
 * @param _salario - salario do utilizador
 * @param _NIF - NIF do utilizador
 */
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
    int _currentProj;

public:
    /**
     * @brief Construtor da class Utilizador
     * @param nome - nome do utilizador
     * @param d - dia da data de nascimento do utilizador
     * @param m - mes da data de nascimento do utilizador
     * @param a - ano da data de nascimento do utilizador
     * @param email - email do utilizador
     * @param salario - salario do utilizador
     * @param NIF - NIF do utilizador
     * @param cargo -Cargo do Utilizador (Gestor/Senior/Junior)
     */
    Utilizador(string nome, int d, int m, int a,string email, float salario, int NIF,string cargo);

    /**
     * @brief Construtor da classe sem parametros, colocando a zero o NIF e o salario do utilizador
     */
	Utilizador() {_NIF = 0; _salario = 0; _currentProj = 0;};

	/**
	 * @brief Destrutor da class Utilizador
	 */
    virtual ~Utilizador(){};

    /**
     * @brief Retorna nome do utilizador
     * @return nome do utilizador
     */
    string getNome() const;

    /**
     * @brief Altera o valor nome do utilizador
     * @param nome - novo nome
     */
    void setNome(string nome);

    /**
     * @brief Retorna uma copia da data de nascimento do utilizador
     * @return data de nascimento do utilizador
     */
    Data getDataNascimento()const;

    /**
     * @brief Retorna por referencia a data de nascimento do utilizador
     * @return data de nascimento do utilizador
     */
    Data* getDataNascimentoRef();

    /**
     * @brief Retorna email do utilizador
     * @return email
     */
    string getEmail()const;

    /**
	 * @brief Altera o email do utilizador
	 * @param email - novo email
	 */
    void setEmail(string email);

    /**
     * @brief Altera data de nascimento do utilizador
     * @param d - novo dia de nascimento;
     * @param m - novo mes de nascimento;
     * @param a - novo ano de nascimento;
     */
    void setData(int d, int m, int a);

    /**
	 * @brief Adiciona o id de um novo projeto aos projetos que utilizador faz parte
	 * @param id - id do projeto a adicionar
	 */
    void addProjeto (int id);

    /**
	 * @brief Remove o id do projeto fornecido dos projetos que utilizador faz parte
	 * @param id - id do projeto a remover
	 */
    void removeProjeto (int id);

    /**
	 * @brief Retorna o cargo do utilizador dentro da empresa
	 * @return cargo do utilizador na empresa
	 */
	virtual string getCargo() const { return _cargo; }

	/**
	 * @brief Retorna o salario do utilizador
	 * @return salario
	 */
	float getSalario()const {return _salario;}

	/**
	 * @brief Retorna o NIF do utilizador
	 * @return NIF
	 */
	int getNIF()const;

	/**
	 * @brief Altera o NIF do utilizador
	 * @return novo NIF
	 */
    void setNIF(int NIF);

	/**
	 * @brief Retorna o vetor de projetos dos quais o utilizador pertence
	 * @return projetos a que o utilizador pertence
	 */
	vector<int> getProjetos() { return _projetos; }

	/**
	 * @brief Mostra no ecra as informacoes do utilizador
	 */
	virtual void getInfo();

	/**
	 * @brief Altera o projeto que o utilizador esta a desenvolver atualmente
	 * @return novo id de projeto
	 */
	void setNextProject(int next_proj);

};




/**
 * @brief Classe do gestor
 */
class Gestor: public Utilizador
{
public:
	/**
	 * @brief Construtor da classe Gestor
	 * @param nome - nome do gestor
	 * @param d - dia da data de nascimento do gestor
	 * @param m - mes da data de nascimento do gestor
	 * @param a - ano da data de nascimento do gestor
	 * @param email - email do gestor
	 * @param salario - salario do gestor
	 * @param NIF - NIF do gestor
	 * @param cargo - gestor
	 */
    Gestor(string nome, int d, int m, int a,string email, float salario,int NIF, string cargo);
};

/**
 * @brief Classe do senior
 */
class Senior:public Utilizador
{

public:
	/**
	 * @brief Construtor da classe Senior
	 * @param nome - nome do senior
	 * @param d - dia da data de nascimento do senior
	 * @param m - mes da data de nascimento do senior
	 * @param a - ano da data de nascimento do senior
	 * @param email - email do senior
	 * @param salario - salario do senior
	 * @param NIF - NIF do senior
	 * @param cargo - senior
	 */
	Senior(string nome, int d, int m, int a,string email,float salario,int NIF, string cargo);

	/**
	 * @brief Altera o salario do senior
	 * @param salario - novo salario
	 */
    void setSalario(float salario);

};


/**
 * @brief Classe do junior
 * @param _reputacao - reputacao do junior
 */
class Junior :public Utilizador {
	int _reputacao;
public:
	/**
	 * @brief Construtor da classe Junior
	 * @param nome - nome do junior
	 * @param d - dia da data de nascimento do junior
	 * @param m - mes da data de nascimento do junior
	 * @param a - ano da data de nascimento do junior
	 * @param email - email do junior
	 * @param reputacao - reputacao do junior
	 * @param salario - salario do junior
	 * @param NIF - NIF do junior
	 * @param cargo - junior
	 */
	Junior(string nome, int d, int m, int a,string email, int reputacao, int NIF, string cargo);

	/**
	 * @brief Altera o salario do junior tendo em conta a sua reputacao
	 */
    void setSalario();

    /**
	 * @brief Retorna a reputacao do utilizador
	 * @return reputacao
	 */
    int getReputacao() const;

    /**
	 * @brief Altera a reputacao do junior
	 * @param reputacao - nova reputacao
	 */
    void setReputacao(int reputacao);

    /**
	 * @brief Mostra no ecra as informacoes do junior
	 */
	void getInfo();

};

/**
 * @brief Classe utilizada para lancar uma excecao quando nao e encontrado um utilizador com o nome fornecido
 * @param name - nome do utilizador que nao foi possível encontrar
 */
class NoSuchUser{
	string name;
public:
	/**
	 * @brief Construtor da classe NoSuchUser
	 * @param n - utilizador cujo nome nao existe
	 */
	NoSuchUser(string n){name=n;}

	/**
	 * @ Retorna nome que nao esta atibuido a nenhum utilizador
	 * @return nome
	 */
	string getName() const {return name;}
};


/**
 * @brief Classe utilizada para lancar uma excecao quando e encontrado um utilizador que ja possui o nome fornecido
 * @param name - nome do utilizador que ja existe
 */
class UserRepetido{
	string name;
public:
	/**
	 * @brief Construtor da classe UserRepetido
	 * @param n - utilizador repetido
	 */
	UserRepetido(string n){name=n;}

	/**
	 * @brief Retorna o nome do utilizador repetido
	 * @return nome
	 */
	string getName() const {return name;}
};

/**
 * @brief Classe utilizada para lancar uma excecao quando e encontrado um utilizador que ja possui o NIF fornecido
 * @param nif - NIF do utilizador que ja existe
 */
class NIFRepetido{
	int nif;
public:
	/**
	 * @brief Construtor da classe NIFRepetido
	 * @param n - NIF repetido
	 */
	NIFRepetido(int n){nif=n;}

	/**
	 * @brief Retorna o NIF repetido
	 * @return NIF
	 */
	int getNIF() const {return nif;}
};


/**
 * @brief Classe utilizada para lancar uma excecao quando e encontrado um utilizador que ja possui o email fornecido
 * @param email - email do utilizador que ja existe
 */
class EmailRepetido{
	string _email;
public:
	/**
	 * @brief Construtor da classe EmailRepetido
	 * @param email - email repetido
	 */
	EmailRepetido(string email){_email= email;}

	/**
	 * @brief Retorna o email repetido
	 * @return email
	 */
	string getEmail() const {return _email;}
};

#endif //PROJ_AEDA_UTILIZADOR_H
