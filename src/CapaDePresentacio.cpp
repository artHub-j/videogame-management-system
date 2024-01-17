#include <iostream>
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include <sstream>
#include "TxIniciSessio.cpp"
#include "TxTancaSessio.cpp"
#include "TxRegistraUsuari.cpp"
#include "TxConsultaUsuari.cpp"
#include "TxInfoCompres.cpp"
#include "CtrlModificaUsuari.cpp"
#include "TxEsborraUsuari.cpp"
#include "TxConsultaCompres.cpp"
#include "TxConsultaVideojoc.cpp"
#include "TxCompraVideojoc.cpp"
#include "TxCompraPaquet.cpp"
#include "TxConsultaVideojocs.cpp"
#include "TxConsultaVideojocsEdat.cpp"
#include "TxConsultaPaquets.cpp"
#include "TxConsultaPaquet.cpp"
#include "TxConsultaNovetatsVideojocs.cpp"

using namespace std;

std::string formatDate(const std::string& inputDate) {
    // Create an input string stream to parse the input date
    std::istringstream dateStream(inputDate);

    // Variables to store day, month, and year
    int day, month, year;

    // Parse the input date
    char delimiter;
    dateStream >> day >> delimiter >> month >> delimiter >> year;

    // Create an output string stream to format the date
    std::ostringstream formattedDate;

    // Format the date
    formattedDate << year << '-' << std::setw(2) << std::setfill('0') << month << '-'
        << std::setw(2) << std::setfill('0') << day;

    // Get the formatted date as a string
    return formattedDate.str();
}

class CapaDePresentacio
{
public:
    CapaDePresentacio();

    void iniciSessio();

    void tancaSessio();

    void registrarUsuari();

    void consultaUsuari();

    void modificaUsuari();

    void esborraUsuari();

    void comprarVideojoc();

    void consultaCompres();

    void comprarPaquetVideojoc();

    void consultaVideojoc();

    void consultaVideojocs();

    void consultaVideojocsEdat();

    void consultaPaquets();

    void consultaPaquet();

    void consultaNovetatsVideojocs();
};

CapaDePresentacio::CapaDePresentacio() {

}

void CapaDePresentacio::iniciSessio() {
    //TITOL
    cout << "\n** Inici Sessio **";

    //OPCIONS
    string sU, cU;
    cout << "\nSobrenom: ";
    cin >> sU;
    cout << "Contrasenya: ";
    cin >> cU;

    try {
        TXIniciSessio txinis(sU, cU);
        txinis.executar();
        system("CLS");
        cout << "Sessio iniciada correctament!" << endl;
    }
    catch (int e) {
        if (e == ErrorContrasenya or e == UsuariNoExisteix) {
            cout << "Hi ha hagut un error amb el sobrenom o la contrasenya" << endl;
            exit(0);
        }

    }
}

void CapaDePresentacio::tancaSessio() {
    char op;
    cout << "vols tancar la sessio? [S/N]" << endl;
    cin >> op;
    if (op == 'S') {
        TXTancaSessio txtses;
        txtses.executar();
        cout << "Sessio tancada correctament" << endl;
    }
}

void CapaDePresentacio::registrarUsuari() {
    //TITOL
    cout << "Registar usuari " << endl;
    cout << "Omplir la informacio que es demana ..." << endl;
    string nU, sU, cU, ceU, dnU;
    //OPCIONS
    cout << "Nom complet: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(std::cin, nU);
    cout << "Sobrenom: ";
    cin >> sU;
    cout << "Contrasenya: ";
    cin >> cU;
    cout << "Correu electronic: ";
    cin >> ceU;
    cout << "Data naixement (DD/MM/AAAA): ";
    cin >> dnU;

    dnU = formatDate(dnU);

    try {
        TxRegistraUsuari txRU(nU, sU, cU, ceU, dnU);
        txRU.executar();
        cout << "Usuari registrat amb exit" << endl;
    }
    catch (int e) {
        if (e == SobrenomExisteix) {
            cout << "Ja existeix un usuari amb aquest sobrenom" << endl;
        }
        else if (e == CorreuExisteix) {
            cout << "Ja existeix un usuari amb aquest correu electronic" << endl;
        }
    }
    //cout << "\nNou usuari registat correctament!\n";
}

