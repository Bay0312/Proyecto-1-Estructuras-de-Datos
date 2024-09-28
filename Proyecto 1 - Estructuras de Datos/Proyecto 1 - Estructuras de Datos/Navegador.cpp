#include "Navegador.h"

Navegador::Navegador() : tabs{ std::list<Tab*>() } {
	tabs.push_back(new Tab());
	iterActual = tabs.begin();
	marcadores.push_back(new Marcador());
	iterMarcadores = marcadores.begin();
}
Navegador::~Navegador() {
	for (Tab* tab : tabs) {
		delete tab;
	}
	for (Marcador* marcador : marcadores) {
		delete marcador;
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

void Navegador::agregarMarcador(SitioWeb* sitio) {
	if (sitio != nullptr) {
		std::vector<std::string> etiquetas;
		Marcador* marcador = new Marcador(sitio->getUrl(), sitio->getTitulo(), etiquetas);
		marcadores.push_back(marcador);
		++iterMarcadores;
	}
}

void Navegador::agregarEtiquetas(SitioWeb* sitio) {
	if (sitio != nullptr) {
		std::vector<std::string> etiquetas;
		std::string etiqueta;

		std::cout << "Ingrese etiquetas (digite . para terminar):" << std::endl;

		while (true) {
			std::cout << "Etiqueta: "; std::cin >> etiqueta;

			if (etiqueta == ".") {
				break;
			}

			if (!etiqueta.empty()) {
				etiquetas.push_back(etiqueta);
			}
		}

		(*iterMarcadores)->setEtiquetas(etiquetas);
	}
}

void Navegador::buscarMarcadores(std::string titulo) {
	for (iterMarcadores = marcadores.begin(); iterMarcadores != marcadores.end(); iterMarcadores++) {
		if ((*iterMarcadores)->getTitulo() == titulo) {
			std::cout << "\nMarcador encontrado: " << (*iterMarcadores)->toString() << std::endl;
			return;
		}
	}

	std::cout << "Marcador no encontrado con el título: \n";
}


std::string Navegador::toStringMarcadores() {
	std::stringstream s;
	int cont = 0;

	for (const auto& marcador : marcadores) {
		cont++;

		if (cont == 1) {
			continue;  // Omite la primera posición
		}

		if (marcador != nullptr) {
			s << marcador->toString() << "\n";
		}
	}

	return s.str();
}