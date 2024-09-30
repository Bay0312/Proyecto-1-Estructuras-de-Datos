#ifndef MARCADOR_H
#define MARCADOR_H
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <fstream>

class Marcador {
private:
	std::string url;
	std::string titulo;
	std::vector<std::string> etiquetas;

public:
	Marcador();
	Marcador(std::string, std::string, std::vector<std::string>);

	std::string getUrl();
	std::string getTitulo();
	std::vector<std::string> getEtiquetas();

	void setUrl(std::string);
	void setTitulo(std::string);
	void setEtiquetas(std::vector<std::string>);

	std::string toString();
	void guardar(std::ofstream& out);
	Marcador* recuperar(std::ifstream& in);
};

#endif // !MARCADOR_H





