#ifndef SITIOWEB_H
#define SITIOWEB_H
#include <string>

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

};

#endif // !SITIOWEB_H





