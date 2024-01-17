#pragma once
#include "Transaccio.cpp"

class TxConsultaUsuari : public Transaccio {

private:
    string resultat[4];
    PassarelaUsuari usuari;

public:
    TxConsultaUsuari();
    void executar();
    string* obteResultat();
    PassarelaUsuari obteUsuari();
};

TxConsultaUsuari::TxConsultaUsuari() {
    inicialitza();
}

void TxConsultaUsuari::executar() {

    Videoconsola v = Videoconsola::getInstance();
    PassarelaUsuari u = v.obteUsuari();

    resultat[0] = u.obteNom();
    resultat[1] = u.obteSobrenom();
    resultat[2] = u.obteCorreuElectronic();
    resultat[3] = u.obteDataNaixement();

    usuari = u;

}

PassarelaUsuari TxConsultaUsuari::obteUsuari() {

    return usuari;

}

string* TxConsultaUsuari::obteResultat() {

    return resultat;

}