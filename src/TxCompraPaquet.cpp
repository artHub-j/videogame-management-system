#pragma once
#include "Transaccio.cpp"
#include "CercadoraUsuari.cpp"
#include "CercadoraElemCompra.cpp"
#include "PassarelaElemCompra.cpp"
#include "PassarelaUsuari.cpp"
#include "PassarelaPaquetVideojoc.cpp"
#include <ctime>

const int EdatInapropiadaPaquet = 12;

int calcularEdadPaq(int anioNacimiento) {
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


class TxCompraPaquet : public Transaccio {

private:
    string paquet;
    pair<vector<string>, vector<string>> resultat;


public:
    TxCompraPaquet(string pqet);
    void executar();
    void comprar();
    pair<vector<string>, vector<string>> obteResultat();

};


TxCompraPaquet::TxCompraPaquet(string pqet) {
    inicialitza();
    paquet = pqet;
}


void TxCompraPaquet::executar() {
    
    // comprobar si existe el paquet
    PassarelaPaquetVideojoc passPaquet = cercPaquet.cercaPaquetVideojoc(paquet);
    PassarelaElemCompra passElem = cercElemComp.cercaElement(paquet);
    resultat.first.push_back(passElem.obteNom());
    resultat.first.push_back(passElem.obteDescripcio());
    resultat.first.push_back(to_string(passElem.obtePreu()));
    double preuPaquet = passElem.obtePreu();
    double preuSeparat = 0.00;
    double estalvi = 0.00;
    int edatMaxima = 0; //per fer RIT9
    PassarelaUsuari passUsu = Videoconsola::getInstance().obteUsuari();
    string naixUsu = passUsu.obteDataNaixement();
    int naixUsu_int = stoi(naixUsu);
    int edatUsu = calcularEdadPaq(naixUsu_int);


    //para sacar info de todos los videojuegos del paquete
    vector<PassarelaConte> videojocsPaquet = cercConte.cercaConte(paquet);
    for (int i = 0; i < videojocsPaquet.size(); i++) {
        string nomVideojoc = videojocsPaquet[i].obteNomVideojoc();
        PassarelaElemCompra passElem = cercElemComp.cercaElement(nomVideojoc);
        PassarelaVideojoc passVid = cercVid.cercaVideojoc(nomVideojoc);
        if (passVid.obteQualificacioEdat() > edatMaxima) {

            edatMaxima = passVid.obteQualificacioEdat();
            if (edatMaxima > edatUsu) throw (EdatInapropiadaPaquet);
        }
        string descripcio = passElem.obteDescripcio();
        double preu = passElem.obtePreu();
        preuSeparat += preu;
        string preustring = to_string(preu);
        resultat.second.push_back("- "+nomVideojoc + "; ");
        resultat.second.push_back(descripcio +  "; " );
        resultat.second.push_back(preustring + " euros \n");
    }

    estalvi = preuSeparat - preuPaquet;
    resultat.first.push_back(to_string(estalvi));
    resultat.first.push_back(to_string(edatMaxima)); //guarda la edat maxima dels videojocs del paquet
}



void TxCompraPaquet::comprar() {

    PassarelaUsuari passUsu = Videoconsola::getInstance().obteUsuari();
    string nomUsu = passUsu.obteSobrenom();

    //comprovar si el usuario ya tiene la compra
    vector<PassarelaCompra> compresUsu = cercComp.cercaCompra(nomUsu);
    for (int i = 0; i < compresUsu.size(); i++) {
        if (compresUsu[i].obteElement() == paquet) throw(CompraExistent);
    }
    
  
    //hacer compra
    PassarelaElemCompra passElem = cercElemComp.cercaElement(paquet); //lanza excepción element no existeix
    double preu = passElem.obtePreu();


    // Definir un buffer para la cadena de tiempo
    const int TIME_STRING_SIZE = 26;
    char currentTimeString[TIME_STRING_SIZE];
    // Obtener la hora actual
    std::time_t currentTime = std::time(nullptr);

    // Convertir la hora actual a una cadena de tiempo de forma segura
    ctime_s(currentTimeString, TIME_STRING_SIZE, &currentTime);

    PassarelaCompra passComp;
    passComp.insereix(nomUsu, paquet, currentTimeString, preu);

}


pair<vector<string>, vector<string>> TxCompraPaquet::obteResultat() {

    return resultat;

}