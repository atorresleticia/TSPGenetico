#pragma once
#include <vector>
#include "Cidade.h"

class lista_cidades
{
public:
	void adiciona_cidade(cidade cidade)
	{
		cidades_.push_back(cidade);
	}

	cidade cidade(int index)
	{
		return cidades_.at(index);
	}

	std::vector<::cidade> get_cidades()
	{
		return cidades_;
	}

private:
	std::vector<::cidade> cidades_;
};
