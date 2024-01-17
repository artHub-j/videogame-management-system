#pragma once
#include "Transaccio.cpp"
#include "PassarelaUsuari.cpp"

class TxRegistraUsuari : public Transaccio {
private:
    string nomU;
    string sobrenomU;
    string contrasenyaU;
    string correuElectronicU;
    string dataNaixementU;

public:
    TxRegistraUsuari();
    TxRegistraUsuari(string nU, string sU, string cU, string ceU, string dnU);
    void executar();
};

TxRegistraUsuari::TxRegistraUsuari() {
    inicialitza();

}

TxRegistraUsuari::TxRegistraUsuari(string nU, string sU, string cU, string ceU, string dnU) {
    inicialitza();
    nomU = nU;
    sobrenomU = sU;
    contrasenyaU = cU;
    correuElectronicU = ceU;
    dataNaixementU = dnU;
}

void TxRegistraUsuari::executar() {
    PassarelaUsuari u(nomU, sobrenomU, contrasenyaU, correuElectronicU, dataNaixementU);
    u.insereix();
}
