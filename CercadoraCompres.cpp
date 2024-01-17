#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include "PassarelaCompra.cpp"
#include "config.h"


using namespace std;

class CercadoraCompres {
public:
    CercadoraCompres();
    vector<PassarelaCompra> cercaCompra(string sobrenomU);
    pqxx::connection conn;

};


CercadoraCompres::CercadoraCompres() : conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT) {
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

vector<PassarelaCompra> CercadoraCompres::cercaCompra(string sobrenomU) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM compra "
        "WHERE usuari = '" + sobrenomU + "' ");

    vector<PassarelaCompra> passComps;
    if(!result.empty()) {
        for (size_t i = 0; i < result.size(); ++i) {

            PassarelaCompra passComp(result[i]);
            passComps.push_back(passComp);
        }
    }

    //if (result.empty()) throw(UsuariNoExisteix);
    return passComps;
    
}