#pragma once
#include <iostream>
#include "Pista.h"
#include "AdminPista.h"
#include "AdminVehiculo.h"
#include "Vehiculo.h"

using std::string;
using std::runtime_error;


class Logica
{

private:

	AdminPista adminPista;
	AdminVehiculo adminVehiculo;
	Pista pista;
	Vehiculo vehiculo;
	bool pasoMeta;


public:


	Logica()
	{

		pasoMeta = false;
	
	}


	bool moverVehiculo(int fila, int columna, char direccionVehiculo, Pista& pista, AdminVehiculo& adminVehiculo)
	{

		Vehiculo vehiculo = adminVehiculo.getVehiculo();
		
		int filaNueva = vehiculo.getFila();
		int columnaNueva = vehiculo.getColumna();


		switch (direccionVehiculo)
		{

		case 'w':
			filaNueva--;
			break;

		case 'W':
			filaNueva--;
			break;

		case 's':
			filaNueva++;
			break;

		case 'S':
			filaNueva++;
			break;

		case 'a':
			columnaNueva--;
			break;

		case 'A':
			columnaNueva--;
			break;

		case 'd':
			columnaNueva++;
			break;

		case 'D':
			columnaNueva++;
			break;

		default:
			return false;

		}


		if (!pista.posicionValida(filaNueva, columnaNueva))
		{ 

			return false;
		
		}

		if (pista.esPared(filaNueva, columnaNueva))
		{

			return false;
		
		}


		adminVehiculo.nuevaPosicion(filaNueva, columnaNueva);


		return true;

	}


	void verificarLineaMeta(Pista& pista, AdminVehiculo& adminVehiculo)
	{

		Vehiculo vehiculo = adminVehiculo.getVehiculo();

		int filaVehiculo = vehiculo.getFila();
		int columnaVehiculo = vehiculo.getColumna();


		if (pista.esMeta(filaVehiculo, columnaVehiculo))
		{

			pasoMeta = true;

		}

		else if (pasoMeta)
		{

			adminVehiculo.registroVueltas();

			pasoMeta = false;

		}

	}


	bool finCarrera(Pista& pista, AdminVehiculo& adminVehiculo)
	{

		Vehiculo vehiculo = adminVehiculo.getVehiculo();

		
		return pista.carreraTerminada(vehiculo.getVueltasCompletadas());

	}

};

