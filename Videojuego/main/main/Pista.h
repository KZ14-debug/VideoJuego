#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::string;


class Pista
{


private:

	int totalVueltas;



public:

	vector<vector<char>> matriz;
	string codigo;
	int ancho;
	int alto;

	static const char Meta = '#';
	static const char Pared = 'x';
	static const char Asfalto = ' ';



	Pista()
	{

		totalVueltas = 0;
		ancho = 0;
		alto = 0;

	}



	Pista(vector<vector<char>> matriz, string codigo, int totalVueltas)
	{

		this->codigo = codigo;
		this->matriz = matriz;
		this->totalVueltas = totalVueltas;
		alto = matriz.size();
		ancho = (alto > 0) ? matriz[0].size() : 0;

	}


	string getCodigo()
	{
		return codigo;
	}


	int getAncho()
	{
		return ancho;
	}


	int getAlto()
	{
		return alto;
	}


	int getVueltas()
	{
		return totalVueltas;
	}


	vector<vector<char>> getMatriz()
	{
		return matriz;
	}


	bool carreraTerminada(int vueltasCompletadas)
	{

		return vueltasCompletadas >= totalVueltas;
	
	}


	bool esMeta(int fila, int columna)
	{

		return (fila >= 0 && fila < alto && columna >= 0 && columna < ancho && matriz[fila][columna] == Meta);

	}


	bool posicionValida(int fila, int columna)
	{
		return fila >= 0 && fila < alto && columna >= 0 && columna < ancho;

	}


	bool esPared(int fila, int columna)
	{

		if (!posicionValida(fila, columna))
		{

			return false;
		
		}

		return matriz[fila][columna] == Pared;

	}


	bool esAsfalto(int fila, int columna)
	{

		if (fila < 0 || fila >= alto || columna < 0 || columna >= ancho)
		{

			return false;

		}

		return matriz[fila][columna] != Pared;

	}


	char ObtenerPosicion(int fila, int columna)
	{

		if (!posicionValida(fila, columna))
		{

			return '\0';

		}

		return matriz[fila][columna];
	}


	char actualizarPosicion(int fila, int columna, char marca)
	{

		if (!posicionValida(fila, columna))
		{

			return;

		}

		
		matriz[fila][columna] = marca;
	
	}




	void imprimirPista()
	{

		for (int i = 0; i < alto; i++)
		{

			for (int j = 0; j < ancho; j++)
			{

				cout << matriz[i][j];
			
			}
			cout << endl;

		}

	}
};