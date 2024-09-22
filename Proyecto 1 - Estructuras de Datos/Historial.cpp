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

void Historial::guardar(std::ofstream& out) {
    size_t numSitios = visitados.size();
    out.write(reinterpret_cast<char*>(&numSitios), sizeof(numSitios));

    for (auto sitio : visitados) {
        sitio->guardar(out);
    }
}

Historial* Historial::recuperar(std::ifstream& in) {
    size_t numSitios;
    in.read(reinterpret_cast<char*>(&numSitios), sizeof(numSitios));

    for (size_t i = 0; i < numSitios; ++i) {
        SitioWeb* sitio = new SitioWeb();
        sitio->recuperar(strm);
        visitados.push_back(sitio);
    }

    return this;
}

