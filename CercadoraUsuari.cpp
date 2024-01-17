#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "PassarelaUsuari.cpp"
#include "config.h"


const int UsuariNoExisteix = 1;

using namespace std;

class CercadoraUsuari {
public:
    CercadoraUsuari();
    PassarelaUsuari cercaUsuari(string sobrenomU);
    pqxx::connection conn;

};


CercadoraUsuari::CercadoraUsuari() : conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT) {
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

PassarelaUsuari CercadoraUsuari::cercaUsuari(string sobrenomU) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM usuari "
        "WHERE sobrenom = '" + sobrenomU + "' ");

    PassarelaUsuari pasUsu(result);
    if (result.empty()) throw(UsuariNoExisteix);
    return pasUsu;
}