#ifndef TAB_H
#define TAB_H
#include "Historial.h"

class Tab {
private:
	std::string nombre;
	Historial* historial;
	SitioWeb* abierto; //Este representa el sitio web que este abierto. (Viajar en el historial no hace que visitemos esas paginas, solo es visualizarlas)
	bool modoIncognito;

public:
	Tab();
	~Tab();
	std::string getNombre();
	SitioWeb* getSitioAbierto();
	void setSitioAbierto(SitioWeb*);
	SitioWeb* getSitioActual();
	bool getModoIncognito();
	void cambiaModoIncognito();

	void irSitio(SitioWeb*);
	void avanzarEnHistorial();
	void retrocederEnHistorial();
	std::string toString();
};

#endif // !TAB_H


