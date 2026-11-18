#pragma once
#include <iostream>
#include <string>

using std::string;

class Tornado{

private:
    int idTornado;
	int velocidad;
	int fila;
	int columna;
	char marca;


public: 

    Tornado(){ 
        idTornado = 0;
        velocidad = 0;
        fila = 0;
        columna = 0;
        marca = 'T';
    
    }
Tornado(int idTornado, int velocidad, int fila, int columna, char marca){

		this->idTornado = idTornado;
		this->velocidad = velocidad;
		this->fila = fila;
		this->columna = columna;
		this->marca = marca;
	}


	int getIdTornado(){

		return idTornado;
	
	}


	int getVelocidad(){

		return velocidad;
	
	}


	int getFila(){

		return fila;

	}


	int getColumna(){

		return columna;

	}


	char getMarca(){

		return marca;

	}




	void setVelocidad(int velocidad){

		this->velocidad = velocidad;
	
	}


	void mover(int fila, int columna){

		this->fila = fila;
		this->columna = columna;
	
	}




};