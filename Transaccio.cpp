#pragma once
#include <iostream>
#include <string>
#include "CercadoraUsuari.cpp"
#include "CercadoraCompres.cpp"
#include "CercadoraElemCompra.cpp"
#include "CercadoraConte.cpp"
#include "CercadoraVideojocs.cpp"
#include "CercadoraPaquetVideojoc.cpp"
#include "Videoconsola.cpp"

using namespace std;

const int ErrorContrasenya = 2;

class Transaccio {
public:


    Transaccio();
    virtual void executar() = 0;
    ~Transaccio();



protected:
    CercadoraUsuari cercUsu;
    CercadoraCompres cercComp;
    CercadoraElemCompra cercElemComp;
    CercadoraVideojocs cercVid;
    CercadoraConte cercConte;
    CercadoraPaquetVideojoc cercPaquet;
    void inicialitza();

};


Transaccio::Transaccio() {
    inicialitza();
}

Transaccio::~Transaccio() {

}

void Transaccio::inicialitza() {

}