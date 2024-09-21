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
	virtual void guardar(std::fstream&);
	virtual Historial* recuperar(std::fstream&);

};

#endif // !HISTORIAL_H





