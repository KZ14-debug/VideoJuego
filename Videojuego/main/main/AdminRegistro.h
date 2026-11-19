#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Registro.h"

using std::string;
using std::vector;


//una linea por jugador ->  nombre;milisegundos
class AdminRegistro
{

private:

	string archivo;


	
	string limpiarNombre(string nombre) const
	{

		for (size_t i = 0; i < nombre.size(); i++)
		{

			if (nombre[i] == ';' || nombre[i] == '\n' || nombre[i] == '\r')
			{

				nombre[i] = ' ';

			}

		}

		size_t inicio = nombre.find_first_not_of(' ');

		if (inicio == string::npos)
		{

			return "Jugador";

		}

		size_t fin = nombre.find_last_not_of(' ');

		nombre = nombre.substr(inicio, fin - inicio + 1);

		if (nombre.size() > 20)
		{

			nombre = nombre.substr(0, 20);

		}

		return nombre;

	}


public:

	AdminRegistro(const string& archivo = "Registros.txt")
	{

		this->archivo = archivo;

	}


	bool guardar(const Registro& registro)
	{

		std::ofstream file(archivo, std::ios::app);

		if (!file.is_open())
		{

			std::cout << "Error al abrir " << archivo << " para guardar." << std::endl;
			return false;

		}

		file << limpiarNombre(registro.getNombre()) << ";" << registro.getMilisegundos() << "\n";

		return true;

	}


	vector<Registro> cargar()
	{

		vector<Registro> registros;

		std::ifstream file(archivo);

		if (!file.is_open())
		{

			return registros;

		}

		string linea;

		while (std::getline(file, linea))
		{

			if (!linea.empty() && linea.back() == '\r')
			{

				linea.pop_back();

			}

			size_t pos = linea.rfind(';');

			if (pos == string::npos)
			{

				continue;

			}

			try
			{

				int ms = std::stoi(linea.substr(pos + 1));

				registros.push_back(Registro(linea.substr(0, pos), ms));

			}
			catch (...)
			{

				continue;

			}

		}

		std::sort(registros.begin(), registros.end(), [](const Registro& a, const Registro& b)
			{
				return a.getMilisegundos() < b.getMilisegundos();
			});

		return registros;

	}


	vector<Registro> mejores(int cantidad)
	{

		vector<Registro> registros = cargar();

		if ((int)registros.size() > cantidad)
		{

			registros.resize(cantidad);

		}

		return registros;

	}


	void imprimirMejores(int cantidad)
	{

		vector<Registro> registros = mejores(cantidad);

		if (registros.empty())
		{

			std::cout << "Todavia no hay tiempos registrados.\n";
			return;

		}

		std::ios_base::fmtflags flags = std::cout.flags();
		std::streamsize precision = std::cout.precision();

		std::cout << std::left << std::setw(6) << "Pos" << std::setw(24) << "Nombre" << "Tiempo (s)\n";

		for (int i = 0; i < (int)registros.size(); i++)
		{

			std::cout << std::left << std::setw(6) << (i + 1) << std::setw(24) << registros[i].getNombre()
				<< std::fixed << std::setprecision(2) << registros[i].getSegundos() << "\n";

		}

		std::cout.flags(flags);
		std::cout.precision(precision);

	}

};