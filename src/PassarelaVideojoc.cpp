#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "config.h"


using namespace std;

class PassarelaVideojoc {
public:
    PassarelaVideojoc();
    PassarelaVideojoc(pqxx::row row);
    
    string obteNom();
    string obteGenere();
    int obteQualificacioEdat();
    string obteDataLlancament();
    int obteMinsEstimat();



private:
    string nom; 
    string genere;
    int qualificacioEdat;
    string dataLlancament;
    int minsEstimat;

};

PassarelaVideojoc::PassarelaVideojoc() {
    
    nom = "";
    genere = "";
    qualificacioEdat = 0;
    dataLlancament = "";
    int minsestimat = 0;
  
}

PassarelaVideojoc::PassarelaVideojoc(pqxx::row row) {

    nom = row[0].c_str();
    genere = row[1].c_str();

    string qualificacioEdat_string = row[2].c_str();
    qualificacioEdat = stoi(qualificacioEdat_string);

    dataLlancament = row[3].c_str();
    string minsestimat_string = row[4].c_str();

    minsEstimat = stoi(minsestimat_string);
}


string PassarelaVideojoc::obteNom() {
    return nom;
}

string PassarelaVideojoc::obteGenere() {
    return genere;
}

int PassarelaVideojoc::obteQualificacioEdat() {
    return qualificacioEdat;
}

string PassarelaVideojoc::obteDataLlancament() {
    return dataLlancament;
}

int PassarelaVideojoc::obteMinsEstimat() {
    return minsEstimat;
}
