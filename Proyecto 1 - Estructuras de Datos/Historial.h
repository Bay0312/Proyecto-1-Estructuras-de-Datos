#ifndef HISTORIAL_H
#define HISTORIAL_H
#include "SitioWeb.h"
#include <deque>


class Historial {
private:
	std::deque<SitioWeb*> visitados;

public:
	Historial();
	~Historial();

	std::deque<SitioWeb*>& getVisitados();
	SitioWeb* getVisitadosPorPos(int);

	void agregarSitio(SitioWeb*);
	std::string toString();


	//Persistencia de datos
	void guardar(std::ofstream& out);
	Historial* recuperar(std::ifstream& in);

};

#endif // !HISTORIAL_H





