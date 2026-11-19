#pragma once
#include "Temporizador.h"
#include "AdminVehiculo.h"



class Efectos
{

private:

	Temporizador temporizadorLentitud;
	Temporizador temporizadorTurbo;

	bool lento;
	bool turbo;

	double duracionLentitud;
	double duracionTurbo;

	int velocidadBase;


public:

	Efectos()
	{

		lento = false;
		turbo = false;
		duracionLentitud = 0;
		duracionTurbo = 0;
		velocidadBase = 2;

	}


	void iniciar(int velocidadBase)
	{

		this->velocidadBase = velocidadBase;
		lento = false;
		turbo = false;

	}


	// Devuelve false si ya estaba lento (el choque se ignora)
	bool aplicarLentitud(double segundos)
	{

		if (lento)
		{

			return false;

		}

		lento = true;
		duracionLentitud = segundos;
		temporizadorLentitud.iniciar();

		return true;

	}


	// Si ya habia turbo, reinicia el tiempo
	void aplicarTurbo(double segundos)
	{

		turbo = true;
		duracionTurbo = segundos;
		temporizadorTurbo.iniciar();

	}


	// Llamar en cada tick: vence los efectos y deja la velocidad del vehiculo correcta
	void actualizar(AdminVehiculo& adminVehiculo)
	{

		if (lento && temporizadorLentitud.getTiempo() >= duracionLentitud)
		{

			lento = false;

		}

		if (turbo && temporizadorTurbo.getTiempo() >= duracionTurbo)
		{

			turbo = false;

		}


		int velocidad = velocidadBase;

		if (turbo)
		{

			velocidad = velocidad * 2;

		}

		if (lento)
		{

			velocidad = velocidad / 2;

		}

		if (velocidad < 1)
		{

			velocidad = 1;

		}


		if (adminVehiculo.getVehiculo().getVelocidad() != velocidad)
		{

			adminVehiculo.nuevaVelocidad(velocidad);

		}

	}


	bool estaLento() const
	{

		return lento;

	}


	bool estaTurbo() const
	{

		return turbo;

	}


	double restanteLentitud()
	{

		if (!lento)
		{

			return 0;

		}

		double restante = duracionLentitud - temporizadorLentitud.getTiempo();

		return restante > 0 ? restante : 0;

	}


	double restanteTurbo()
	{

		if (!turbo)
		{

			return 0;

		}

		double restante = duracionTurbo - temporizadorTurbo.getTiempo();

		return restante > 0 ? restante : 0;

	}

};