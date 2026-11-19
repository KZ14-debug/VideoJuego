#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdio>
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
#include "AdminTuerca.h"
#include "Logica.h"
#include "Temporizador.h"
#include "Efectos.h"
#include "Registro.h"
#include "AdminRegistro.h"

using std::cout;
using std::string;
using std::vector;


// cosas para debugear
const int  TICK_MS = 50;        // duracion de ticks
const bool MODO_PASO = false;    // true: el juego avanza UN tick por cada tecla 
const bool GUARDAR_TRAZA = true; // true: escribe traza.txt con una linea por tick
const bool TECLAS_DEBUG = false;  // true: f = terminar carrera, k = tornado sobre el auto, u = tuerca sobre el auto
// ---------------------------------------------------------------------------------------

// Velocidad del auto: VELOCIDAD_NORMAL = 1 celda por tick. La mitad = 1 celda cada 2 ticks, el doble = 2 celdas por tick.
const int VELOCIDAD_NORMAL = 2;
const double DURACION_LENTITUD = 5.0;   // segundos que dura el efecto del tornado
const double DURACION_TURBO = 3.0;      // segundos que dura el efecto de la tuerca
const int TICKS_POR_MOVIMIENTO_TORNADO = 3;   // velocidad del tornado: se mueve cada N ticks


//esto fue para que no parpadee
void cursorAlInicio()
{

#ifdef _WIN32
	COORD origen = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), origen);
#else
	cout << "\033[H";
#endif

}


string decimales(double valor, int cifras)
{

	char buffer[32];

	snprintf(buffer, sizeof(buffer), "%.*f", cifras, valor);

	return string(buffer);

}


// Rellena con espacios para tapar restos de un cuadro anterior
string rellenar(string texto, size_t ancho = 90)
{

	if (texto.size() < ancho)
	{

		texto.append(ancho - texto.size(), ' ');

	}

	return texto + "\n";

}


bool esTeclaMovimiento(char tecla)
{

	return tecla == 'w' || tecla == 'W' || tecla == 'a' || tecla == 'A'
		|| tecla == 's' || tecla == 'S' || tecla == 'd' || tecla == 'D';

}



