#ifndef PROJ_AEDA_TICKET_H
#define PROJ_AEDA_TICKET_H

#include <iostream>
#include <string>
#include <vector>
#include "projeto.h"

using namespace std;

/**
 * @brief Class dos tickets
 * @param _ECT - tempo estimado para conclusao
 * @param _TTC - tempo em que o ticket deve estar acabado
 * @param _urgencia - urgencia do projeto com o ticket
 * @param _projeto - projeto associado ao ticket
 */
class Ticket{
private:
	Data _ECT;
	Data _TTC;
	int _urgencia;
	Projeto* _projeto;

public:
	/**
	 * @brief Construtor da class ticket
	 * @param ECT - tempo estimado para conclusao
	 * @param TTC - tempo em que o ticket deve estar acabado
	 * @param U - urgencia do projeto com o ticket
	 * @param projeto - projeto associado ao ticket
	 */
	Ticket(Data ECT,Data TTC, int U, Projeto* projeto);
	 /**
	  * @brief Retorna tempo estimado para conclusao
	  * @return ECT
	  */
	Data getECT() const;

	/**
	 * @brief Retorna tempo em que o ticket deve estar acabado
	 * @return TTC
	 */
	Data getTTC() const;

	/**
	 * @brief Retorna urgencia do projeto com este ticket
	 * @return urgencia
	 */
	int getUrgencia() const;

	/**
	 * @brief Retorna projeto associado ao ticket
	 * @return projeto
	 */
	Projeto* getProjeto() const;

	/**
	 * @brief Altera o valor do ECT
	 * @param ECT - novo valor para o ECT
	 */
	void setECT(Data ECT);

	/**
	 * @brief Altera o valor do TTC
	 * @param TTC -novo valor para o TTC
	 */
	void setTTC(Data TTC);

	/**
	 * @brief Alterna o valor da urgencia do projeto associado ao ticket
	 * @param U - novo valor para a urgencia do projeto associado ao ticket
	 */
	void setUrgencia(int U);

	/**
	 * @brief Altera o projeto associado ao ticket
	 * @param projeto - novo projeto
	 */
	void setProjeto(Projeto* projeto);

	/**
	 * @brief Comprara dois tickets
	 * @param other - ticket a comparar
	 * @return verdadeiro se o projeto do ticket for mais urgente que o projeto de other, senao retorna falso
	 */
	bool operator <(const Ticket& other) const;

	/**
	 * @brief Verifica o projeto pode ser concluido dentro da data limite
	 * @return verdadeiro se ECT for mais recente que TTC, senao retorna
	 */
	bool feasible() const;


};

class NoFeasibleTicket{
public:
	/**
	 * @brief Construtor da classe da excecao
	 */
	NoFeasibleTicket(){ cout << "Não existem projetos exequíveis";}

};

#endif
