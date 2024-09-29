#ifndef SITIOWEB_H
#define SITIOWEB_H
#include <string>
#include <fstream>

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

	void guardar(std::ofstream& out);
	SitioWeb* recuperar(std::ifstream& in);

};

#endif // !SITIOWEB_H





