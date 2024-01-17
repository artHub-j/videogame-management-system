// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <iostream>

 std::string DBNAME;
 std::string USER;
 std::string PASSWORD;
 std::string HOSTADDR;
 std::string PORT;

 void loadConfig() {
     std::ifstream configFile("config.txt");
     if (configFile.is_open()) {
         std::string line;
         while (std::getline(configFile, line)) {
             // Analizar cada línea del archivo de configuración
             // Puedes implementar tu propia lógica de análisis aquí
             // Aquí hay un ejemplo básico:
             size_t equalsPos = line.find('=');
             if (equalsPos != std::string::npos) {
                 std::string key = line.substr(0, equalsPos);
                 std::string value = line.substr(equalsPos + 1);
                 // Asignar el valor a la variable correspondiente
                 if (key == "DBNAME") DBNAME = value;
                 else if (key == "USER") USER = value;
                 else if (key == "PASSWORD") PASSWORD = value;
                 else if (key == "HOSTADDR") HOSTADDR = value;
                 else if (key == "PORT") PORT = value;
             }
         }
         configFile.close();
     }
     else {
         std::cerr << "Error al abrir el archivo de configuración." << std::endl;
     }
 }

#endif // CONFIG_H