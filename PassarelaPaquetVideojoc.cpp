#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "config.h"



using namespace std;

class PassarelaPaquetVideojoc {
public:
    PassarelaPaquetVideojoc();
    PassarelaPaquetVideojoc(pqxx::row row);

    string obteNom();

private:
    string nom;

};

PassarelaPaquetVideojoc::PassarelaPaquetVideojoc() {

}

PassarelaPaquetVideojoc::PassarelaPaquetVideojoc(pqxx::row row) {

    nom = row[0].c_str();

}


string PassarelaPaquetVideojoc::obteNom() {
    return nom;
}
