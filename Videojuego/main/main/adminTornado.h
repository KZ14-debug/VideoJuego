#pragma once
#include "Tornado.h"
#include "Pista.h"
#include <vector>
#include <random>
#include <cstdlib>

using std::vector;


class AdminTornado
{

private:

	Tornado tornado;
	std::mt19937 generador;   // se siembra UNA sola vez, al construir el AdminTornado


	
	int aleatorio(int limite)
	{

		std::uniform_int_distribution<int> dist(0, limite - 1);

		return dist(generador);

	}


public:

	AdminTornado()
	{

		std::random_device rd;
		generador.seed(rd());

	}


	bool crearTornado(int idTornado, int velocidad, char marca, const Pista& pista, int filaVehiculo, int columnaVehiculo, int distanciaMinima = 15)
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

			int fila = filaInicio + aleatorio(alto - filaInicio);

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

			int columna = primerX + 1 + aleatorio(rango);

			if (matriz[fila][columna] != Pista::Asfalto)
			{

				continue;

			}

			int distancia = std::abs(fila - filaVehiculo) + std::abs(columna - columnaVehiculo);

			if (distancia < distanciaMinima)
			{

				continue;

			}

			tornado = Tornado(idTornado, velocidad, fila, columna, marca);

			return true;

		}

		return false;

	}


	Tornado getTornado()
	{

		return tornado;

	}


	
	bool mover(Pista& pista)
	{

		const int dFila[4] = { -1, 1, 0, 0 };
		const int dColumna[4] = { 0, 0, -1, 1 };

		vector<int> direccionesValidas;

		for (int d = 0; d < 4; d++)
		{

			int nuevaFila = tornado.getFila() + dFila[d];
			int nuevaColumna = tornado.getColumna() + dColumna[d];

			if (pista.posicionValida(nuevaFila, nuevaColumna) && !pista.esPared(nuevaFila, nuevaColumna))
			{

				direccionesValidas.push_back(d);

			}

		}

		if (direccionesValidas.empty())
		{

			return false;

		}

		int d = direccionesValidas[aleatorio((int)direccionesValidas.size())];

		tornado.mover(tornado.getFila() + dFila[d], tornado.getColumna() + dColumna[d]);

		return true;

	}


	/*void nuevaVelocidad(int velocidad)
	{

		tornado.setVelocidad(velocidad);

	}
	*/

};
