#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include "PassarelaPaquetVideojoc.cpp"
#include "config.h"



using namespace std;

const int PaquetNoExixtent = 10;

class CercadoraPaquetVideojoc {
public:
    CercadoraPaquetVideojoc();
    PassarelaPaquetVideojoc cercaPaquetVideojoc(string nomV);

    pqxx::connection conn;

};


CercadoraPaquetVideojoc::CercadoraPaquetVideojoc() : conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT) {
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

PassarelaPaquetVideojoc CercadoraPaquetVideojoc::cercaPaquetVideojoc(string nomP) {

    pqxx::work txn(conn);
    pqxx::result result;
    result = txn.exec("SELECT * FROM paquet_videojoc "
        "WHERE nom = '" + nomP + "' ");

    if (result.empty()) throw(PaquetNoExixtent);

    PassarelaPaquetVideojoc p(result[0]);

    return p;

}