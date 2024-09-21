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

void SitioWeb::guardar(std::fstream& strm) {
	strm << url << SEPARA_VALOR;
	strm << dominio << SEPARA_VALOR;
	strm << titulo << SEPARA_REGISTRO;
}

SitioWeb* SitioWeb::recuperar(std::fstream& strm) {
    std::string urlTemp, dominioTemp, tituloTemp;

    if (!std::getline(strm, urlTemp, SEPARA_VALOR)) return nullptr;
    if (!std::getline(strm, dominioTemp, SEPARA_VALOR)) return nullptr;
    if (!std::getline(strm, tituloTemp, SEPARA_REGISTRO)) return nullptr;

    this->url = urlTemp;
    this->dominio = dominioTemp;
    this->titulo = tituloTemp;

    return this;
}
