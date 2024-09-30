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


std::list<Tab*>& Navegador::gettTabs() {	return tabs;}
void Navegador::setTabActual(std::list<Tab*>::iterator nuevoIter) {	iterActual = nuevoIter;}
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
		std::list<Tab*>::iterator aux = iterActual;

		// Si el iterador actual está en la primera posición
		if (iterActual == tabs.begin()) {
			++iterActual;  // Avanzamos al siguiente elemento
		}
		else {
			--iterActual;  // Retrocedemos al anterior elemento
		}

		delete* aux;
		tabs.erase(aux);
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

void Navegador::guardar(std::ofstream& out) {
	size_t numTabs = tabs.size();
	out.write(reinterpret_cast<char*>(&numTabs), sizeof(numTabs));

	for (Tab* tab : tabs) {
		tab->guardar(out); 
	}

	int indexTabActual = std::distance(tabs.begin(), iterActual);
	out.write(reinterpret_cast<char*>(&indexTabActual), sizeof(indexTabActual));

	size_t numMarcadores = marcadores.size();
	out.write(reinterpret_cast<char*>(&numMarcadores), sizeof(numMarcadores));
	for (Marcador* marcador : marcadores) {
		marcador->guardar(out);
	}

	int indexMarcadorActual = std::distance(marcadores.begin(), iterMarcadores);
	out.write(reinterpret_cast<char*>(&indexMarcadorActual), sizeof(indexMarcadorActual));
}

Navegador* Navegador::recuperar(std::ifstream& in) {
	size_t numTabs;
	in.read(reinterpret_cast<char*>(&numTabs), sizeof(numTabs));

	if (numTabs > 0) {
		// Eliminar la pestaña vacía que se creó por defecto
		if (!tabs.empty()) {
			delete* tabs.begin(); 
			tabs.erase(tabs.begin());
		}

		for (size_t i = 0; i < numTabs; ++i) {
			Tab* tab = new Tab();
			tab->recuperar(in);  // Método recuperar dentro de la clase Tab
			tabs.push_back(tab);
		}
	}

	int indexTabActual;
	in.read(reinterpret_cast<char*>(&indexTabActual), sizeof(indexTabActual));
	iterActual = std::next(tabs.begin(), indexTabActual);

	size_t numMarcadores;
	in.read(reinterpret_cast<char*>(&numMarcadores), sizeof(numMarcadores));

	for (size_t i = 0; i < numMarcadores; ++i) {
		Marcador* marcador = new Marcador();
		marcador->recuperar(in); 
		marcadores.push_back(marcador);
	}	

	int indexMarcadorActual;
	in.read(reinterpret_cast<char*>(&indexMarcadorActual), sizeof(indexMarcadorActual));
	iterMarcadores = std::next(marcadores.begin(), indexMarcadorActual);

	return this;
}
