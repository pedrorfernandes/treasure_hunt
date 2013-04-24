/*
 * displayWithPages.h
 *
 *  Created on: 28 de Dez de 2012
 *  Modified on: 23 de Abr de 2013
 *
 */


/**
 * @file	displayWithPages.h
 * @defgroup displayWithPages
 * @{
 * Contem funcoes template display da informacao de vectores, divindo
 *  por paginas para facilidade de leitura, permitindo a escolha de um objecto
 */
#ifndef DISPLAY_PER_PAGE_H_
#define DISPLAY_PER_PAGE_H_

#include <vector>
#include <iostream>
#define PROMPT "> "

using namespace std;

inline int getVectorChoice() {
	string input = "";
	int number;

	do {
		cout << PROMPT;
		getline(cin, input);
		stringstream stream(input);

		if(input.compare("X") == 0 || input.compare("x") == 0)
			return 0;

		if (stream >> number && number >= 0 && number <= 7)
			break;

		cout << "Please enter a valid choice!" << endl;
	} while(true);

	return number;
}

/**
 * Funcao template para display da informacao de um vector, dividindo-a por paginas.
 *  Permite a escolha de um dos objectos, retornando-o
 *
 * @param v1 referencia para o vector a apresentar
 * @return retorna um apontador para o objecto escolhido pelo utilizador, NULL caso nenhum seja escolhido
 */
template <class T>
T* displayVector(vector<T> &v1) {
	T* obj = NULL;
	bool escolhido = false;
	int numPagina = 0;
	int numPaginaMax;
	if(v1.size()%5 == 0)
		numPaginaMax = v1.size()/5-1;
	else
		numPaginaMax = v1.size()/5;
	while(!escolhido)
	{
		typename vector<T>::iterator it = v1.begin();
		int counter;
		for(counter = 0, it = (v1.begin()+(numPagina*5)); it != v1.end() && counter < 5; it++, counter++)
		{
			cout << (counter+1) << " - " << endl << (*it) << endl;
		}
		cout << "X - Exit\t[1,...,5] - Choose one" << endl;
		if(numPagina > 0)
		{
			cout << "6 - Previous page" << endl;
		}
		if(numPagina < numPaginaMax)
		{
			cout << "7 - Next page" << endl;
		}

		int escolha = getVectorChoice();

		switch(escolha) {
		case 1: case 2: case 3: case 4: case 5:
			if(v1.size() < (unsigned) numPagina*5 + escolha)
				return obj;

			obj = &v1[numPagina*5 + (escolha-1)];
			escolhido = true;
			break;
		case 6:
			if(numPagina > 0)
				numPagina--;
			else
				escolhido = true;
			break;
		case 7:
			if(numPagina < numPaginaMax)
				numPagina++;
			else
				escolhido = true;
			break;
		default:
			escolhido = true;
			break;
		}
	}

	return obj;
}


/**
 * Funcao template para display da informacao de um vector de apontadores, dividindo-a por paginas.
 *  Permite a escolha de um dos objectos, retornando-o
 *
 * @param v1 referencia para o vector de apontadores a apresentar
 * @return retorna o objecto do vector (apontador para outro objecto) escolhido pelo utilizador, NULL caso nenhum seja escolhido
 */
template <class T>
T* displayVector(vector<T*> &v1) {
	T* obj = NULL;
	bool escolhido = false;
	int numPagina = 0;
	int numPaginaMax;
	if(v1.size()%5 == 0)
		numPaginaMax = (int)v1.size()/5-1;
	else
		numPaginaMax = (int)v1.size()/5;
	while(!escolhido)
	{
		typename vector<T*>::iterator it = v1.begin();
		int counter;
		for(counter = 0, it = (v1.begin()+(numPagina*5)); it != v1.end() && counter < 5; it++, counter++)
		{
			cout << (counter+1) << " - " << endl << (**it) << endl;
		}
		cout << "X - Cancel\t[1,...,5] - Choose one" << endl;
		if(numPagina > 0)
		{
			cout << "6 - Previous page" << endl;
		}
		if(numPagina < numPaginaMax)
		{
			cout << "7 - Next page" << endl;
		}

		int escolha = getVectorChoice();

		switch(escolha) {
		case 1: case 2: case 3: case 4: case 5:
			if(v1.size() < (unsigned) numPagina*5 + escolha)
				return obj;

			obj = v1[numPagina*5 + (escolha-1)];
			escolhido = true;
			break;
		case 6:
			if(numPagina > 0)
				numPagina--;
			else
				escolhido = true;
			break;
		case 7:
			if(numPagina < numPaginaMax)
				numPagina++;
			else
				escolhido = true;
			break;
		default:
			escolhido = true;
			break;
		}
	}

	return obj;
}

/**
 * @}
 */
#endif /* DISPLAYWITHPAGES_H_ */
