#pragma once
#include <string>

using std::string;


class Registro
{

private:

	string nombre;
	int milisegundos;


public:

	Registro()
	{

		nombre = "";
		milisegundos = 0;

	}


	Registro(const string& nombre, int milisegundos)
	{

		this->nombre = nombre;
		this->milisegundos = milisegundos;

	}


	string getNombre() const
	{

		return nombre;

	}


	int getMilisegundos() const
	{

		return milisegundos;

	}


	double getSegundos() const
	{

		return milisegundos / 1000.0;

	}

};