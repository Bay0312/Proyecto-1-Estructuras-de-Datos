#include "Navegador.h"

Navegador::Navegador() : tabs{ std::list<Tab*>() } {
	tabs.push_back(new Tab());
	iterActual = tabs.begin();
}
Navegador::~Navegador() {
	for (Tab* tab : tabs) {
		delete tab;
	}
	Configuracion::destruirInstancia();  
}

std::list<Tab*> Navegador::getTabs() { return tabs; }
bool Navegador::getModoIncognitoTabActual() { return (*iterActual)->getModoIncognito(); }
SitioWeb* Navegador::getSitioActual() { return (*iterActual)->getSitioActual(); }
void Navegador::avanzarEnHistorial() { (*iterActual)->avanzarEnHistorial(); }
void Navegador::retrocederEnHistorial() { (*iterActual)->retrocederEnHistorial(); }
int Navegador::numeroTab() { return std::distance(tabs.begin(), iterActual) + 1; }

std::string Navegador::getNombreTab() { return (*iterActual)->getNombre(); } 
void Navegador::cambiarModoIncognitoTabActual() { (*iterActual)->cambiaModoIncognito(); }

void Navegador::irSitio(SitioWeb* sitio) {
	try {
		if (sitio != nullptr) (*iterActual)->irSitio(new SitioWeb(sitio->getUrl(), sitio->getDominio(), sitio->getTitulo()));
		else (*iterActual)->irSitio(new SitioWeb("404", "404", "Not Found"));
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Error de memoria al intentar crear el SitioWeb para pagina abierta: " << e.what() << std::endl;
		return;
	}
	
	
}

void Navegador::nuevaTab() {
	try {
		tabs.push_back(new Tab());
		++iterActual; //Se mueve al nuevo tab
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Error de memoria al intentar crear una pestaña nueva: " << e.what() << std::endl;
		return;
	}
}

void Navegador::cerrarTab() {
	if (tabs.size() > 1) {
		std::list<Tab*>::iterator aux = std::prev(iterActual);
		delete* iterActual;
		iterActual = tabs.erase(iterActual);
		iterActual = aux;
	}
}

void Navegador::avanzarEnTabs() {
	if (iterActual != (--tabs.end())) {
		++iterActual;
	}
}

void Navegador::retrocederEnTabs() {
	if (iterActual != tabs.begin()) {
		--iterActual;
	}
}