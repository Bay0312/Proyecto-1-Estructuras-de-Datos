#include "Marcador.h"

Marcador::Marcador() : url{ "" }, titulo{ "" }, etiquetas{ std::list<std::string>() } {}
Marcador::Marcador(std::string url, std::string titulo, std::list<std::string> etiquetas) : url{ url }, titulo{ titulo }, etiquetas{ etiquetas } {}

std::string Marcador::getUrl() { return url; }
void Marcador::setUrl(std::string url) { this->url = url; }

std::string Marcador::getTitulo() { return titulo; }
void Marcador::setTitulo(std::string titulo) { this->titulo = titulo; }

void Marcador::setEtiquetas(std::list<std::string> etiquetas) { this->etiquetas = etiquetas; } 
std::list<std::string> Marcador::getEtiquetas() { return etiquetas; }

std::string Marcador::toString() {
	std::string str = "URL: " + url + "\nTitulo: " + titulo + "\nEtiquetas: ";
	for (std::string etiqueta : etiquetas) {
		str += etiqueta + " ";
	}
	return str;
}

void Marcador::guardar(std::fstream& strm) {
    strm << url << SEPARA_VALOR;
    strm << titulo << SEPARA_VALOR;

    strm << etiquetas.size() << SEPARA_VALOR;

    for (const auto& etiqueta : etiquetas) {
        strm << etiqueta << SEPARA_VALOR;
    }

    strm << SEPARA_REGISTRO;
}


Marcador* Marcador::recuperar(std::fstream& strm) {
    std::string tempUrl, tempTitulo;
    size_t numEtiquetas;

    if (!std::getline(strm, tempUrl, SEPARA_VALOR)) return nullptr;
    if (!std::getline(strm, tempTitulo, SEPARA_VALOR)) return nullptr;
    if (!(strm >> numEtiquetas))  return nullptr;
    strm.ignore(1); // Ignorar el separador

    etiquetas.clear();
    for (size_t i = 0; i < numEtiquetas; ++i) {
        std::string etiqueta;
        if (std::getline(strm, etiqueta, SEPARA_VALOR)) {
            etiquetas.push_back(etiqueta);
        }
        else {
            return nullptr;
        }
    }

    this->url = tempUrl;
    this->titulo = tempTitulo;

    return this;
}
