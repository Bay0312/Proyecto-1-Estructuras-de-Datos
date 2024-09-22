#include "SitioWeb.h"

SitioWeb::SitioWeb() : url{ "" }, dominio{ "" }, titulo { "" } {}
SitioWeb::SitioWeb(std::string url, std::string dominio, std::string titulo) : url{ url }, dominio{ dominio }, titulo{ titulo } {}


std::string SitioWeb::getUrl() { return url; }
void SitioWeb::setUrl(std::string url) { this->url = url; }

std::string SitioWeb::getTitulo() { return titulo; }
void SitioWeb::setTitulo(std::string titulo) { this->titulo = titulo; }

std::string SitioWeb::getDominio() { return dominio; }
void SitioWeb::setDominio(std::string dominio) { this->dominio = dominio; }

std::string SitioWeb::toString() { return "URL: " + url + "\nTitulo: " + titulo + "\nDominio: " + dominio; }

void SitioWeb::guardar(std::ofstream& out) {
    size_t sizeUrl = url.size();
    size_t sizeDominio = dominio.size();
    size_t sizeTitulo = titulo.size();

    out.write(reinterpret_cast<char*>(&sizeUrl), sizeof(sizeUrl));
    out.write(url.data(), sizeUrl);

    out.write(reinterpret_cast<char*>(&sizeDominio), sizeof(sizeDominio));
    out.write(dominio.data(), sizeDominio);

    out.write(reinterpret_cast<char*>(&sizeTitulo), sizeof(sizeTitulo));
    out.write(titulo.data(), sizeTitulo);
}

SitioWeb* SitioWeb::recuperar(std::ifstream& in) {
    size_t sizeUrl, sizeDominio, sizeTitulo;
    std::string tempUrl, tempDominio, tempTitulo;

    in.read(reinterpret_cast<char*>(&sizeUrl), sizeof(sizeUrl));
    tempUrl.resize(sizeUrl);
    in.read(&tempUrl[0], sizeUrl);

    in.read(reinterpret_cast<char*>(&sizeDominio), sizeof(sizeDominio));
    tempDominio.resize(sizeDominio);
    in.read(&tempDominio[0], sizeDominio);

    in.read(reinterpret_cast<char*>(&sizeTitulo), sizeof(sizeTitulo));
    tempTitulo.resize(sizeTitulo);
    in.read(&tempTitulo[0], sizeTitulo);

    this->url = tempUrl;
    this->dominio = tempDominio;
    this->titulo = tempTitulo;

    return this;
}
