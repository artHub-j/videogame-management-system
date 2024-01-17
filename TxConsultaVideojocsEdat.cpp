#pragma once
#include "Transaccio.cpp"

class TxConsultaVideojocsEdat : public Transaccio {

private:

    vector<vector<string>> resultat;   // guarda todo lo que muestra en capa de presentacio sobre compres
    int edat;

public:
    TxConsultaVideojocsEdat();
    void executar();
    vector<vector<string>> obteResultat();
    TxConsultaVideojocsEdat(int edatU);

};

TxConsultaVideojocsEdat::TxConsultaVideojocsEdat() {
    inicialitza();
}

TxConsultaVideojocsEdat::TxConsultaVideojocsEdat(int edatU) {
    inicialitza();
    edat = edatU;
}

void TxConsultaVideojocsEdat::executar() {

    vector<PassarelaVideojoc> passVids = cercVid.cercaVideojocsEdat(edat);
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

vector<vector<string>> TxConsultaVideojocsEdat::obteResultat() {

    return resultat;

}