#pragma once
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "config.h"



using namespace std;

const int SobrenomExisteix = 3;
const int CorreuExisteix = 4;

class PassarelaUsuari {
public:
    PassarelaUsuari(pqxx::result result);
    PassarelaUsuari();
    PassarelaUsuari(string nomU, string sobrenomU, string contrasenyaU, string correuElectronicU, string dataNaixementU);
    void insereix();
    void modifica();
    void esborra();

    string obteContrasenya();
    string obteNom();
    string obteSobrenom();
    string obteCorreuElectronic();
    string obteDataNaixement();
    void posaContrasenya(string contraU);
    void posaNom(string nomU);
    void posaCorreuElectronic(string correuU);
    void posaDataNaixement(string neixU);

private:
    string nom, sobrenom, contrasenya, correuElectronic, dataNaixement;
};

PassarelaUsuari::PassarelaUsuari() {
    nom = "";
    sobrenom = "";
    contrasenya = "";
    correuElectronic = "";
    dataNaixement = "";

}

PassarelaUsuari::PassarelaUsuari(pqxx::result result) {
    if (!result.empty()) {

        sobrenom = result[0][0].c_str();
        nom = result[0][1].c_str();
        contrasenya = result[0][2].c_str();
        correuElectronic = result[0][3].c_str();
        dataNaixement = result[0][4].c_str();
    }
}


PassarelaUsuari::PassarelaUsuari(string nomU, string sobrenomU, string contrasenyaU, string correuElectronicU, string dataNaixementU) {

    nom = nomU;
    sobrenom = sobrenomU;
    contrasenya = contrasenyaU;
    correuElectronic = correuElectronicU;
    dataNaixement = dataNaixementU;

}

void PassarelaUsuari::insereix() {
    try {
        pqxx::connection conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT);

        if (conn.is_open()) {
            pqxx::result comprovarSobrenom;
            pqxx::work txn(conn);
            comprovarSobrenom = txn.exec("SELECT sobrenom FROM usuari "
                "WHERE sobrenom = '" + sobrenom + "' ");
            if (!comprovarSobrenom.empty()) throw (SobrenomExisteix);


            pqxx::result comprovarCorrE;
            comprovarCorrE = txn.exec("SELECT correu_electronic FROM usuari "
                "WHERE correu_electronic = '" + correuElectronic + "' ");
            if (!comprovarCorrE.empty()) throw (CorreuExisteix);


            string query = "INSERT INTO usuari VALUES('" + sobrenom + "', '" + nom + "', '" + contrasenya + "', '" + correuElectronic + "', '" + dataNaixement + "')";
            pqxx::result result = txn.exec(query);
            txn.commit();
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

void PassarelaUsuari::modifica() {

    try {
        pqxx::connection conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT);

        if (conn.is_open()) {
            pqxx::result comprovarSobrenom;
            pqxx::work txn(conn);

            pqxx::result comprovarCorrE;
            comprovarCorrE = txn.exec("SELECT correu_electronic FROM usuari "
                "WHERE correu_electronic = '" + correuElectronic + "' ");
            if (!comprovarCorrE.empty()) throw (CorreuExisteix);

            string query = "UPDATE usuari SET "
                "nom = '" + nom + "', "
                "contrasenya = '" + contrasenya + "', "
                "correu_electronic = '" + correuElectronic + "', "
                "data_naixement = '" + dataNaixement + "' "
                "WHERE sobrenom = '" + sobrenom + "';";

            pqxx::result result = txn.exec(query);
            txn.commit();
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

void PassarelaUsuari::esborra() {

    try {
        pqxx::connection conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT);

        if (conn.is_open()) {
            pqxx::result comprovarSobrenom;
            pqxx::work txn(conn);

            string query = "DELETE FROM usuari WHERE sobrenom = '" + sobrenom + "' ";

            pqxx::result result = txn.exec(query);
            txn.commit();
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }

}

string PassarelaUsuari::obteContrasenya() {
    return contrasenya;
}


string PassarelaUsuari::obteNom() {
    return nom;
}

string PassarelaUsuari::obteSobrenom() {
    return sobrenom;
}

string PassarelaUsuari::obteCorreuElectronic() {
    return correuElectronic;
}

string PassarelaUsuari::obteDataNaixement() {
    return dataNaixement;
}

void PassarelaUsuari::posaContrasenya(string contraU) {

    contrasenya = contraU;

}

void PassarelaUsuari::posaNom(string nomU) {

    nom = nomU;

}

void PassarelaUsuari::posaCorreuElectronic(string correuU) {

    correuElectronic = correuU;

}

void PassarelaUsuari::posaDataNaixement(string neixU) {

    dataNaixement = neixU;

}