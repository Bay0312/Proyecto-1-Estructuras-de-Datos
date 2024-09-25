#ifndef NAVEGADOR_H
#define NAVEGADOR_H
#include <list>
#include <vector>
#include "Tab.h"
#include "Marcador.h"


class Navegador {
private:
	std::list<Tab*> tabs;
	std::list<Tab*>::iterator iterActual;
	std::list<Marcador*> marcadores;
	std::list<Marcador*>::iterator iterMarcadores;
	
public:
	Navegador();
	~Navegador();

	std::list<Tab*> getTabs();
	bool getModoIncognitoTabActual();
	SitioWeb* getSitioActual();

	int numeroTab();
	void avanzarEnHistorial();
	void retrocederEnHistorial();

	std::string getNombreTab();
	void cambiarModoIncognitoTabActual();

	void irSitio(SitioWeb*); 
	
	void nuevaTab();
	void cerrarTab();
	void avanzarEnTabs();
	void retrocederEnTabs();
	
	void agregarMarcador(SitioWeb*);
	void agregarEtiquetas(SitioWeb*);
	void buscarMarcadores(std::string);

	std::string toStringMarcadores();



};

#endif // !NAVEGADOR_H





