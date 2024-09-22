#ifndef NAVEGADOR_H
#define NAVEGADOR_H
#include <list>
#include <vector>
#include "Tab.h"
#include "Marcador.h"
#include <iostream>

class Navegador {
private:
	std::list<Tab*> tabs;
	std::list<Tab*>::iterator iterActual;
	bool modoIncognito;
	std::list<Marcador*> marcadores;
	std::list<Marcador*>::iterator iterMarcadores;
	
public:
	Navegador();
	~Navegador();

	std::list<Tab*> getTabs();
	bool getModoIncognito();
	SitioWeb* getSitioActual();

	int numeroTab();
	void avanzarEnHistorial();
	void retrocederEnHistorial();

	std::string getNombreTab();
	void cambiarModoIncognito();

	std::string toStringSitios();

	void irSitio(SitioWeb*); 
	
	void nuevaTab();
	void cerrarTab();
	void avanzarEnTabs();
	void retrocederEnTabs();

	void agregarMarcador(SitioWeb*);
	void agregarEtiquetas(SitioWeb*);
	void buscarMarcadores(std::string);
	
	std::string toStringMarcadores();

	//Persistencia de datos
	void guardar(std::ofstream& out);
	Navegador* recuperar(std::ifstream& in);


};

#endif // !NAVEGADOR_H





