#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "config.h"


using namespace std;

class PassarelaCompra {
public:
    PassarelaCompra(pqxx::row row);
    void insereix(string usuari, string element, string date, double preu);
    PassarelaCompra();
    string obteElementCompra();

    string obteUsuari();
    string obteElement();
    string obteData();
    double obtePreuPagat();
    
private:
    string usuari;  // En el enunciado: diagrama de clases, son diferentes. Pero no tiene sentido!
    string element;
    string data;
    double preuPagat;
};

PassarelaCompra::PassarelaCompra() {
    usuari = "";  // En el enunciado: diagrama de clases, son diferentes. Pero no tiene sentido!
    element = "";
    data = "";
    preuPagat = 0.0;
}

PassarelaCompra::PassarelaCompra(pqxx::row row) {

        usuari = row[0].c_str();
        element = row[1].c_str();
        data = row[2].c_str();
        string preu_string = row[3].c_str();
        preuPagat = stof(preu_string);

}

void PassarelaCompra::insereix(string usuari, string element, string date, double preu) {

    try {
        pqxx::connection conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT);

        if (conn.is_open()) {
            pqxx::work txn(conn);
            string preu_str = to_string(preu);
            string query = "INSERT INTO compra VALUES('" + usuari + "', '" + element + "', '" + date + "', '" + preu_str + "')";
            pqxx::result result = txn.exec(query);
            txn.commit();
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

string PassarelaCompra::obteElementCompra() {

    return element;

}

string PassarelaCompra::obteUsuari() { return usuari; }
string PassarelaCompra::obteElement() { return element; }
string PassarelaCompra::obteData() { return data; }
double PassarelaCompra::obtePreuPagat() { return preuPagat; }