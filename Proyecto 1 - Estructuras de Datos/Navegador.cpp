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

void Navegador::guardar(std::ofstream& out) {
	out.write(reinterpret_cast<char*>(&modoIncognito), sizeof(modoIncognito));

	size_t numTabs = tabs.size();
	out.write(reinterpret_cast<char*>(&numTabs), sizeof(numTabs));
	for (auto tab : tabs) {
		tab->guardar(out);
	}

	size_t posTabActual = std::distance(tabs.begin(), iterActual);
	out.write(reinterpret_cast<char*>(&posTabActual), sizeof(posTabActual));

	size_t numMarcadores = marcadores.size();
	out.write(reinterpret_cast<char*>(&numMarcadores), sizeof(numMarcadores));
	for (auto marcador : marcadores) {
		marcador->guardar(out);
	}
}

Navegador* Navegador::recuperar(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&modoIncognito), sizeof(modoIncognito));

	size_t numTabs;
	in.read(reinterpret_cast<char*>(&numTabs), sizeof(numTabs));
	for (size_t i = 0; i < numTabs; ++i) {
		Tab* tab = new Tab();
		tab->recuperar(in);
		tabs.push_back(tab);
	}

	size_t posTabActual;
	in.read(reinterpret_cast<char*>(&posTabActual), sizeof(posTabActual));
	iterActual = tabs.begin();
	std::advance(iterActual, posTabActual);

	size_t numMarcadores;
	in.read(reinterpret_cast<char*>(&numMarcadores), sizeof(numMarcadores));
	for (size_t i = 0; i < numMarcadores; ++i) {
		Marcador* marcador = new Marcador();
		marcador->recuperar(in);
		marcadores.push_back(marcador);
	}

	return this;
}