void dibujar(Pista& pista, Vehiculo vehiculo, Tornado tornado, Tuerca tuerca, double tiempo, int tick,
	double restanteLento, double restanteTurbo)
{

	vector<vector<char>> matriz = pista.getMatriz();   // copia: la pista original no se toca

	if (tuerca.estaActiva())
	{

		matriz[tuerca.getFila()][tuerca.getColumna()] = tuerca.getMarca();

	}

	matriz[tornado.getFila()][tornado.getColumna()] = tornado.getMarca();
	matriz[vehiculo.getFila()][vehiculo.getColumna()] = vehiculo.getMarca();   // el auto va encima de todo


	string cuadro;

	for (int i = 0; i < (int)matriz.size(); i++)
	{

		cuadro += string(matriz[i].begin(), matriz[i].end());
		cuadro += '\n';

	}

	cuadro += rellenar("Tiempo: " + decimales(tiempo, 1) + " s  |  Vueltas: " + std::to_string(vehiculo.getVueltasCompletadas())
		+ "/" + std::to_string(pista.getVueltas()) + "  |  Velocidad: " + std::to_string(vehiculo.getVelocidad())
		+ "  |  Tick: " + std::to_string(tick));

	string efectos = "";

	if (restanteLento > 0)
	{

		efectos += "[TORNADO! LENTO " + decimales(restanteLento, 1) + " s]  ";

	}

	if (restanteTurbo > 0)
	{

		efectos += "[TURBO " + decimales(restanteTurbo, 1) + " s]  ";

	}

	cuadro += rellenar(efectos);

	cuadro += rellenar("Auto (" + std::to_string(vehiculo.getFila()) + "," + std::to_string(vehiculo.getColumna()) + ")  Tornado ("
		+ std::to_string(tornado.getFila()) + "," + std::to_string(tornado.getColumna()) + ")");

	cuadro += rellenar("[w a s d] mover   [q] salir");


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
	Efectos efectos;
	AdminRegistro adminRegistro;


	AdminVehiculo adminVehiculo;

	if (!adminVehiculo.crearVehiculo(1, VELOCIDAD_NORMAL, 'A', pista))
	{

		cout << "No se pudo crear el vehiculo (revise la meta en Pista.txt)." << std::endl;
		return;

	}

	efectos.iniciar(VELOCIDAD_NORMAL);


	int filaSalida = adminVehiculo.getVehiculo().getFila();
	int columnaSalida = adminVehiculo.getVehiculo().getColumna();


	AdminTornado adminTornado;

	if (!adminTornado.crearTornado(1, TICKS_POR_MOVIMIENTO_TORNADO, 'T', pista, filaSalida, columnaSalida, 15))
	{

		cout << "No se pudo crear el tornado." << std::endl;
		return;

	}


	AdminTuerca adminTuerca;

	if (!adminTuerca.crearTuerca('*', pista, filaSalida, columnaSalida))
	{

		cout << "No se pudo crear la tuerca." << std::endl;
		return;

	}


	// Revisa si el auto choco con el tornado (lentitud, y el tornado se va a otro lugar)
	
	auto revisarEncuentros = [&]()
		{

			Vehiculo v = adminVehiculo.getVehiculo();
			Tornado t = adminTornado.getTornado();

			if (v.getFila() == t.getFila() && v.getColumna() == t.getColumna())
			{

				// Si ya esta lento, el choque se ignora (devuelve false)
				if (efectos.aplicarLentitud(DURACION_LENTITUD))
				{

					adminTornado.crearTornado(t.getIdTornado(), t.getVelocidad(), t.getMarca(), pista, v.getFila(), v.getColumna(), 15);

				}

			}

			if (adminTuerca.recoger(v.getFila(), v.getColumna()))
			{

				efectos.aplicarTurbo(DURACION_TURBO);

			}

		};


	std::ofstream traza;

	if (GUARDAR_TRAZA)
	{

		traza.open("traza.txt");
		traza << "tick;tecla;auto_fila;auto_col;velocidad;lento;turbo;tornado_fila;tornado_col;tuerca_fila;tuerca_col;tuerca_activa;vueltas\n";

	}


#ifdef _WIN32
	system("cls");   // una sola vez, al empezar
#else
	cout << "\033[2J";
#endif


	int tick = 0;
	int acumulador = 0;        // "presupuesto" de movimiento del auto
	bool forzarFin = false;

	temporizador.iniciar();


	while (!logica.finCarrera(pista, adminVehiculo))
	{

		efectos.actualizar(adminVehiculo);

		Vehiculo vehiculoActual = adminVehiculo.getVehiculo();

		adminTuerca.actualizar(pista, vehiculoActual.getFila(), vehiculoActual.getColumna());


		// 1) Entrada: se leen todas las teclas acumuladas y se usa la ultima
		char tecla = ' ';

		if (MODO_PASO)
		{

			tecla = _getch();

		}
		else
		{

			while (_kbhit())
			{

				tecla = _getch();

			}

		}

		if (tecla == 'q' || tecla == 'Q')
		{

			break;

		}


		// Teclas debug
		if (TECLAS_DEBUG)
		{

			if (tecla == 'f' || tecla == 'F')
			{

				forzarFin = true;
				break;

			}

			if (tecla == 'k' || tecla == 'K')
			{

				adminTornado.colocar(vehiculoActual.getFila(), vehiculoActual.getColumna());
				revisarEncuentros();

			}

			if (tecla == 'u' || tecla == 'U')
			{

				adminTuerca.colocar(vehiculoActual.getFila(), vehiculoActual.getColumna());
				revisarEncuentros();

			}

		}


		
		if (esTeclaMovimiento(tecla))
		{

			acumulador += adminVehiculo.getVehiculo().getVelocidad();

			while (acumulador >= VELOCIDAD_NORMAL)
			{

				logica.moverVehiculo(filaSalida, columnaSalida, tecla, pista, adminVehiculo);
				logica.verificarLineaMeta(pista, adminVehiculo);
				revisarEncuentros();

				acumulador -= VELOCIDAD_NORMAL;

			}

		}
		else
		{

			acumulador = 0;

		}


		// Mover el tornado cada n ticks
		int ticksPorMovimiento = adminTornado.getTornado().getVelocidad();

		if (ticksPorMovimiento < 1)
		{

			ticksPorMovimiento = 1;

		}

		if (tick % ticksPorMovimiento == 0)
		{

			adminTornado.mover(pista);
			revisarEncuentros();

		}


		// 4) Dibujar y registrar
		efectos.actualizar(adminVehiculo);

		Vehiculo vehiculo = adminVehiculo.getVehiculo();
		Tornado tornado = adminTornado.getTornado();
		Tuerca tuerca = adminTuerca.getTuerca();

		dibujar(pista, vehiculo, tornado, tuerca, temporizador.getTiempo(), tick, efectos.restanteLentitud(), efectos.restanteTurbo());

		if (GUARDAR_TRAZA)
		{

			traza << tick << ";" << (tecla == ' ' ? '_' : tecla) << ";" << vehiculo.getFila() << ";" << vehiculo.getColumna() << ";"
				<< vehiculo.getVelocidad() << ";" << efectos.estaLento() << ";" << efectos.estaTurbo() << ";"
				<< tornado.getFila() << ";" << tornado.getColumna() << ";" << tuerca.getFila() << ";" << tuerca.getColumna() << ";"
				<< tuerca.estaActiva() << ";" << vehiculo.getVueltasCompletadas() << "\n";

		}


		// 5) Esperar un tick
		if (!MODO_PASO)
		{

			std::this_thread::sleep_for(std::chrono::milliseconds(TICK_MS));

		}

		tick++;

	}


	temporizador.detener();


	bool carreraCompleta = forzarFin || logica.finCarrera(pista, adminVehiculo);

	cout << "\n";

	if (!carreraCompleta)
	{

		cout << "Partida cancelada." << std::endl;
		return;

	}


	
	double segundos = temporizador.getTiempo();

	cout << "Carrera completada! Tiempo: " << decimales(segundos, 2) << " s" << std::endl;
	cout << "Ingrese su nombre: ";

	string nombre;

	std::getline(std::cin >> std::ws, nombre);

	adminRegistro.guardar(Registro(nombre, (int)(segundos * 1000)));

	cout << "\n--- Mejores tiempos ---\n";

	adminRegistro.imprimirMejores(5);

	cout << std::endl;

}