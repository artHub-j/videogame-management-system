#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "config.h"


using namespace std;

class PassarelaElemCompra {
public:
    PassarelaElemCompra(pqxx::row row);
    PassarelaElemCompra();
    double obtePreu();
    string obteTipus();
    string obteDescripcio();
    string obteNom();

private:
    string nom;  // En el enunciado: diagrama de clases, son diferentes. Pero no tiene sentido!
    string descripcio;
    double preu;
    string tipus;
};

PassarelaElemCompra::PassarelaElemCompra() {

}

PassarelaElemCompra::PassarelaElemCompra(pqxx::row row) {

    nom = row[0].c_str();
    descripcio = row[1].c_str();

    string preu_string = row[2].c_str();
    preu = stof(preu_string);

    tipus = row[3].c_str();

}

double PassarelaElemCompra::obtePreu() {

    return preu;

}

string PassarelaElemCompra::obteTipus() {

    return tipus;

}

string PassarelaElemCompra::obteDescripcio() {

    return descripcio;

}

string PassarelaElemCompra::obteNom() {

    return nom;

}