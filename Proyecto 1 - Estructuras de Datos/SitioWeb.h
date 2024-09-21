#ifndef SITIOWEB_H
#define SITIOWEB_H
#include <string>
#include <fstream>
#include <iostream>

#define SEPARA_VALOR ','
#define SEPARA_REGISTRO '\n'

class SitioWeb {
private:
	std::string url;
	std::string dominio;
	std::string titulo;

public:
	SitioWeb();
	SitioWeb(std::string, std::string, std::string);

	std::string getUrl();
	void setUrl(std::string);

	std::string getDominio();
	void setDominio(std::string);

	std::string getTitulo();
	void setTitulo(std::string);
	
	std::string toString();

	//Persistencia de datos
	virtual void guardar(std::fstream&);
	SitioWeb* recuperar(std::fstream&);

};

#endif // !SITIOWEB_H





