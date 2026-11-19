#pragma once
#include <chrono>


using std::chrono::steady_clock;


class Temporizador{

private:
    
    steady_clock::time_point inicio;
    steady_clock::time_point fin;
    bool corriendo;


public: 

    Temporizador(){ 
        corriendo = false;
    }

    void iniciar(){
        inicio = steady_clock::now();
        corriendo = true;
    }

    void detener(){
        fin = steady_clock::now();
        corriendo = false;
    }

    double getTiempo(){ //devuelve segundos
        if(corriendo){
            return std::chrono::duration<double>(steady_clock::now() - inicio).count();
        }
        return std::chrono::duration<double>(fin - inicio).count();
    }

    bool getCinco(){
        if (getTiempo() >= 5.0){
            return true;
        }
        return false;
    }
    bool getTres(){
        if (getTiempo() >= 3.0){
            return true;
        }
        return false;
    }

};