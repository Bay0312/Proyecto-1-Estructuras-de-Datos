#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Navegador.h"

class Menu {
private:
	Navegador* navegador;
	std::map<std::string, SitioWeb*> sitiosDisponibles;
	//std::vector<SitioWeb*> sitiosDisponibles;

public:
	Menu();
	~Menu();

	void menuPrincipal();
	void irSitioWeb();
	void cargarSitios(std::string);
	SitioWeb* traeSitioWeb(std::string);
	void cambiarConfiguracion();
};

#endif // !MENU_H
