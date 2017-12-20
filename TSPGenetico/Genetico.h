#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#pragma once
#include "populacao.h"

class genetico
{
public:
	
	genetico(const float tx_mutacao, const bool elitismo)
		: tx_mutacao_(tx_mutacao),
		elitismo_(elitismo)
	{
	}

	genetico() = default;
	~genetico() = default;

	static individuo torneio(populacao& p);
	static individuo cruzamento(individuo& a, individuo& b);
	void mutacao(individuo a) const;
	populacao evolucao(populacao p) const;

private:
	float tx_mutacao_;
	float tx_cruzamento_;
	bool elitismo_;
	std::vector<individuo> rotas_;
};

#endif
