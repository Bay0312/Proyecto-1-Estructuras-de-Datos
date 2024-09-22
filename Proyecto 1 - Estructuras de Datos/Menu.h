#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Navegador.h"
#include "Configuracion.h"

class Menu {
private:
	Navegador* navegador;
	std::map<std::string, SitioWeb*> sitiosDisponibles;
	//std::vector<SitioWeb*> sitiosDisponibles;

public:
	Menu();
	~Menu();

	void menuPrincipal();
	void menuMarcadores();
	void navegacionConTeclas();
	void irSitioWeb();
	void cargarSitios(std::string);
	void cambiarConfiguracion();
	SitioWeb* traeSitioWeb(std::string);

	//Persistencia
	void guardarDatos();
	void cargarDatos();
};

#endif // !MENU_H
