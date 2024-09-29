#include "Marcador.h"

Marcador::Marcador() : url{ "" }, titulo{ "" }, etiquetas{ std::vector<std::string>() } {}
Marcador::Marcador(std::string url, std::string titulo, std::vector<std::string> etiquetas) : url{ url }, titulo{ titulo }, etiquetas{ etiquetas } {}

std::string Marcador::getUrl() { return url; }
void Marcador::setUrl(std::string url) { this->url = url; }

std::string Marcador::getTitulo() { return titulo; }
void Marcador::setTitulo(std::string titulo) { this->titulo = titulo; }

void Marcador::setEtiquetas(std::vector<std::string> etiquetas) { this->etiquetas = etiquetas; } 
std::vector<std::string> Marcador::getEtiquetas() { return etiquetas; }

std::string Marcador::toString() {
	std::string str = "URL: " + url + "\nTitulo: " + titulo + "\nEtiquetas: ";
	for (std::string etiqueta : etiquetas) {
		str += etiqueta + " ";
	}
	return str;
}

void Marcador::guardar(std::ofstream& out) {
    size_t sizeUrl = url.size();
    size_t sizeTitulo = titulo.size();
    size_t sizeEtiquetas = etiquetas.size();

    out.write(reinterpret_cast<char*>(&sizeUrl), sizeof(sizeUrl));
    out.write(url.data(), sizeUrl);

    out.write(reinterpret_cast<char*>(&sizeTitulo), sizeof(sizeTitulo));
    out.write(titulo.data(), sizeTitulo);

    out.write(reinterpret_cast<char*>(&sizeEtiquetas), sizeof(sizeEtiquetas));
    for (const auto& etiqueta : etiquetas) {
        size_t sizeEtiqueta = etiqueta.size();
        out.write(reinterpret_cast<char*>(&sizeEtiqueta), sizeof(sizeEtiqueta));
        out.write(etiqueta.data(), sizeEtiqueta);
    }
}

Marcador* Marcador::recuperar(std::ifstream& in) {
    size_t sizeUrl, sizeTitulo, sizeEtiquetas;
    std::string tempUrl, tempTitulo;

    in.read(reinterpret_cast<char*>(&sizeUrl), sizeof(sizeUrl));
    tempUrl.resize(sizeUrl);
    in.read(&tempUrl[0], sizeUrl);

    in.read(reinterpret_cast<char*>(&sizeTitulo), sizeof(sizeTitulo));
    tempTitulo.resize(sizeTitulo);
    in.read(&tempTitulo[0], sizeTitulo);

    in.read(reinterpret_cast<char*>(&sizeEtiquetas), sizeof(sizeEtiquetas));
    etiquetas.clear();
    for (size_t i = 0; i < sizeEtiquetas; ++i) {
        size_t sizeEtiqueta;
        std::string etiqueta;
        in.read(reinterpret_cast<char*>(&sizeEtiqueta), sizeof(sizeEtiqueta));
        etiqueta.resize(sizeEtiqueta);
        in.read(&etiqueta[0], sizeEtiqueta);
        etiquetas.push_back(etiqueta);
    }

    this->url = tempUrl;
    this->titulo = tempTitulo;

    return this;
}

