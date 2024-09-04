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
