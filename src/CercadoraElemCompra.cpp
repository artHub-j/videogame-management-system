#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include "PassarelaElemCompra.cpp"
#include "config.h"


using namespace std;

const int ElementNoExisteix = 9;

class CercadoraElemCompra {
public:
    CercadoraElemCompra();
    PassarelaElemCompra cercaElement(string elem);
    vector<PassarelaElemCompra> cercaPaquets();
    pqxx::connection conn;

};


CercadoraElemCompra::CercadoraElemCompra() : conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT) {
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

PassarelaElemCompra CercadoraElemCompra::cercaElement(string elem) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM element_compra "
        "WHERE nom = '" + elem + "'");

    if (result.empty()) throw(ElementNoExisteix);
    PassarelaElemCompra pasElemComp(result[0]);
    return pasElemComp;

}

vector<PassarelaElemCompra> CercadoraElemCompra::cercaPaquets() {
    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM element_compra "
        "WHERE tipus = 'paquet'");
    vector<PassarelaElemCompra> totsPaquets;

    for (int i = 0; i < result.size(); i++) {
        PassarelaElemCompra passPaq(result[i]);
        totsPaquets.push_back(passPaq);
    }
    return totsPaquets;
}