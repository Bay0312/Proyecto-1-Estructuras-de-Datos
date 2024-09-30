#ifndef HISTORIAL_H
#define HISTORIAL_H
#include "SitioWeb.h"
#include "Configuracion.h"
#include <deque>
#include <fstream>


class Historial {
private:
	std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>> visitados; //libreria de deque ya contiene -> <utility> -> std::pair
	std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>>::iterator iterActual; //Recorre historial
	Configuracion& configuracion;

public:
	Historial();
	~Historial();

	std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>>& getVisitados();
	std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>>::iterator getIteradorActual();
	
	void AsignaInicioIteradorActual();
	
	bool iterApuntaInvalido();
	void borraDeInicioAIter();
	SitioWeb* getSitioIterActual();

	void retrocedeIter();
	void avanzaIter();

	void agregarSitio(SitioWeb*);
	int limpiarHistorial();
	bool cambiaTamanioHistorial();
	std::string toString();

	void guardar(std::ofstream& out);
	Historial* recuperar(std::ifstream& in);
};

#endif // !HISTORIAL_H





