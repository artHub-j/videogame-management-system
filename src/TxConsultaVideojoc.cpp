#pragma once
#include "Transaccio.cpp"

class TxConsultaVideojoc : public Transaccio {

private:

    vector<string> resultat;   // guarda todo lo que muestra en capa de presentacio sobre compres
    string nomVideojoc;

public:
    TxConsultaVideojoc(string nomVideojoc);
    void executar();
    vector<string> obteResultat();

};

TxConsultaVideojoc::TxConsultaVideojoc(string nomVj) {
    inicialitza();
    nomVideojoc = nomVj;
}

void TxConsultaVideojoc::executar() {

    PassarelaVideojoc passVid = cercVid.cercaVideojoc(nomVideojoc);

    resultat.push_back(passVid.obteNom());
    resultat.push_back( to_string(passVid.obteQualificacioEdat()) );
    resultat.push_back(passVid.obteGenere());
    resultat.push_back(passVid.obteDataLlancament());

    PassarelaElemCompra passElem = cercElemComp.cercaElement(nomVideojoc);

    resultat.push_back(passElem.obteDescripcio());
    resultat.push_back( to_string(passElem.obtePreu()) );

    vector<PassarelaConte> passContes = cercConte.cercaVideojocConte(nomVideojoc);

    for (int i = 0; i < passContes.size(); i++) {

        resultat.push_back(passContes[i].obteNomPaquet());

    }

}

vector<string> TxConsultaVideojoc::obteResultat() {

    return resultat;

}