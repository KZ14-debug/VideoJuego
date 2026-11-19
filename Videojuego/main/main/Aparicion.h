#pragma once
#include <vector>
#include <random>
#include <cstdlib>
#include "Pista.h"

using std::vector;


//esto es solo para que aparezca la tuerca
inline bool buscarCeldaLibre(const Pista& pista, int filaVehiculo, int columnaVehiculo, int distanciaMinima,
	std::mt19937& generador, int& filaSalida, int& columnaSalida)
{

	vector<vector<char>> matriz = pista.getMatriz();

	int alto = (int)matriz.size();

	int ultimaFilaMeta = -1;

	for (int i = 0; i < alto; i++)
	{

		for (int j = 0; j < (int)matriz[i].size(); j++)
		{

			if (matriz[i][j] == Pista::Meta)
			{

				ultimaFilaMeta = i;

			}

		}

	}

	int filaInicio = ultimaFilaMeta + 1;

	if (filaInicio >= alto)
	{

		return false;

	}


	for (int intento = 0; intento < 1000; intento++)
	{

		std::uniform_int_distribution<int> distFila(0, alto - filaInicio - 1);

		int fila = filaInicio + distFila(generador);

		int primerX = -1;
		int segundaX = -1;

		for (int j = 0; j < (int)matriz[fila].size(); j++)
		{

			if (matriz[fila][j] == Pista::Pared)
			{

				if (primerX == -1)
				{

					primerX = j;

				}
				else
				{

					segundaX = j;
					break;

				}

			}

		}

		int rango = segundaX - primerX - 1;

		if (primerX == -1 || segundaX == -1 || rango <= 0)
		{

			continue;

		}

		std::uniform_int_distribution<int> distColumna(0, rango - 1);

		int columna = primerX + 1 + distColumna(generador);

		if (matriz[fila][columna] != Pista::Asfalto)
		{

			continue;

		}

		int distancia = std::abs(fila - filaVehiculo) + std::abs(columna - columnaVehiculo);

		if (distancia < distanciaMinima)
		{

			continue;

		}

		filaSalida = fila;
		columnaSalida = columna;

		return true;

	}

	return false;

}