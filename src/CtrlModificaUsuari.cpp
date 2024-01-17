#include "PassarelaUsuari.cpp"
#include "TxConsultaUsuari.cpp"
#include <vector>

class CtrlModificaUsuari {

	private:
		PassarelaUsuari usuari;

	public:
		CtrlModificaUsuari();
		CtrlModificaUsuari(const CtrlModificaUsuari& C);
		vector<string> consultaUsuari();
		void modificaUsuari(string nomU, string contraU, string correuU, string neixU);

};

CtrlModificaUsuari::CtrlModificaUsuari() {


}

CtrlModificaUsuari::CtrlModificaUsuari(const CtrlModificaUsuari& C) {

	usuari = C.usuari;
}

vector<string> CtrlModificaUsuari::consultaUsuari() {

	TxConsultaUsuari txConUsu;
	txConUsu.executar();

	vector<string> infoUsu;
	infoUsu.push_back(txConUsu.obteResultat()[0]);
	infoUsu.push_back(txConUsu.obteResultat()[1]);
	infoUsu.push_back(txConUsu.obteResultat()[2]);
	infoUsu.push_back(txConUsu.obteResultat()[3]);

	usuari = txConUsu.obteUsuari();

	return infoUsu;

}

void CtrlModificaUsuari::modificaUsuari(string nomU, string contraU, string correuU, string neixU){

	if (nomU != "") usuari.posaNom(nomU);
	if (contraU != "") usuari.posaContrasenya(contraU);
	if (correuU != "") usuari.posaCorreuElectronic(correuU);
	if (neixU != "") usuari.posaDataNaixement(neixU);

	if (nomU != "" or contraU != "" or correuU != "" or neixU != "") {

		usuari.modifica();
		Videoconsola v = Videoconsola::getInstance();
		v.refresca();

	}

}