void CapaDePresentacio::consultaUsuari() {

    TxConsultaUsuari txConUsu;
    txConUsu.executar();

    cout << "** Consulta usuari **\n";
    cout << "Nom complet: " + txConUsu.obteResultat()[0] << endl;
    cout << "Sobrenom: " + txConUsu.obteResultat()[1] << endl;
    cout << "Correu electronic: " + txConUsu.obteResultat()[2] << endl;
    cout << "Data naixement (DD/MM/AAAA): " + txConUsu.obteResultat()[3] << endl;

    TxInfoCompres txInfoComp;
    txInfoComp.executar();

    cout << txInfoComp.obteResultat()[1] << " videojocs comprats\n"
        << txInfoComp.obteResultat()[0] << " paquet de videojocs comprats\n"
        << fixed << setprecision(2) << txInfoComp.obteResultat()[2] << " euros gastats en total\n";

}

void CapaDePresentacio::modificaUsuari() {

    CtrlModificaUsuari ctrlModUsu;

    vector<string> infoU;
    infoU = ctrlModUsu.consultaUsuari();

    cout << "** Modifica usuari **\n";
    cout << "Nom complet: " << infoU[0] << endl;
    cout << "Sobrenom: " << infoU[1] << endl;
    cout << "Correu electronic: " << infoU[2] << endl;
    cout << "Data naixement (DD/MM/AAAA): " << infoU[3] << endl;

    string nomU = "", contraU = "", correuU = "", neixU = "";

    cout << "\nomplir la informacio que es vol modificar..." << endl;
    cout << "Nom complet: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(std::cin, nomU);
    cout << "Contrasenya: ";
    cin >> contraU;
    cout << "Correu electronic: ";
    cin >> correuU;
    cout << "Data naixement (DD/MM/AAAA): ";
    cin >> neixU;

    try {
        ctrlModUsu.modificaUsuari(nomU, contraU, correuU, neixU);

        vector<string> infoU;
        infoU = ctrlModUsu.consultaUsuari();

        cout << "\n** Dades usuari modificades **\n";
        cout << "Nom complet: " << infoU[0] << endl;
        cout << "Sobrenom: " << infoU[1] << endl;
        cout << "Correu electronic: " << infoU[2] << endl;
        cout << "Data naixement (DD/MM/AAAA): " << infoU[3] << endl;

    }
    catch (int e) {
        if (e == CorreuExisteix) {
            cout << "Ja existeix un usuari amb aquest correu electronic" << endl;
        }
    }
}

void CapaDePresentacio::esborraUsuari() {

    string contrasenya;
    cout << " Esborrar usuari \n";
    cout << "Per confirmar l'esborrat, s'ha d'entrar la contrasenya...\n"
        << "Contrasenya: ";
    cin >> contrasenya;
    
    try {

        TxEsborraUsuari txEsbUsu(contrasenya);
        txEsbUsu.executar();
        cout << "L'usuari s'ha esborrat correctament." << endl;
        exit(0);
    }
    catch (int e) {

        if (e == ErrorContrasenya) cout << "La contrasenya no es correcta, l'usuari no s'ha esborrat." << endl;

    }


}

void CapaDePresentacio::comprarVideojoc() {

    string videojoc;
    cout << "* Comprar videojoc *\n";
    cout << "Nom videojoc: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(std::cin, videojoc);
    try {
        TxCompraVideojoc txCompVid(videojoc);

        txCompVid.executar();
        vector<string> infoVjoc;
        infoVjoc = txCompVid.obteResultat();
        cout << "Informacio videojoc...\n";
        cout << "Nom videojoc: " + infoVjoc[0] << endl;
        cout << "Descripcio: " + infoVjoc[4] << endl;
        cout << "Qualificacio Edat: " + infoVjoc[2] << endl;
        cout << "Genere: " + infoVjoc[1] << endl;
        cout << "Data llancament: " + infoVjoc[3] << endl;
        cout << "Preu: " + infoVjoc[5] << endl;
        string op;
        cout << "Vols continuar amb la compra (S/N): ";
        cin >> op;
        if (op == "S" or op == "s") {
            txCompVid.comprar();
            const int TIME_STRING_SIZE = 26;
            char currentTimeString[TIME_STRING_SIZE];
            // Obtener la hora actual
            std::time_t currentTime = std::time(nullptr);

            // Convertir la hora actual a una cadena de tiempo de forma segura
            ctime_s(currentTimeString, TIME_STRING_SIZE, &currentTime);
            cout << "Compra registrada: " << currentTimeString << endl;

            // Mostrar los videojuegos relacionados
            cout << "Jocs relacionats:" << endl;

            for (int i = 6; i < infoVjoc.size(); i++) cout << infoVjoc[i];

        }
        else system("CLS");
    }

    catch (int e) {
        system("CLS");
        if (e == VideojocNoExisteix) cout << "El videojoc introduit no existeix" << endl;
        if (e == CompraExistent) cout << "Ya tens aquest videojoc comprat!" << endl;
        if (e == EdatInapropiada) cout << "No tens la edat minima per a poder comprar aquest videojoc" << endl;
    }
}

