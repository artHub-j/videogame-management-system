#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include "PassarelaConte.cpp"
#include "config.h"


using namespace std;

class CercadoraConte {
public:
    CercadoraConte();
    vector<PassarelaConte> cercaConte(string nomPaquet);
    vector<PassarelaConte> cercaVideojocConte(string nomVideojoc);
    pqxx::connection conn;

private:

};


CercadoraConte::CercadoraConte() : conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT) {
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

vector<PassarelaConte> CercadoraConte::cercaConte(string nomPaquet) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM conte "
        "WHERE paquet = '" + nomPaquet + "' ");

    vector<PassarelaConte> passContes;
    if (!result.empty()) {
        for (size_t i = 0; i < result.size(); ++i) {

            PassarelaConte passConte(result[i]);
            passContes.push_back(passConte);
        }
    }

    return passContes;
}

vector<PassarelaConte> CercadoraConte::cercaVideojocConte(string nomVideojoc) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM conte "
        "WHERE videojoc = '" + nomVideojoc + "' ");

    vector<PassarelaConte> passContes;
    if (!result.empty()) {
        for (size_t i = 0; i < result.size(); ++i) {

            PassarelaConte passConte(result[i]);
            passContes.push_back(passConte);
        }
    }

    return passContes;
}