#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <conio.h>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX          // evita que windows.h rompa std::numeric_limits<...>::max()
#endif
#include <windows.h>
#endif

#include "Pista.h"
#include "AdminPista.h"
#include "AdminVehiculo.h"
#include "AdminTornado.h"
#include "Logica.h"
#include "Temporizador.h"

using std::cout;
using std::string;
using std::vector;


// ---------------- OPCIONES DE PRUEBA (cambielas segun lo que necesite) ----------------
const int  TICK_MS = 500;        // duracion de cada tick (mas grande = mas lento)
const bool MODO_PASO = true;    // true: el juego avanza UN tick por cada tecla (ideal para depurar)
const bool GUARDAR_TRAZA = true; // true: escribe traza.txt con una linea por tick
// ---------------------------------------------------------------------------------------


// Mueve el cursor al inicio de la consola SIN borrar (evita el parpadeo de system("cls"))
void cursorAlInicio()
{

    #ifdef _WIN32
        COORD origen = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), origen);
    #else
        cout << "\033[H";
    #endif

}


// Arma TODO el cuadro en un string y lo imprime de una sola vez.
void dibujar(Pista& pista, Vehiculo vehiculo, Tornado tornado, double tiempo, bool colision, int tick)
{

	vector<vector<char>> matriz = pista.getMatriz();   // copia: la pista original no se toca

	matriz[tornado.getFila()][tornado.getColumna()] = tornado.getMarca();
	matriz[vehiculo.getFila()][vehiculo.getColumna()] = vehiculo.getMarca();


	string cuadro;

	for (int i = 0; i < (int)matriz.size(); i++)
	{

		cuadro += string(matriz[i].begin(), matriz[i].end());
		cuadro += '\n';

	}

	cuadro += "Tiempo: " + std::to_string(tiempo).substr(0, 5) + " s  |  Vueltas: "
		+ std::to_string(vehiculo.getVueltasCompletadas()) + "/" + std::to_string(pista.getVueltas())
		+ "  |  Tick: " + std::to_string(tick) + "                    \n";

	cuadro += "Auto (" + std::to_string(vehiculo.getFila()) + "," + std::to_string(vehiculo.getColumna()) + ")  "
		+ "Tornado (" + std::to_string(tornado.getFila()) + "," + std::to_string(tornado.getColumna()) + ")        \n";

	cuadro += colision ? "*** COLISION CON EL TORNADO ***      \n" : "                                    \n";

	cuadro += "[w a s d] mover   [q] salir                      \n";


	cursorAlInicio();

	cout << cuadro << std::flush;

}


void partidaPrueba()
{

	AdminPista adminPista;
	adminPista.cargarPista("Pista.txt");

	Pista pista = adminPista.getPista();


	Logica logica;
	Temporizador temporizador;


	AdminVehiculo adminVehiculo;

	if (!adminVehiculo.crearVehiculo(1, 1, 'A', pista))
	{

		cout << "No se pudo crear el vehiculo (revise la meta en Pista.txt)." << std::endl;
		return;

	}


	int filaVehiculo = adminVehiculo.getVehiculo().getFila();
	int columnaVehiculo = adminVehiculo.getVehiculo().getColumna();


	// velocidad del tornado = cada cuantos ticks se mueve
	AdminTornado adminTornado;

	if (!adminTornado.crearTornado(1, 3, 'T', pista, filaVehiculo, columnaVehiculo, 15))
	{

		cout << "No se pudo crear el tornado." << std::endl;
		return;

	}


	std::ofstream traza;

	if (GUARDAR_TRAZA)
	{

		traza.open("traza.txt");
		traza << "tick;tecla;auto_fila;auto_col;tornado_fila;tornado_col;vueltas;colision\n";

	}


#ifdef _WIN32
	system("cls");   // una sola vez, al empezar
#else
	cout << "\033[2J";
#endif


	int tick = 0;

	temporizador.iniciar();


	while (!logica.finCarrera(pista, adminVehiculo))
	{

		// 1) Entrada
		char tecla = ' ';

		if (MODO_PASO)
		{

			tecla = _getch();   // espera una tecla por cada tick (cualquier tecla que no sea wasd solo avanza el tick)

		}
		else if (_kbhit())
		{

			tecla = _getch();

		}

		if (tecla == 'q' || tecla == 'Q')
		{

			break;

		}


		// 2) Mover auto
		logica.moverVehiculo(filaVehiculo, columnaVehiculo, tecla, pista, adminVehiculo);


		// 3) Mover tornado cada N ticks
		int ticksPorMovimiento = adminTornado.getTornado().getVelocidad();

		if (ticksPorMovimiento < 1)
		{

			ticksPorMovimiento = 1;

		}

		if (tick % ticksPorMovimiento == 0)
		{

			adminTornado.mover(pista);

		}


		// 4) Meta y colision
		logica.verificarLineaMeta(pista, adminVehiculo);

		Vehiculo vehiculo = adminVehiculo.getVehiculo();
		Tornado tornado = adminTornado.getTornado();

		bool colision = (vehiculo.getFila() == tornado.getFila() && vehiculo.getColumna() == tornado.getColumna());


		// 5) Dibujar y registrar
		dibujar(pista, vehiculo, tornado, temporizador.getTiempo(), colision, tick);

		if (GUARDAR_TRAZA)
		{

			traza << tick << ";" << (tecla == ' ' ? '_' : tecla) << ";" << vehiculo.getFila() << ";" << vehiculo.getColumna() << ";"
				<< tornado.getFila() << ";" << tornado.getColumna() << ";" << vehiculo.getVueltasCompletadas() << ";" << colision << "\n";

		}


		// 6) Tick
		if (!MODO_PASO)
		{

			std::this_thread::sleep_for(std::chrono::milliseconds(TICK_MS));

		}

		tick++;

	}


	temporizador.detener();

	cout << "\nFin de la partida. Tiempo: " << temporizador.getTiempo() << " s" << std::endl;

}