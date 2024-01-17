#pragma once
#include "Transaccio.cpp"
#include "CercadoraUsuari.cpp"
#include "CercadoraElemCompra.cpp"
#include "PassarelaElemCompra.cpp"
#include "PassarelaUsuari.cpp"
#include <ctime>

const int rit3 = 11;

class TxConsultaPaquet : public Transaccio {

private:
    string paquet;
    pair<vector<string>, vector<string>> resultat;


public:
    TxConsultaPaquet(string pqet);
    void executar();
    void comprar();
    pair<vector<string>, vector<string>> obteResultat();

};


TxConsultaPaquet::TxConsultaPaquet(string pqet) {
    inicialitza();
    paquet = pqet;
}


void TxConsultaPaquet::executar() {
    
    PassarelaElemCompra passElem = cercElemComp.cercaElement(paquet);
    resultat.first.push_back(passElem.obteNom());
    resultat.first.push_back(passElem.obteDescripcio());
    resultat.first.push_back(to_string(passElem.obtePreu()));
    
    double preuPaquet = passElem.obtePreu();
    double preuSeparat = 0.00;
    double estalvi = 0.00;

    //para sacar info de todos los videojuegos del paquete
    vector<PassarelaConte> videojocsPaquet = cercConte.cercaConte(paquet);
    for (int i = 0; i < videojocsPaquet.size(); i++) {
        string nomVideojoc = videojocsPaquet[i].obteNomVideojoc();
        PassarelaElemCompra passElem = cercElemComp.cercaElement(nomVideojoc);
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
}


pair<vector<string>, vector<string>> TxConsultaPaquet::obteResultat() {

    return resultat;

}