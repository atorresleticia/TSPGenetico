#include "stdafx.h"
#include "Genetico.h"
#include <unordered_set>

individuo individuo_selecionado_1;
individuo individuo_selecionado_2;
individuo filho;

individuo genetico::torneio(populacao& p)
{
	int tamanhoTorneio = 5;
	populacao aux;

	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	aux.armazena_individuo(p.get_individuo_em(rand() % p.get_tamanho_populacao()));
	
	return aux.get_melhor();
}

individuo genetico::cruzamento(individuo& a, individuo& b)
{
	individuo filho = individuo();
	const int size = a.get_tamanho_rota();
	std::unordered_set<int> cidades;

	const int start = rand() % (size / 2);
	int end = rand() % (size / 2);

	end = size - end;

	for (int i = 0; i < start; i++)
	{
		filho.set_cidade(a.cidade(i));
		cidades.insert(a.cidade(i).id());
	}

	for (int i = end; i < size; i++)
	{
		filho.set_cidade(a.cidade(i));
		cidades.insert(a.cidade(i).id());
	}

	int i = 0;

	while (filho.get_tamanho_rota() != size)
	{
		if (cidades.count(b.cidade(i).id()) == 0)
		{
			filho.set_cidade(b.cidade(i));
		}
		i++;
	}

	return filho;
}

void genetico::mutacao(individuo a) const
{
	const int tamanho = a.get_tamanho_rota();
	for (int i = 0; i < tamanho; i++)
	{
		const float m = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (m <= tx_mutacao_)
		{
			int j = rand() % tamanho;
			const cidade cidade_1 = a.cidade(i);
			const cidade cidade_2 = a.cidade(j);
			a.set_cidade(j, cidade_1);
			a.set_cidade(i, cidade_2);
		}
	}
}

populacao genetico::evolucao(populacao p) const
{
	populacao nova_p = populacao();

	auto j = 0;

	if (elitismo_)
	{
		nova_p.armazena_individuo(p.get_melhor());
		j = 1;
	}

	for (auto i = j; i < p.get_tamanho_populacao(); i++)
	{
		individuo_selecionado_1 = torneio(p);
		individuo_selecionado_2 = torneio(p);
		filho = cruzamento(individuo_selecionado_1, individuo_selecionado_2);

		nova_p.armazena_individuo(filho);
	}
	for (int i = j; i < p.get_tamanho_populacao(); i++)
	{
		mutacao(nova_p.get_individuo_em(i));
	}
	return nova_p;
}
