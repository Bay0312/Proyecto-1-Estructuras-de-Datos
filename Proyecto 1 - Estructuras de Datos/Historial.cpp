#include "Historial.h"

Historial::Historial() : visitados{ std::deque<SitioWeb*>() } {}
Historial::~Historial() {
	for (auto sitio : visitados) {
		delete sitio;
	}
}

std::deque<SitioWeb*>& Historial::getVisitados() { return visitados; }

SitioWeb* Historial::getVisitadosPorPos(int pos) {
	return visitados[pos];
}

void Historial::agregarSitio(SitioWeb* sitio) { visitados.push_front(sitio); }

std::string Historial::toString() {
	std::string str = "";
	for (auto sitio : visitados) {
		str += sitio->toString() + "\n";
	}
	return str;
}

void Historial::guardar(std::fstream& strm) {
    strm << visitados.size() << SEPARA_VALOR;

    // Guardar cada sitio web
    for (auto sitio : visitados) {
        sitio->guardar(strm);
    }
    strm << SEPARA_REGISTRO;
}

Historial* Historial::recuperar(std::fstream& strm) {
    size_t numSitios;
    strm >> numSitios;
    strm.ignore(1); // Ignorar el separador

    for (size_t i = 0; i < numSitios; ++i) {
        SitioWeb* sitio = new SitioWeb();
        sitio->recuperar(strm);
        visitados.push_back(sitio);
    }

    return this;
}
