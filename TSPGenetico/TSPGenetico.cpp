// TSPGenetico.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "Populacao.h"
#include "Genetico.h"

using namespace std;

int main()
{
	float tamanho_populacao;
	float taxa_mutacao;
	int elitismo;
	int numero_cidades;
	int numero_geracoes;

	cout << "Parametros: numero_geracoes tamanho_populacao numero_cidades taxa_mutacao elitismo (0-sem 1-com)" << endl;
	cin >> numero_geracoes >> tamanho_populacao >> numero_cidades >> taxa_mutacao >> elitismo;

	cout << "PARAMETROS: " << endl;
	cout << "Numero de geracoes: " << numero_geracoes << endl;
	cout << "Tamanho populacao: " << tamanho_populacao << endl;
	cout << "Taxa mutacao: " << taxa_mutacao << endl;
	cout << "Numero de cidades por rota: " << numero_cidades << endl;
	cout << (elitismo == 1 ? "Com elitismo" : "Sem elitismo") << endl;

	unsigned long g_count = 0;
	const auto init = chrono::high_resolution_clock::now();

	populacao pop = populacao(tamanho_populacao, numero_cidades);
	double distancia_inicial = pop.get_melhor().distancia();

	cout << "PRE GENETICOS: " << endl;
	cout << "Tamanho populacao: " << pop.get_tamanho_populacao() << endl;
	cout << "Numero cidades: " << numero_cidades << endl;
	cout << "Distancia inicial: " << distancia_inicial << endl;

	genetico gen = genetico(taxa_mutacao / 100.0, elitismo);

	while (g_count < numero_geracoes)
	{
		pop = gen.evolucao(pop);
		g_count++;
		if (g_count % 1000 == 0)
		{
			cout << "\n" << pop.get_melhor().distancia() << "\b\b\b\b\b\b\b\b\b\b\b\b";
		}
	}

	const auto end = chrono::high_resolution_clock::now();

	double melhoria = distancia_inicial - pop.get_melhor().distancia();

	cout << "RESULTADOS: " << endl;
	cout << "Numero de geracoes: " << g_count << endl;
	cout << "Menor distancia encontrada: " << pop.get_melhor().distancia() << endl;
	cout << "Melhoria de distancia: " << melhoria << endl;
	cout << "Qualidade da Solucao: " << melhoria / distancia_inicial * 100.0 << "% melhor que a distancia inicial" << endl;
	cout << "Duracao: " << chrono::duration_cast<chrono::duration<double>>(end - init).count() << "s" << endl;
	cout << endl;
}

