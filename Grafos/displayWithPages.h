//  displayWithPages.h
//
//  Projeto CAL
//  Parte 1
//
//  Turma 1 Grupo D
//
//  ei11089 - Diogo Santos
//  ei11122 - Pedro Fernandes
//  ei11132 - Daniel Pereira
//


/**
 * @file	displayWithPages.h
 * @defgroup displayWithPages Display with pages
 * @{
 * Contains template functions to display information stored in vectors,
 * dividing each page for easier reading.
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

		if(input.compare("0") == 0)
			return 0;

		if (stream >> number && number >= 0 && number <= 7)
			break;

		cout << "Please enter a valid choice!" << endl;
	} while(true);

	return number;
}

/**
 * Template function to display the information inside a vector, dividing it by pages.
 * Allows the choice of an object inside the vector and returns it.
 *
 * @param v1 The vector the display
 * @return Pointer to the object chosen, NULL if none was chosen.
 */
template <class T>
T* displayVector(vector<T> &v1) {
	T* obj = NULL;
	bool hasChosen = false;
	int pageNumber = 0;
	int maxPageNumber;
	if(v1.size()%5 == 0)
		maxPageNumber = v1.size()/5-1;
	else
		maxPageNumber = v1.size()/5;
	while(!hasChosen)
	{
		typename vector<T>::iterator it = v1.begin();
		int counter;
		for(counter = 0, it = (v1.begin()+(pageNumber*5)); it != v1.end() && counter < 5; it++, counter++)
		{
			cout << (counter+1) << " - " << endl << (*it) << endl;
		}
		cout << "0 - Cancel\n[1,...,5] - Choose option" << endl;
		if(pageNumber > 0)
		{
			cout << "6 - Previous page" << endl;
		}
		if(pageNumber < maxPageNumber)
		{
			cout << "7 - Next page" << endl;
		}

		int choices = getVectorChoice();

		switch(choices) {
		case 1: case 2: case 3: case 4: case 5:
			if(v1.size() < (unsigned) pageNumber*5 + choices)
				return obj;

			obj = &v1[pageNumber*5 + (choices-1)];
			hasChosen = true;
			break;
		case 6:
			if(pageNumber > 0)
				pageNumber--;
			else
				hasChosen = true;
			break;
		case 7:
			if(pageNumber < maxPageNumber)
				pageNumber++;
			else
				hasChosen = true;
			break;
		default:
			hasChosen = true;
			break;
		}
	}

	return obj;
}


/**
 * Template function to display the information inside a vector, dividing it by pages.
 * Allows the choice of an object inside the vector and returns it.
 *
 * @param v1 The vector with pointers to the objects that will be displayed.
 * @return Pointer to the object chosen, NULL if none was chosen.
 */
template <class T>
T* displayVector(vector<T*> &v1) {
	T* obj = NULL;
	bool hasChosen = false;
	int pageNumber = 0;
	int maxPageNumber;
	if(v1.size()%5 == 0)
		maxPageNumber = (int)v1.size()/5-1;
	else
		maxPageNumber = (int)v1.size()/5;
	while(!hasChosen)
	{
		typename vector<T*>::iterator it = v1.begin();
		int counter;
		for(counter = 0, it = (v1.begin()+(pageNumber*5)); it != v1.end() && counter < 5; it++, counter++)
		{
			cout << (counter+1) << " - " << endl << (**it) << endl;
		}
		cout << "0 - Cancel\n[1,...,5] - Choose option" << endl;
		if(pageNumber > 0)
		{
			cout << "6 - Previous page" << endl;
		}
		if(pageNumber < maxPageNumber)
		{
			cout << "7 - Next page" << endl;
		}

		int choices = getVectorChoice();

		switch(choices) {
		case 1: case 2: case 3: case 4: case 5:
			if(v1.size() < (unsigned) pageNumber*5 + choices)
				return obj;

			obj = v1[pageNumber*5 + (choices-1)];
			hasChosen = true;
			break;
		case 6:
			if(pageNumber > 0)
				pageNumber--;
			else
				hasChosen = true;
			break;
		case 7:
			if(pageNumber < maxPageNumber)
				pageNumber++;
			else
				hasChosen = true;
			break;
		default:
			hasChosen = true;
			break;
		}
	}

	return obj;
}

/**
 * @}
 */

#endif /* DISPLAYWITHPAGES_H_ */
