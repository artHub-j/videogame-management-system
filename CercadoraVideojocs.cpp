#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include "PassarelaVideojoc.cpp"
#include "config.h"


using namespace std;

const int VideojocNoExisteix = 5;

class CercadoraVideojocs {
public:
    CercadoraVideojocs();
    vector<PassarelaVideojoc> cercaVideojocs();
    PassarelaVideojoc cercaVideojoc(string nomV);
    vector<PassarelaVideojoc> cercaVideojocDataLlancament(string data);
    vector<PassarelaVideojoc> cercaVideojocsEdat(int edat);
    pqxx::connection conn;

};


CercadoraVideojocs::CercadoraVideojocs() : conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT) {
    // Intenta conectarte en el constructor y maneja cualquier excepción que pueda lanzarse aquí.

    try {
        if (conn.is_open()) {
            //cout << "Connected to the database successfully!" << endl;
        }
        else {

            //cout << "Failed to connect to the database." << endl;
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

vector<PassarelaVideojoc> CercadoraVideojocs::cercaVideojocs() {
    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM videojoc");
    vector<PassarelaVideojoc> totsVideojocs;

    for (int i = 0; i < result.size(); i++) {
        PassarelaVideojoc passVid(result[i]);
        totsVideojocs.push_back(passVid);
    }
    return totsVideojocs;
}

PassarelaVideojoc CercadoraVideojocs::cercaVideojoc(string nomV) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM videojoc "
        "WHERE nom = '" + nomV + "' ");

    if (result.empty()) throw(VideojocNoExisteix);

    PassarelaVideojoc vJoc(result[0]);

    return vJoc;

}

vector<PassarelaVideojoc> CercadoraVideojocs::cercaVideojocDataLlancament(string data) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM videojoc "
        "WHERE data_llansament >= '" + data + "' ");

    vector<PassarelaVideojoc> passVideojocs;
    for (size_t i = 0; i < result.size(); ++i) {

        PassarelaVideojoc passVid(result[i]);
        passVideojocs.push_back(passVid);

    }
    return passVideojocs;

}

vector<PassarelaVideojoc> CercadoraVideojocs::cercaVideojocsEdat(int edat) {
    pqxx::work txn(conn);
    pqxx::result result;

    string edat_str = to_string(edat);
    result = txn.exec("SELECT * FROM videojoc "
        "WHERE qualificacio_edat <= '" + edat_str + "' ");
    vector<PassarelaVideojoc> totsVideojocs;

    for (int i = 0; i < result.size(); i++) {
        PassarelaVideojoc passVid(result[i]);
        totsVideojocs.push_back(passVid);
    }
    return totsVideojocs;
}