void CapaDePresentacio::comprarPaquetVideojoc() {

    string paquet;
    cout << "* Comprar paquet *\n";
    cout << "Nom paquet: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(std::cin, paquet);

    try {
        //mostra informacio paquet
        TxCompraPaquet txCompPaquet(paquet);
        txCompPaquet.executar();
        pair<vector<string>, vector<string>> infoPaquet;
        infoPaquet = txCompPaquet.obteResultat();
        cout << "Informacio paquet..." << endl;
        cout << "Nom paquet: " << infoPaquet.first[0] << endl;
        cout << "Descripcio: " << infoPaquet.first[1] << endl;
        cout << "Preu: " << infoPaquet.first[2];
        cout << " (estalvi de " << infoPaquet.first[3] << " euros)" << endl;

        //mostra informacio videojocs del paquet
        cout << "\n Jocs inclosos:" << endl;
        for (int i = 0; i < infoPaquet.second.size(); i++) {
            cout << infoPaquet.second[i];
        }

        string op;
        cout << "Vols continuar amb la compra (S/N): ";
        cin >> op;
        if (op == "S" or op == "s") {
            txCompPaquet.comprar();
            const int TIME_STRING_SIZE = 26;
            char currentTimeString[TIME_STRING_SIZE];
            // Obtener la hora actual
            std::time_t currentTime = std::time(nullptr);

            // Convertir la hora actual a una cadena de tiempo de forma segura
            ctime_s(currentTimeString, TIME_STRING_SIZE, &currentTime);
            cout << "Compra registrada: " << currentTimeString << endl;
        }
        else system("CLS");

    }

    catch (int e) {
        system("CLS");
        if (e == PaquetNoExixtent) cout << "El paquet introduit no existeix" << endl;
        if (e == CompraExistent) cout << "Ya tens aquest paquet comprat!" << endl;
        if (e == EdatInapropiadaPaquet) cout << "No tens la edad necessaria per a poder comprar aquest paquet de videojocs" << endl; //RIT9
    }
}

void CapaDePresentacio::consultaCompres() {

    cout << "** Consulta compres **\n";

    TxConsultaCompres txConComp;
    txConComp.executar();
    vector< vector<string> > infoCompres = txConComp.obteResultat();

    for (int i = 0; i < infoCompres.size(); i++) {

        for (int j = 0; j < infoCompres[i].size(); j++) {

            cout << infoCompres[i][j];

            //if (j == 0) cout << ": ";
            //else cout << "; ";
        }
        //cout << endl;
    }

}

void CapaDePresentacio::consultaVideojoc() {

    string videojoc = "";
    cout << "* Consultar videojoc *\n";
    cout << "Nom videojoc: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(std::cin, videojoc);
    
    TxConsultaVideojoc txConsVid(videojoc);

    try { 
        txConsVid.executar(); 
    
        vector<string> infoVjoc;
        infoVjoc = txConsVid.obteResultat();
        cout << "Informacio videojoc...\n";
        cout << "Nom videojoc: " + infoVjoc[0] << endl;
        cout << "Descripcio: " + infoVjoc[4] << endl;
        cout << "Qualificacio Edat: " + infoVjoc[1] << endl;
        cout << "Genere: " + infoVjoc[2] << endl;
        cout << "Data llancament: " + infoVjoc[3] << endl;
        cout << "Preu: " + infoVjoc[5] << endl;

        cout << "Paquets on esta inclos: ";

        if (infoVjoc.size() == 6) cout << "Aquest videojoc no esta inclos en cap paquet";

        for (int i = 6; i < infoVjoc.size(); i++) {

            cout << infoVjoc[i] << ", ";
            if ((i != infoVjoc.size()) - 1) cout << ", ";

        }
    
    } catch (int e) { 
        if (e == VideojocNoExisteix) cout << "El videojoc no existeix."; 
    }
}

