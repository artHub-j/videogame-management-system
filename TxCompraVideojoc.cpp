#pragma once
#include "Transaccio.cpp"
#include "CercadoraUsuari.cpp"
#include "CercadoraElemCompra.cpp"
#include "PassarelaElemCompra.cpp"
#include "PassarelaUsuari.cpp"
#include <ctime>

const int CompraExistent = 6;
const int EdatInapropiada = 7;

class TxCompraVideojoc : public Transaccio {

private:
    string videojoc;
    vector<string> resultat;


public:
    TxCompraVideojoc(string vjoc);
    void executar();
    void comprar();
    vector<string> obteResultat();

};


TxCompraVideojoc::TxCompraVideojoc(string vjoc) {
    inicialitza();
    videojoc = vjoc;
}


void TxCompraVideojoc::executar() {

    PassarelaVideojoc passVid = cercVid.cercaVideojoc(videojoc);
    resultat.push_back(passVid.obteNom());
    resultat.push_back(passVid.obteGenere());
    resultat.push_back(to_string(passVid.obteQualificacioEdat()));
    resultat.push_back(passVid.obteDataLlancament());
    PassarelaElemCompra passElem = cercElemComp.cercaElement(videojoc);
    resultat.push_back(passElem.obteDescripcio());
    resultat.push_back(to_string(passElem.obtePreu()));

    vector<PassarelaConte> passPaqeuts = cercConte.cercaVideojocConte(videojoc);

    for (int i = 0; i < passPaqeuts.size(); i++) {
    
        string nomPaquet = passPaqeuts[i].obteNomPaquet();

        vector<PassarelaConte> passVjocs = cercConte.cercaConte(nomPaquet);

        for (int j = 0; j < passVjocs.size(); j++) {

            PassarelaElemCompra passElemRelacionts = cercElemComp.cercaElement(passVjocs[j].obteNomVideojoc());
            if( passVjocs[j].obteNomVideojoc() != videojoc ) resultat.push_back(passElemRelacionts.obteNom() + "; " + passElemRelacionts.obteDescripcio() + "; " + to_string(passElemRelacionts.obtePreu()) + " euros\n");

        }

    }
}

int calcularEdad(int anioNacimiento) {
    // Obtener el ano actual de forma segura
    std::time_t tiempoActual = std::time(nullptr);
    std::tm tmActual; // No mas puntero aqui, estamos usando la estructura directamente.
    // Llamamos a localtime_s en lugar de localtime
    localtime_s(&tmActual, &tiempoActual);
    int anioActual = tmActual.tm_year + 1900; // Accedemos directamente a la estructura tmActual.

    // Calcular la edad restando el ano de nacimiento al ano actual
    int edad = anioActual - anioNacimiento;

    return edad;
}

void TxCompraVideojoc::comprar() {

    PassarelaUsuari passUsu = Videoconsola::getInstance().obteUsuari();
    string nomUsu = passUsu.obteSobrenom();

    //comprovar si el usuario ya tiene la compra
    vector<PassarelaCompra> compresUsu = cercComp.cercaCompra(nomUsu);
    for (int i = 0; i < compresUsu.size(); i++) {
        if (compresUsu[i].obteElement() == videojoc) throw(CompraExistent);
    }

    //comprovar si el usuario tiene la edad suficiente para poder comprar el videojuego
    PassarelaVideojoc passVid = cercVid.cercaVideojoc(videojoc);
    int qualEdat = passVid.obteQualificacioEdat();
    string naix = passUsu.obteDataNaixement();
    int edat = calcularEdad(stoi(naix.substr(0, 4)));
    if (qualEdat > edat) throw(EdatInapropiada);
    //hacer compra
    PassarelaElemCompra passElem = cercElemComp.cercaElement(videojoc);
    string videojoc = passVid.obteNom();
    double preu = passElem.obtePreu();

    // Definir un buffer para la cadena de tiempo
    const int TIME_STRING_SIZE = 26;
    char currentTimeString[TIME_STRING_SIZE];
    // Obtener la hora actual
    std::time_t currentTime = std::time(nullptr);

    // Convertir la hora actual a una cadena de tiempo de forma segura
    ctime_s(currentTimeString, TIME_STRING_SIZE, &currentTime);

    PassarelaCompra passComp;
    passComp.insereix(nomUsu, videojoc, currentTimeString, preu);

}

vector<string> TxCompraVideojoc::obteResultat() {

    return resultat;

}