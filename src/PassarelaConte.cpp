#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "config.h"


using namespace std;

class PassarelaConte {
public:
    PassarelaConte(pqxx::row row);
    PassarelaConte();

    string obteNomVideojoc();
    string obteNomPaquet();

private:
    string nomVideojoc;  // En el enunciado: diagrama de clases, son diferentes. Pero no tiene sentido!
    string nomPaquet;
};

PassarelaConte::PassarelaConte() {

}

PassarelaConte::PassarelaConte(pqxx::row row) {

     nomPaquet = row[0].c_str();
     nomVideojoc = row[1].c_str();

}

string PassarelaConte::obteNomVideojoc() { return nomVideojoc; }
string PassarelaConte::obteNomPaquet() { return nomPaquet; }