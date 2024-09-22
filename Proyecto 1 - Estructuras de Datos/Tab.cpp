#include "Tab.h"
#include "Navegador.h"

Tab::Tab() : historial{ new Historial() }, nombre{ "Tab Nuevo" }, iterActual{ historial->getVisitados().end() } {}
Tab::~Tab() { delete historial; }


std::string Tab::getNombre() {
	return nombre;
}

SitioWeb* Tab::getSitioActual() {
	if (historial->getVisitados().size() != 0) {
		return *iterActual;
	}
	return nullptr;
}

void Tab::irSitio(SitioWeb* sitio) {
	SitioWeb* nuevo = new SitioWeb(sitio->getUrl(), sitio->getTitulo(), sitio->getDominio());

	//Si no estamos en el primer sitio significa que volvimos, por lo que, si tratamos de ir a un nuevo sitio, borramos los sitios que estan adelante, igual que lo hace un navegador real.
	if (historial->getVisitados().size() != 0) {
		if (iterActual != historial->getVisitados().begin()) {
			for (auto it = historial->getVisitados().begin(); it != iterActual; ++it) {
				delete* it;
			}
			historial->getVisitados().erase(historial->getVisitados().begin(), iterActual);
		}
	}
	historial->agregarSitio(nuevo);
	iterActual = historial->getVisitados().begin();
	
}

void Tab::avanzarEnHistorial() {
	if (iterActual != historial->getVisitados().begin()) {
		--iterActual;
	}
}
//Retroceder y avanzar estan invertidos con el "++" y "--" porque se inserta al frente en el historial.
void Tab::retrocederEnHistorial() {
	if (iterActual != (historial->getVisitados().end() - 1)) {
		++iterActual;
	}
}

SitioWeb* Tab::getActual() {
	return *iterActual;
}

SitioWeb* Tab::getVisitadosPorPos(int pos) {
	return historial->getVisitadosPorPos(pos);
}

//void Tab::cambiaModoIncognito() { modoIncognito = !modoIncognito; }

std::string Tab::toString() {
	return historial->toString();
}

void Tab::guardar(std::ofstream& out) {
	size_t nombreSize = nombre.size();
	out.write(reinterpret_cast<char*>(&nombreSize), sizeof(nombreSize));
	out.write(nombre.data(), nombreSize);

	historial->guardar(out);

	size_t posActual = std::distance(historial->getVisitados().begin(), iterActual);
	out.write(reinterpret_cast<char*>(&posActual), sizeof(posActual));
}

Tab* Tab::recuperar(std::ifstream& in) {
	size_t nombreSize;
	in.read(reinterpret_cast<char*>(&nombreSize), sizeof(nombreSize));
	nombre.resize(nombreSize);
	in.read(&nombre[0], nombreSize);

	historial = new Historial();
	historial->recuperar(in);

	size_t posActual;
	in.read(reinterpret_cast<char*>(&posActual), sizeof(posActual));
	iterActual = historial->getVisitados().begin();
	std::advance(iterActual, posActual);

	return this;
}

