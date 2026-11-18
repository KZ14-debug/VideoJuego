#include <iostream>
#include "Pista.h"
#include "AdminPista.h"
#include <limits>
#include "AdminVehiculo.h"
#include "Vehiculo.h"
#include <vector>

using namespace std;
using std::cout;
using std::cin;

void menuPrincipal();
void iniciarPartida();
void tablaPosiciones();


int main()
{

	menuPrincipal();
	return 0;
}


void menuPrincipal()
{

	int opc;

	do
	{
		cout << "\n";
		cout << "************************************************\n";
		cout << "*       	  SUPER SPRINT                  *\n";
		cout << "************************************************\n";
		cout << "\n";
		cout << "1. Iniciar juego\n";
		cout << "2. Tabla de posiciones\n";
		cout << "3. Salir\n";
		cout << "\n";
		cout << "Seleccionar opcion: ";
		cin >> opc;


		if (cin.fail())
		{

			cout << "\nEntrada no valida, vuelva a ingresar una opcion.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}


		switch (opc)
		{

		case 1:
			iniciarPartida();
			break;

		case 2:
			tablaPosiciones();
			break;

		default:
			cout << "\nOpcion no valida.\n";
			cout << "Intentelo nuevamente.\n";
			break;
		}

	} while (opc != 3);

}



void iniciarPartida()
{

	cout << "\n";
	cout << "Iniciando partida...\n";


	//Creacion de la pista

	AdminPista adminPista;

	adminPista.cargarPista("Pista.txt");

	Pista pista = adminPista.getPista();



	//Creacion del vehiculo en la pista

	AdminVehiculo adminVehiculo;

	bool automovilCreado = adminVehiculo.crearVehiculo(1, 0, '▀', pista);

	if (!automovilCreado)
	{

		cout << "El vehiculo esta en el taller.\n";
		return;
	
	}

	Vehiculo vehiculo = adminVehiculo.getVehiculo();




	//Imprimir la pista con el vehiculo en la posicion inicial

	for (int i = 0; i < pista.getAlto(); i++)
	{

		for (int j = 0; j < pista.getAncho(); j++)
		{

			if (i == vehiculo.getFila() && j == vehiculo.getColumna())
			{

				cout << vehiculo.getMarca();

			}
			else
			{

				cout << pista.matriz[i][j];

			}
			
		}

		cout << endl;

	}

}



void tablaPosiciones()
{

	cout << "\n";
	cout << "Tabla de posiciones\n";

}
