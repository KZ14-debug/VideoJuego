#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Pista.h"

using std::vector;
using std::string;
using std::ifstream;
using std::cout;


class AdminPista
{

private:

	Pista pista;


public:

	AdminPista() {}


	void cargarPista(const string& nombreArchivo)
	{

		vector <vector<char> > matriz;

		ifstream file(nombreArchivo);

		if (!file.is_open())
		{

			cout << "Error en la apertura de : " << nombreArchivo << std::endl;
			return;

		}


		string line;


		while (getline(file, line))
		{

			matriz.push_back(vector<char>(line.begin(), line.end()));

		}


		size_t anchoMaximo = 0;


		for (int i = 0; i < matriz.size(); i++)
		{

			if (matriz[i].size() > anchoMaximo)
			{

				anchoMaximo = matriz[i].size();
			
			}
		
		}

		
		for (int i = 0; i < matriz.size(); i++)
		{
		
			matriz[i].resize(anchoMaximo, ' ');
		
		}


		file.close();


		pista = Pista(matriz, "Pista", 3);

	}



	Pista getPista()
	{

		return pista;

	}

};
