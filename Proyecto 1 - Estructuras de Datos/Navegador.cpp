#include "Navegador.h"

Navegador::Navegador() : tabs{ std::list<Tab*>() }, modoIncognito{ false }, marcadores{ std::list<Marcador*>() } {
	tabs.push_back(new Tab());
	iterActual = tabs.begin();
	marcadores.push_back(new Marcador());
	iterMarcadores = marcadores.begin();
}
Navegador::~Navegador() {
	for (Tab* tab : tabs) {
		delete tab;
	}
	for (auto marcador : marcadores) {
		delete marcador;
	}
	delete &marcadores;
}

std::list<Tab*> Navegador::getTabs() { return tabs; }
bool Navegador::getModoIncognito() { return modoIncognito; }
SitioWeb* Navegador::getSitioActual() { return (*iterActual)->getSitioActual(); }

void Navegador::avanzarEnHistorial() { (*iterActual)->avanzarEnHistorial(); }
void Navegador::retrocederEnHistorial() { (*iterActual)->retrocederEnHistorial(); }
int Navegador::numeroTab() { return std::distance(tabs.begin(), iterActual) + 1; }

std::string Navegador::getNombreTab() { return (*iterActual)->getNombre(); } 
void Navegador::cambiarModoIncognito() { modoIncognito = !modoIncognito; }

std::string Navegador::toStringSitios() { return (*iterActual)->toString(); }

void Navegador::irSitio(SitioWeb* sitio) {
	if (sitio != nullptr) {
		(*iterActual)->irSitio(sitio);
	}
	else {
		(*iterActual)->irSitio(new SitioWeb("404", "Not Found", "404"));
	}
}

void Navegador::nuevaTab() {
	tabs.push_back(new Tab());
	++iterActual; //Se mueve al nuevo tab
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
		std::list<std::string> etiquetas;
		Marcador* marcador = new Marcador(sitio->getUrl(), sitio->getTitulo(), etiquetas);
		marcadores.push_back(marcador);
		++iterMarcadores;
	}
}

void Navegador::agregarEtiquetas(SitioWeb* sitio) {
	if (sitio != nullptr) {
		std::list<std::string> etiquetas;
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

void Navegador::guardar(std::fstream& strm) {
	// Guardar si el navegador está en modo incognito
	strm << modoIncognito << SEPARA_VALOR;
	strm << tabs.size() << SEPARA_VALOR;

	for (auto tab : tabs) {
		tab->guardar(strm);
	}

	auto posTabActual = std::distance(tabs.begin(), iterActual);
	strm << posTabActual << SEPARA_VALOR;

	strm << marcadores.size() << SEPARA_VALOR;
	for (auto marcador : marcadores) {
		marcador->guardar(strm);
	}
	strm << SEPARA_REGISTRO;
}

Navegador* Navegador::recuperar(std::fstream& strm) {
	// Recuperar modo incognito
	strm >> modoIncognito;
	strm.ignore(1); // Ignorar el separador

	size_t numTabs;
	strm >> numTabs;
	strm.ignore(1); // Ignorar el separador

	for (size_t i = 0; i < numTabs; ++i) {
		Tab* tab = new Tab();
		tab->recuperar(strm);
		tabs.push_back(tab);
	}

	size_t posTabActual;
	strm >> posTabActual;
	strm.ignore(1); // Ignorar el separador
	iterActual = tabs.begin();
	std::advance(iterActual, posTabActual);

	// Recuperar los marcadores
	size_t numMarcadores;
	strm >> numMarcadores;
	strm.ignore(1); // Ignorar el separador

	for (size_t i = 0; i < numMarcadores; ++i) {
		Marcador* marcador = new Marcador();
		marcador->recuperar(strm);
		marcadores.push_back(marcador);
	}

	return this;
}
