#pragma once
#include "Vehiculo.h"
#include "Pista.h"
#include <vector>

using std::vector;


class AdminVehiculo
{

private:

	Vehiculo vehiculo;


public:

	AdminVehiculo()
	{
	}


	bool crearVehiculo(int idVehiculo, int velocidad, char marca, const Pista& pista)
	{

		vector<vector<char>> matriz = pista.getMatriz();

		vector<int> lineaMeta;

		int columnaMeta = -1;


		for (int i = 0; i < pista.getAlto(); i++)
		{

			for (int j = 0; j < pista.getAncho(); j++)
			{

				if (matriz[i][j] == Pista::Meta)
				{

					lineaMeta.push_back(i);
					columnaMeta = j;

				}

			}

		}


		if (lineaMeta.empty())
		{

			return false;

		}


		int filaPartida = lineaMeta[lineaMeta.size() / 2];

		int columnaPartida = columnaMeta + 1;


		if (columnaPartida >= pista.getAncho() || matriz[filaPartida][columnaPartida] != Pista::Asfalto)
		{

			return false;

		}


		vehiculo = Vehiculo(idVehiculo, velocidad, filaPartida, columnaPartida, marca);

		return true;

	}


	Vehiculo getVehiculo()
	{

		return vehiculo;

	}


	void nuevaPosicion(int fila, int columna)
	{

		vehiculo.setPosicion(fila, columna);

	}


	void nuevaVelocidad(int velocidad)
	{

		vehiculo.setVelocidad(velocidad);

	}


	void registroVueltas()
	{

		vehiculo.vueltaCompletada();

	}

};

