#ifndef TAB_H
#define TAB_H
#include "Historial.h"

class Tab {
private:
	std::string nombre;
	Historial* historial;
	std::deque<SitioWeb*>::iterator iterActual;
	bool modoIncognito;
public:
	Tab();
	~Tab();
	std::string getNombre();
	SitioWeb* getSitioActual();

	void irSitio(SitioWeb*);
	void avanzarEnHistorial();
	void retrocederEnHistorial();
	SitioWeb* getActual();
	SitioWeb* getVisitadosPorPos(int);
	std::string toString();


	//Persistencia de datos
	void guardar(std::ofstream& out);
	Tab* recuperar(std::ifstream& in);

	//void cambiaModoIncognito();

};

#endif // !TAB_H


