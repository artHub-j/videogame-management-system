#pragma once
#include "Transaccio.cpp"

class TxEsborraUsuari : public Transaccio {

private:
    string contraU;

public:
    TxEsborraUsuari(string contrasenya);
    void executar();

};

TxEsborraUsuari::TxEsborraUsuari(string contrasenya) {

    inicialitza();
    contraU = contrasenya;
}

void TxEsborraUsuari::executar() {

    Videoconsola v = Videoconsola::getInstance();
    PassarelaUsuari usu = v.obteUsuari();

    if (contraU != usu.obteContrasenya()) throw(ErrorContrasenya);

    usu.esborra();

}