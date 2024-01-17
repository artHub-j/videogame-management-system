#pragma once
#include "Transaccio.cpp"
#include "CercadoraUsuari.cpp"
#include "PassarelaUsuari.cpp"

class TXIniciSessio : public Transaccio {

private:
    string sobrenomU;
    string contrasenyaU;

public:
    TXIniciSessio(string sU, string cU);
    void executar();
};

TXIniciSessio::TXIniciSessio(string sU, string cU) {
    inicialitza();
    sobrenomU = sU;
    contrasenyaU = cU;
}

void TXIniciSessio::executar() {
    PassarelaUsuari u = cercUsu.cercaUsuari(sobrenomU);
    if (u.obteContrasenya() != contrasenyaU) throw(ErrorContrasenya);
    Videoconsola& videoconsola = Videoconsola::getInstance();
    videoconsola.iniciaSessio(u);
}