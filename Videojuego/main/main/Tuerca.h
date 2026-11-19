#pragma once


class Tuerca
{

private:

	int fila;
	int columna;
	char marca;
	bool activa;


public:

	Tuerca()
	{

		fila = 0;
		columna = 0;
		marca = '*';
		activa = false;

	}


	Tuerca(int fila, int columna, char marca)
	{

		this->fila = fila;
		this->columna = columna;
		this->marca = marca;
		activa = true;

	}


	int getFila() const
	{

		return fila;

	}


	int getColumna() const
	{

		return columna;

	}


	char getMarca() const
	{

		return marca;

	}


	bool estaActiva() const
	{

		return activa;

	}


	void setActiva(bool activa)
	{

		this->activa = activa;

	}


	void setPosicion(int fila, int columna)
	{

		this->fila = fila;
		this->columna = columna;

	}

};