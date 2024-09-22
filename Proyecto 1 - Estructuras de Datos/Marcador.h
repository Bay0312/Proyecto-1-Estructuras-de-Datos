#ifndef MARCADOR_H
#define MARCADOR_H
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <sstream>
#include <list>
#include <fstream>

#define SEPARA_VALOR ','
#define SEPARA_REGISTRO '\n'

class Marcador {
private:
	std::string url;
	std::string titulo;
	std::list<std::string> etiquetas;

public:
	Marcador();
	Marcador(std::string, std::string, std::list<std::string>);

	std::string getUrl();
	std::string getTitulo();
	std::list<std::string> getEtiquetas();

	void setUrl(std::string);
	void setTitulo(std::string);
	void setEtiquetas(std::list<std::string>);

	std::string toString();


	//Persistencia de datos
	void guardar(std::ofstream& out);
	Marcador* recuperar(std::ifstream& in);

};

#endif // !MARCADOR_H