void CapaDePresentacio::consultaVideojocs() {
    cout << "* Informacio de tots els videojocs *\n";

    TxConsultaVideojocs txConsVid;

    txConsVid.executar();

    vector<vector<string>> infoVjoc = txConsVid.obteResultat();

    for (int i = 0; i < infoVjoc.size(); i++) {

        cout << "Informacio videojoc...\n";
        cout << "Nom videojoc: " + infoVjoc[i][0] << endl;
        cout << "Descripcio: " + infoVjoc[i][1] << endl;
        cout << "Qualificacio Edat: " + infoVjoc[i][2] << endl;
        cout << "Genere: " + infoVjoc[i][3] << endl;
        cout << "Data llancament: " + infoVjoc[i][4] << endl;
        cout << "Preu: " + infoVjoc[i][5] << endl;
        cout << "Paquets on esta inclos: ";

        if (infoVjoc[i].size() == 6) cout << "Aquest videojoc no esta inclos en cap paquet";

        for (int j = 6; j < infoVjoc[i].size(); j++) {
            cout << infoVjoc[i][j] << ", ";
        }
        cout << endl << endl;
    }

}

void CapaDePresentacio::consultaVideojocsEdat() {

    cout << "** Consulta videojocs per edat **" << endl;
    cout << "Edat maxima (anys): ";
    int edat;
    cin >> edat;

    TxConsultaVideojocsEdat txConsVidEdat(edat);
    txConsVidEdat.executar();


    vector<vector<string>> infoVjoc = txConsVidEdat.obteResultat();

    for (int i = 0; i < infoVjoc.size(); i++) {

        cout << "Nom videojoc: " + infoVjoc[i][0] << "; ";
        cout << "Descripcio: " + infoVjoc[i][1] << "; ";
        cout << "Qualificacio Edat: " + infoVjoc[i][2] << "; ";
        cout << "Genere: " + infoVjoc[i][3] << "; ";
        cout << "Data llancament: " + infoVjoc[i][4] << "; ";
        cout << "Preu: " + infoVjoc[i][5] << "; ";
        cout << "Paquets on esta inclos: ";

        if (infoVjoc[i].size() == 6) cout << "Aquest videojoc no esta inclos en cap paquet";

        for (int j = 6; j < infoVjoc[i].size(); j++) {
            cout << infoVjoc[i][j] << ", ";
        }
        cout << endl;
    }
}

void CapaDePresentacio::consultaPaquets() {
    cout << "** Consulta Paquets **" << endl;
    TxConsultaPaquets txConsPaquets;
    txConsPaquets.executar();

    vector<vector<string>> infoPaquets = txConsPaquets.obteResultat();
    for (int i = 0; i < infoPaquets.size(); i++) {

        cout << infoPaquets[i][0] << "; ";
        cout << infoPaquets[i][1] << "; ";
        cout << infoPaquets[i][2] << " euros ";
        cout << "(estalvi " + infoPaquets[i][3] << " euros) " << endl;
    }
}


void CapaDePresentacio::consultaPaquet() {
    cout << "** Consulta Paquet **" << endl;
    cout << "Nom Paquet: ";
    string nomP;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getline(std::cin, nomP);

    try {
        //mostra informacio paquet
        TxConsultaPaquet txConsPaquet(nomP);
        txConsPaquet.executar();
        pair<vector<string>, vector<string>> infoPaquet;
        infoPaquet = txConsPaquet.obteResultat();

        cout << "Informacio paquet..." << endl;
        cout << "Nom paquet: " << infoPaquet.first[0] << endl;
        cout << "Descripcio: " << infoPaquet.first[1] << endl;
        cout << "Preu: " << infoPaquet.first[2];
        cout << " (estalvi de " << infoPaquet.first[3] << " euros)" << endl;

        //mostra informacio videojocs del paquet
        cout << "\nJocs inclosos:" << endl;
        for (int i = 0; i < infoPaquet.second.size(); i++) {
            cout << infoPaquet.second[i];
        }
    }
    catch (int e) {
        if (e == ElementNoExisteix) cout << "El paquet introduit no existeix" << endl;
    }
}

void CapaDePresentacio::consultaNovetatsVideojocs() {

    string data;
    cout << "** Consulta novetats **\n";
    cout << "Data (DD/MM/AAAA): ";
    cin >> data;
    data = formatDate(data);

    TxConsultaNovetatsVideojocs txConNov(data);
    txConNov.executar();

    vector<vector<string>> infoVjoc = txConNov.obteResultat();

    for (int i = 0; i < infoVjoc.size(); i++) {

        cout << infoVjoc[i][0] << "; ";
        cout << infoVjoc[i][1] << "; ";
        cout << infoVjoc[i][2] << "; ";
        cout << infoVjoc[i][3] << "; ";
        cout << infoVjoc[i][4] << "; ";
        cout << infoVjoc[i][5] << "; ";

        if (infoVjoc[i].size() != 6) {
            cout << "Paquets: ";
            for (int j = 6; j < infoVjoc[i].size(); j++) {
                cout << infoVjoc[i][j] << ", ";
            }
        }
        cout << endl;
    }

}