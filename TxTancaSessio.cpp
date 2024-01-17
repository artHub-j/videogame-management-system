#pragma once
#include "Transaccio.cpp"
class TXTancaSessio : public Transaccio {

private:


public:
    TXTancaSessio();
    void executar();
};

TXTancaSessio::TXTancaSessio() {
    inicialitza();
}

void TXTancaSessio::executar() {
    Videoconsola& videoconsola = Videoconsola::getInstance();
    videoconsola.tancaSessio();
}