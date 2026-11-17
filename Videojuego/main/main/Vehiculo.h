#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;


class Vehiculo
{

private:

	int idVehiculo;
	int velocidad;
	int fila;
	int columna;
	char marca;
	int vueltasCompletadas;


public:

	Vehiculo()
	{ 
	
		idVehiculo = 0;
		velocidad = 0;
		fila = 0;
		columna = 0;
		marca = ' ';
		vueltasCompletadas = 0;

	}


	Vehiculo(int idVehiculo, int velocidad, int fila, int columna, char marca)
	{

		this->idVehiculo = idVehiculo;
		this->velocidad = velocidad;
		this->fila = fila;
		this->columna = columna;
		this->marca = marca;
		vueltasCompletadas = 0;
	
	}


	int getIdVehiculo()
	{

		return idVehiculo;
	
	}


	int getVelocidad()
	{

		return velocidad;
	
	}


	int getFila()
	{

		return fila;

	}


	int getColumna()
	{

		return columna;

	}


	char getMarca()
	{

		return marca;

	}


	int getVueltasCompletadas()
	{

		return vueltasCompletadas;

	}


	void setVelocidad(int velocidad)
	{

		this->velocidad = velocidad;
	
	}


	void setPosicion(int fila, int columna)
	{

		this->fila = fila;
		this->columna = columna;
	
	}


	void setVueltasCompletadas(int vueltas)
	{
		
		this->vueltasCompletadas = vueltas;
	
	}


	void vueltaCompletada()
	{

		vueltasCompletadas++;

	}
};

