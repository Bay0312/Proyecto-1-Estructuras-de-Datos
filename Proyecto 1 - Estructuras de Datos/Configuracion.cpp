#include "Configuracion.h"

Configuracion* Configuracion::instancia = nullptr;

Configuracion::Configuracion() : tiempoExpiracionHistorial{ 120 }, maximoSitiosHistorial{ 5 } {} //Por defecto 2 minutos y 5 sitios
Configuracion::Configuracion(int tiempo, int cantidad): tiempoExpiracionHistorial{ tiempo }, maximoSitiosHistorial{ cantidad } {}

Configuracion::~Configuracion() {
	if (instancia != nullptr) {
		delete instancia;
		instancia = nullptr;
	}
}

Configuracion& Configuracion::getInstancia() {
	if (instancia == nullptr) {
		instancia = new Configuracion();
	}
	return *instancia;
}

std::chrono::duration<int> Configuracion::getTiempoExpiracionHistorial() { return tiempoExpiracionHistorial; }
void Configuracion::setTiempoExpiracionHistorial(std::chrono::duration<int> tiempo) { tiempoExpiracionHistorial = tiempo; }

int Configuracion::getMaximoSitiosHistorial() { return maximoSitiosHistorial; }
void Configuracion::setMaximoSitiosHistorial(int cantidad) { maximoSitiosHistorial = cantidad; }

std::string Configuracion::toString() {
	return "Tiempo de expiracion del historial: " + std::to_string(tiempoExpiracionHistorial.count()) + " minutos\nMaximo de sitios en el historial: " + std::to_string(maximoSitiosHistorial);
}


