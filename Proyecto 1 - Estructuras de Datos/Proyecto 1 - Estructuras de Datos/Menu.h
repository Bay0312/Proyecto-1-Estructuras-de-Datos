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

public:
	Menu();
	~Menu();

	void menuPrincipal();
	void menuMarcadores();
	void navegacionConTeclas();
	void irSitioWeb();
	void cargarSitios(std::string);
	SitioWeb* traeSitioWeb(std::string);
	void cambiarConfiguracion();
	bool leerOpcion(int&);
	void menuBusqueda();
	void gestionarSesion();
	void filtrarSitiosPorLetra();
	void buscarSitioPorPalabra();
	void guardarSesion();
	void recuperarSesion();
};

#endif // !MENU_H
