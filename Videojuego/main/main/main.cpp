#include <iostream>
#include "Pista.h"
#include "AdminPista.h"
#include <limits>

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


	AdminPista adminPista;

	adminPista.cargarPista("Pista.txt");

	Pista pista = adminPista.getPista();


	for (int i = 0; i < pista.getAlto(); i++)
	{

		for (int j = 0; j < pista.getAncho(); j++)
		{

			cout << pista.matriz[i][j];
		
		}

		cout << endl;

	}

}



void tablaPosiciones()
{

	cout << "\n";
	cout << "Tabla de posiciones\n";

}
