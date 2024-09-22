#include "Historial.h"

Historial::Historial() : visitados{ std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>>() }, configuracion{ Configuracion::getInstancia() }, iterActual{ visitados.end() } {}
Historial::~Historial() {
	for (auto sitio : visitados) {
		delete sitio.first;
	}
}
std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>>& Historial::getVisitados() {
	return visitados;
}

std::deque<std::pair<SitioWeb*, std::chrono::steady_clock::time_point>>::iterator Historial::getIteradorActual() {
	return iterActual;
}

void Historial::AsignaInicioIteradorActual() { iterActual = visitados.begin(); } //Asigna inicio a iter (.begin())
bool Historial::iterApuntaInvalido() { return iterActual == visitados.end(); }

void Historial::borraDeInicioAIter(){
	if (iterActual != visitados.begin()) {
		for (auto it = visitados.begin(); it != iterActual; ++it) { //Se recorre desde el inicio hasta donde estamos con el iterActual
			delete (*it).first; //Se borra el puntero
		}
		visitados.erase(visitados.begin(), iterActual); //Se liberan los espacios de lo borrado, y se desplazan los demas elemtos del deque
	}
}

SitioWeb* Historial::getSitioIterActual() { 
	if (iterActual == visitados.end()) return nullptr;
	return (*iterActual).first; 
}

//Retroceder y avanzar estan invertidos con el "++" y "--" porque se inserta al frente en el historial.
void Historial::retrocedeIter() { 
	if (iterActual != visitados.end() -1) ++iterActual; 

}
void Historial::avanzaIter() { if (iterActual != visitados.begin()) --iterActual; }

void Historial::agregarSitio(SitioWeb* sitio) {
	//cambiaTamanioHistorial(); //Antes de ingresar un nuevo sitio activamos esta funcion por si la cantidad de entradas fue cambiada a una mas baja.
	if (visitados.size() == configuracion.getMaximoSitiosHistorial()) {
		delete visitados.back().first;
		visitados.pop_back();
	}
	visitados.push_front({ sitio, std::chrono::steady_clock::now() }); //Inserta al frente del deque el sitio y el tiempo actual
	iterActual = visitados.begin();
}


int Historial::limpiarHistorial(){
	//cambiaTamanioHistorial();
	auto ahora = std::chrono::steady_clock::now();
	int cant = 0, estado = 0;

	for (auto sitio : visitados) {
		if ((ahora - sitio.second) > configuracion.getTiempoExpiracionHistorial()) {
			cant++; //Cuenta cuantos sitios ya superaron el tiempo de expiracion
		}
	}
	//Elimina los sitios que ya superaron el tiempo de expiracion. Como en el deque se inserta desde el frente, los elementos mas viejos siempre estan en el back()
	for (int i = 0; i < cant; i++) {
		if (estado != 1) { // Si esto ya es 1 significa que iter fue borrado, si se trata de evaluar iter como en la siguiente condicional va a haber un error.
			if (iterActual == visitados.end() - 1) {
				estado = 1;
			}
		}
		delete visitados.back().first;
		visitados.pop_back();
	}
	int tam = visitados.size();

	//Si ya no hay sitios en el historial y se borro a lo que apunta el iterador del Tab (estado == 1), entonces estado = 2 para indicar esto.
	if ((tam == 0) && (estado == 1)) estado = 2;
	

	switch (estado) {
	case 1: iterActual = visitados.end() - 1; //Aun hay elementos, se asigna el primero que fue insertado.
		break;
	case 2: iterActual = visitados.end(); //Ya no hay elementos, se asigna un espacio invalido al iterador
	default:
		break;
	}

	
	return estado;
}

bool Historial::cambiaTamanioHistorial() { //Por si la cantidad de entradas del historial es reducida a una menor que la cantidad que ya contiene
	int cantidadConf = (Configuracion::getInstancia()).getMaximoSitiosHistorial();
	bool iterEstaba = false;
	if (visitados.size() > cantidadConf) {
		while (visitados.size() != cantidadConf) {
			if (!iterEstaba) { //Verificamos si no se borro lo que contenia el iter, asi no se genera un problema de acceso.
				if (iterActual == visitados.end() - 1) {
					iterEstaba = true;
				}
			}
			visitados.pop_back();
		}
	}

	if (iterEstaba) iterActual = visitados.end() - 1;

	return iterEstaba;
}

std::string Historial::toString() {
	std::string str = "";
	for (auto sitio : visitados) {
		str += sitio.first->toString() + "\n";
	}
	return str;
}



