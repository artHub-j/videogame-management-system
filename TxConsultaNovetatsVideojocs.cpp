#pragma once
#include "Transaccio.cpp"

class TxConsultaNovetatsVideojocs : public Transaccio {

private:

    vector< vector<string>> resultat;
    string data;

public:
    TxConsultaNovetatsVideojocs(string dataL);
    void executar();
    vector<vector<string>> obteResultat();

};

TxConsultaNovetatsVideojocs::TxConsultaNovetatsVideojocs(string dataL) {
    inicialitza();
    data = dataL;
}

void TxConsultaNovetatsVideojocs::executar() {

    vector<PassarelaVideojoc> passVids = cercVid.cercaVideojocDataLlancament(data);
    for (int i = 0; i < passVids.size(); i++) {
        vector<string> aux;
        string nomVideojoc = passVids[i].obteNom();
        aux.push_back(nomVideojoc);
        PassarelaElemCompra passElem = cercElemComp.cercaElement(nomVideojoc);
        aux.push_back(passElem.obteDescripcio());
        aux.push_back(to_string(passElem.obtePreu()));
        aux.push_back(to_string(passVids[i].obteQualificacioEdat()));
        aux.push_back(passVids[i].obteGenere());
        aux.push_back(passVids[i].obteDataLlancament());
        
        vector<PassarelaConte> passContes = cercConte.cercaVideojocConte(nomVideojoc);
        for (int i = 0; i < passContes.size(); i++) {

            aux.push_back(passContes[i].obteNomPaquet());

        }
        resultat.push_back(aux);
    }

}

vector< vector<string>> TxConsultaNovetatsVideojocs::obteResultat() {

    return resultat;

}