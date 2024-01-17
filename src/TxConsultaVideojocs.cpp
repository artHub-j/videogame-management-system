#pragma once
#include "Transaccio.cpp"

class TxConsultaVideojocs : public Transaccio {

private:

    vector<vector<string>> resultat;   // guarda todo lo que muestra en capa de presentacio sobre compres

public:
    TxConsultaVideojocs();
    void executar();
    vector<vector<string>> obteResultat();

};

TxConsultaVideojocs::TxConsultaVideojocs() {
    inicialitza();
}

void TxConsultaVideojocs::executar() {

    vector<PassarelaVideojoc> passVids = cercVid.cercaVideojocs();
    for (int i = 0; i < passVids.size(); i++) {
        vector<string> aux;
        string nomVideojoc = passVids[i].obteNom();
        aux.push_back(nomVideojoc);
        PassarelaElemCompra passElem = cercElemComp.cercaElement(nomVideojoc);
        aux.push_back(passElem.obteDescripcio());
        aux.push_back(to_string(passVids[i].obteQualificacioEdat()));
        aux.push_back(passVids[i].obteGenere());
        aux.push_back(passVids[i].obteDataLlancament());
        aux.push_back(to_string(passElem.obtePreu()));
        vector<PassarelaConte> passContes = cercConte.cercaVideojocConte(nomVideojoc);
        for (int i = 0; i < passContes.size(); i++) {

            aux.push_back(passContes[i].obteNomPaquet());

        }
        resultat.push_back(aux);
    }
}

vector<vector<string>> TxConsultaVideojocs::obteResultat() {

    return resultat;

}