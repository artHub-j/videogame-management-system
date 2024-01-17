#pragma once
#include "Transaccio.cpp"

class TxConsultaPaquets : public Transaccio {

private:

    vector<vector<string>> resultat;   // guarda todo lo que muestra en capa de presentacio sobre compres

public:
    TxConsultaPaquets();
    void executar();
    vector<vector<string>> obteResultat();

};

TxConsultaPaquets::TxConsultaPaquets() {
    inicialitza();
}

void TxConsultaPaquets::executar() {

    vector<PassarelaElemCompra> passPaqs = cercElemComp.cercaPaquets();
    double estalvi = 0;
    double preuSeparat = 0;
    double preuPaquet = 0;
    for (int i = 0; i < passPaqs.size(); i++) {
        vector<string> aux;
        string nomPaquet = passPaqs[i].obteNom();
        aux.push_back(nomPaquet);
        aux.push_back(passPaqs[i].obteDescripcio());
        preuPaquet = passPaqs[i].obtePreu();
        aux.push_back(to_string(preuPaquet));
        vector<PassarelaConte> passContes = cercConte.cercaConte(nomPaquet);
        for (int i = 0; i < passContes.size(); i++) {
            string nomVjoc = passContes[i].obteNomVideojoc();
            PassarelaElemCompra passComp = cercElemComp.cercaElement(nomVjoc);
            preuSeparat += passComp.obtePreu();
        }
        estalvi = preuSeparat - preuPaquet;
        aux.push_back(to_string(estalvi));
        resultat.push_back(aux);
    }

}

vector<vector<string>> TxConsultaPaquets::obteResultat() {

    return resultat;

}