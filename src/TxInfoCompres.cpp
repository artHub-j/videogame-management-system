#pragma once
#include "Transaccio.cpp"
#include <vector>

class TxInfoCompres : public Transaccio {

private:

    PassarelaUsuari usuari;
    double resultat[3];
    double totalEuros;
    int totalVideojocs, totalPaquets;

public:
    TxInfoCompres();
    void executar();
    double* obteResultat();
};

TxInfoCompres::TxInfoCompres() {

    inicialitza();
    totalEuros = totalVideojocs = totalPaquets = 0.0;

}

void TxInfoCompres::executar() {

    Videoconsola v = Videoconsola::getInstance();
    PassarelaUsuari u = v.obteUsuari();

    usuari = u;

    string sobrenomU = u.obteSobrenom();
    vector<PassarelaCompra> passCompres = cercComp.cercaCompra(sobrenomU);

    for (int i = 0; i < passCompres.size(); i++) {

        string elem = passCompres[i].obteElementCompra();
        PassarelaElemCompra ec = cercElemComp.cercaElement(elem);
        totalEuros = totalEuros + ec.obtePreu();

        if (ec.obteTipus() == "videojoc") totalVideojocs++;
        else if (ec.obteTipus() == "paquet") totalPaquets++;

    }

    resultat[0] = totalPaquets;
    resultat[1] = totalVideojocs;
    resultat[2] = totalEuros;

}

double* TxInfoCompres::obteResultat() {

    return resultat;
}