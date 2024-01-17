#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "CapaDePresentacio.cpp"
#include <fstream>
#include <unordered_map>
#include "config.h"

using namespace std;





void menu_principal()
{
    //TITOL
    cout << "\n******************\n  Menu Principal  \n******************\n";

    //OPCIONS
    cout << "1. Iniciar sessio\n2. Registar usuari\n3. Sortir\n";
    cout << "Opcio: ";
}

void menu_usuari_iniciat()
{
    int op;
    //TITOL
    cout << "\n******************\n  Menu Principal  \n******************\n";
    //OPCIONS
    cout << "1. Gestionar usuari\n2. Gestionar compres\n3. Consultar\n";
    cout << "4. Tancar sessio\n5. Sortir\n";

    cout << "Opcio: ";


}

void menu_gestionar_usuari() {
    
    //TITOL
    cout << "---------------------------" << endl;
    cout << "     Gestionar usuari" << endl;
    cout << "---------------------------" << endl;

    //OPCIONS
    cout << "1. Consultar usuari\n2. Modificar usuari\n";
    cout << "3. Esborrar usuari\n4. Tornar\n";
    cout << "Opcio: ";

}


int main() {

    loadConfig();
 
    Transaccio tx();
    CapaDePresentacio cp;
    string sU, cU;
    bool continuar = true;
    bool continuarMenuIniciat = true;
    while (continuar) {
        int op;
        menu_principal();
        cin >> op;
        if (op == 1) {
            system("CLS");
            cp.iniciSessio();
            while (continuarMenuIniciat) {
                menu_usuari_iniciat();
                cin >> op;
                switch (op) {
                case 1: //GESTIO USUARI
                    system("CLS");
                    menu_gestionar_usuari();
                    cin >> op;
                    switch (op) {
                    case 1:
                        system("CLS");
                        cp.consultaUsuari();
                        break;
                    case 2:
                        system("CLS");
                        cp.modificaUsuari();
                        break;
                    case 3:
                        system("CLS");
                        cp.esborraUsuari();
                        continuarMenuIniciat = false;
                        break;
                    case 4:
                        system("CLS");
                        break;
                    }
                    break;
                case 2: //GESTIO COMPRES
                    system("CLS");
                    cout << "---------------------------" << endl;
                    cout << "     Gestionar compres" << endl;
                    cout << "---------------------------" << endl;
                    cout << "1. Comprar videojoc\n2. Comprar paquet videojocs" << endl;
                    cout << "3. Consultar compres\n4. Tornar" << endl;
                    cout << "Opcio: ";
                    cin >> op;
                    switch (op) {
                    case 1:
                        system("CLS");
                        cp.comprarVideojoc();
                        break;
                    case 2:
                        system("CLS");
                        cp.comprarPaquetVideojoc();
                        break;
                    case 3:
                        system("CLS");
                        cp.consultaCompres();
                        break;
                    case 4:
                        system("CLS");
                        break;
                    }
                    break;
                case 3: //CONSULTAR
                    system("CLS");
                    cout << "------------------------\n      ConsultesVideojocs\n";
                    cout << "------------------------\n";
                    cout << "1. Consultar videojoc\n2. Consultar videojocs\n";
                    cout << "3. Consultar videojocs per edat\n4. Consultar novetats videojocs\n";
                    cout << "5. Consultar paquet videojocs\n6. Consultar paquets videojocs\n";
                    cout << "7. Tornar\n";
                    cout << "Opcio: ";
                    cin >> op;
                    switch (op) {
                    case 1:
                        system("CLS");
                        cp.consultaVideojoc();
                        break;
                    case 2:
                        system("CLS");
                        cp.consultaVideojocs();
                        break;
                    case 3:
                        system("CLS");
                        cp.consultaVideojocsEdat();
                        break;
                    case 4:
                        system("CLS");
                        cp.consultaNovetatsVideojocs();
                        break;
                    case 5:
                        system("CLS");
                        cp.consultaPaquet();
                        break;
                    case 6:
                        system("CLS");
                        cp.consultaPaquets();
                        break;
                    case 7:
                        system("CLS");
                        break;
                    }
                    break;
                case 4: // TANCA SESSIO
                    system("CLS");
                    cp.tancaSessio();
                    exit(0);
                    break;
                case 5: // SORTIR
                    system("CLS");
                    exit(0);
                    break;
                }
            }
        }
        else if (op == 2) {
            system("CLS");
            cp.registrarUsuari();
        }
        else if (op == 3) {
            continuar = false;
        }
    }
    return 0;
}
