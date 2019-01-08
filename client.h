#ifndef PROJ_AEDA_CLIENT_H
#define PROJ_AEDA_CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "projeto.h"

using namespace std;

/**
 * @brief Classe dos clientes
 * @param _nome - nome do cliente
 * @param _email - email do cliente
 * @param _numProj - número total de projetos encomendados pelo cliente
 * @param _contacto - contacto do cliente
 * @param _NIF - nif do cliente
 * @param _projetos - projetos em desenvolvimento encomendados pelo cliente
 */
class Client {
    string _nome;
    string _email;
    int _numeroProj;
    unsigned _contacto;
    unsigned _NIF;
    vector<Projeto*> _projetos;

public:
    /**
     * @brief Construtor da classe Client
     */
    Client(string nome, string email, unsigned numero, unsigned nif);

    /**
     * @brief Retorna o nome do clente
     * @return nome do cliente
     */
    string getNome() const;

    /**
     * @brief Retorna o email do cliente
     * @return email do cliente
     */
    string getEmail() const;

    /**
     * @brief Retorna o contacto do cliente
     * @return contacto do cliente
     */
    unsigned getContacto() const;

    /**
     * @brief Retorna o NIF do cliente
     * @return Nif do cliente
     */
    unsigned getNif() const;

    /**
     * Retorna o número de projetos encomendados pelo cliente
     * @return número de projetos ativos encomendados pelo cliente
     */
    int getNProj() const;

    /**
     * @brief Retorna o vetor de apontadores para projetos ativos encomendados pelo cliente
     * @return vetor de apontadores para projetos ativos encomendados pelo cliente
     */
    vector<Projeto*> getProjetos() const;

    /**
     * @brief Altera o nome do cliente
     * @param nome - novo nome
     */
    void setNome(string nome);

    /**
     * @brief Altera o email do cliente
     * @param email - novo email do cliente
     */
    void setEmail(string email);

    /**
     * @brief Altera o contacto do clente
     * @param numero - novo contacto do clente
     */
    void setContacto(unsigned numero);

    /**
     * @brief Altera o NUF do cliente
     * @param nif - novo NIF do cliente
     */
    void setNIF(unsigned nif);

    /**
     * @brief Incrementa o numero de projetos encomendados pelo cliente
     */
    void incrementaProj();

    /**
     * @brief Adiciona um projetos ao vetor de projetos ativos encomendados pelo cliente
     * @param proj - apontador para o projeto que vai ser adicionado ao vetor de projetos do cliente
     */
    void addProj(Projeto* proj);

    /**
     * @brief Apaga um projeto do vetor de projetos encomendados pelo cliente
     * @param id - ID do projeto a ser apagado
     */
    void removeProj (unsigned id);

    /**
     * @brief Compara dois clentes
     * @param c1 - cliente a ser comparado
     * @return verdadeiro se o numero de projetos encomendados pelo cliente for menor do q o numero de projetos encomendados por c1 e falso caso contrario
     */
    bool operator<(const Client& c1) const;

    /**
     * @brief Compara dois clientes
     * @param c1 - cliente a ser comparado
     * @return cerdadeiro se os ID's do cliente e de c1 forem iguais
     */
    bool operator==(const Client& c1) const;

    /**
     * @brief Imprime todos os projetos ativos associados a esse cliente
     */
    void printProjects();

    /**
     * Altera o numero de projetos encomendados pelo cliente
     */
    void setNProj(int n);

};


#endif //PROJ_AEDA_CLIENT_H
