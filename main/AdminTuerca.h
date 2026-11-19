#pragma once
#include <random>
#include "Tuerca.h"
#include "Pista.h"
#include "Aparicion.h"
#include "Temporizador.h"


class AdminTuerca
{

private:

	Tuerca tuerca;
	Temporizador temporizadorReaparicion;
	std::mt19937 generador;
	double segundosReaparicion;
	int distanciaMinima;


public:

	AdminTuerca()
	{

		std::random_device rd;
		generador.seed(rd());

		segundosReaparicion = 6.0;
		distanciaMinima = 10;

	}


	bool crearTuerca(char marca, const Pista& pista, int filaVehiculo, int columnaVehiculo)
	{

		int fila;
		int columna;

		if (!buscarCeldaLibre(pista, filaVehiculo, columnaVehiculo, distanciaMinima, generador, fila, columna))
		{

			return false;

		}

		tuerca = Tuerca(fila, columna, marca);

		return true;

	}


	Tuerca getTuerca()
	{

		return tuerca;

	}


	bool recoger(int fila, int columna)
	{

		if (tuerca.estaActiva() && tuerca.getFila() == fila && tuerca.getColumna() == columna)
		{

			tuerca.setActiva(false);
			temporizadorReaparicion.iniciar();

			return true;

		}

		return false;

	}



	void actualizar(const Pista& pista, int filaVehiculo, int columnaVehiculo)
	{

		if (tuerca.estaActiva())
		{

			return;

		}

		if (temporizadorReaparicion.getTiempo() < segundosReaparicion)
		{

			return;

		}

		int fila;
		int columna;

		if (buscarCeldaLibre(pista, filaVehiculo, columnaVehiculo, distanciaMinima, generador, fila, columna))
		{

			tuerca.setPosicion(fila, columna);
			tuerca.setActiva(true);

		}

	}


	void colocar(int fila, int columna)
	{

		tuerca.setPosicion(fila, columna);
		tuerca.setActiva(true);

	}

};