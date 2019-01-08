#include "ticket.h"

using namespace std;

Ticket::Ticket(Data ECT, Data TTC, int U, Projeto* projeto)
{
	_ECT = ECT;
	_TTC = TTC;
	_urgencia = U;
	_projeto = projeto;
}

Data Ticket::getECT() const
{
	return _ECT;
}

Data Ticket::getTTC()const
{
	return _TTC;
}

int Ticket::getUrgencia() const
{
	return _urgencia;
}

Projeto* Ticket::getProjeto() const
{
	return _projeto;
}

void Ticket::setECT(Data ECT)
{
	_ECT = ECT;
}

void Ticket::setTTC(Data TTC)
{
	_TTC = TTC;
}

void Ticket::setUrgencia(int U)
{
	_urgencia = U;
}

void Ticket::setProjeto(Projeto* projeto)
{
	_projeto = projeto;
}


bool Ticket::operator <(const Ticket& other) const
{
	return _urgencia > other.getUrgencia();
}

bool Ticket::feasible() const
{
	return _ECT <= _TTC;
}
