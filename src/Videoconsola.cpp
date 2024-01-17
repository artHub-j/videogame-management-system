#include <iostream>
#include <string>
#include "PassarelaUsuari.cpp"
#include "config.h"

using namespace std;

class Videoconsola {
private:
	Videoconsola() {

	}

	PassarelaUsuari usuari;

public:
	PassarelaUsuari obteUsuari();
	void iniciaSessio(PassarelaUsuari u);
	void tancaSessio();
	void refresca();
	static Videoconsola& getInstance() {
		static Videoconsola instance;
		instance.refresca();
		return instance;
	}

};

PassarelaUsuari Videoconsola::obteUsuari() {

	return usuari;

}

void Videoconsola::iniciaSessio(PassarelaUsuari u) {
	usuari = u;

}

void Videoconsola::tancaSessio() {

	usuari = PassarelaUsuari(); //en caso de que haya que hacer juegos, hay que programar para que no tenga ninguno, como se ha hecho en el constructor de PassarelaUsuari(),ha puesto toda la info a "".

}

void Videoconsola::refresca() {

	pqxx::connection conn("dbname=" + DBNAME + " user=" + USER + " password=" + PASSWORD + " hostaddr=" + HOSTADDR + " port=" + PORT);
	pqxx::work txn(conn);
	pqxx::result result;
	result = txn.exec("SELECT * FROM usuari "
		"WHERE sobrenom = '" + usuari.obteSobrenom() + "' ");

	usuari = PassarelaUsuari(result);

}