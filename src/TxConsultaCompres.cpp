#pragma once
#include "Transaccio.cpp"

class TxConsultaCompres : public Transaccio {

private:

    vector< vector<string> > resultat;   // guarda todo lo que muestra en capa de presentacio sobre compres

public:
    TxConsultaCompres();
    void executar();
    vector< vector<string> > obteResultat();

};

TxConsultaCompres::TxConsultaCompres() {
    inicialitza();
}

void TxConsultaCompres::executar() {

    Videoconsola v = Videoconsola::getInstance();
    PassarelaUsuari u = v.obteUsuari();
    string sobrenomU = u.obteSobrenom();

    vector<PassarelaCompra> passarelaCompres = cercComp.cercaCompra(sobrenomU);

    double preuTotal = 0;

    for (int i = 0; i < passarelaCompres.size(); i++) {

        string name = passarelaCompres[i].obteElement();
        PassarelaElemCompra passElemComp = cercElemComp.cercaElement(name);
        string tipus = passElemComp.obteTipus();
        string descripcio = passElemComp.obteDescripcio();
        
        vector<string> aux;

        aux.push_back(passarelaCompres[i].obteData() + ": ");
        aux.push_back(tipus + " ");
        aux.push_back(name + "; ");
        aux.push_back(descripcio + "; ");
        aux.push_back( to_string(passarelaCompres[i].obtePreuPagat()) + "\n");

        preuTotal += passarelaCompres[i].obtePreuPagat();

        if (tipus == "paquet") {

            aux.push_back("     Videojocs:\n");

            vector<PassarelaConte> videojocsPaquet = cercConte.cercaConte(name);

            for (int i = 0; i < videojocsPaquet.size(); i++) {

                string nomVideojoc = videojocsPaquet[i].obteNomVideojoc();
                PassarelaElemCompra passElem = cercElemComp.cercaElement(nomVideojoc);
                string descripcio = passElem.obteDescripcio();
                aux.push_back("         " + nomVideojoc + "; ");
                aux.push_back(descripcio + "\n");

            }

        }

        resultat.push_back(aux);

    }

    vector<string> aux;
    aux.push_back("Total: " + to_string(preuTotal));
    resultat.push_back(aux);

}

vector< vector<string> > TxConsultaCompres::obteResultat() {

    return resultat;

}