#ifndef CONFIGURACION_H
#define CONFIGURACION_H
#include <chrono>
#include <string>

class Configuracion { // Singleton para la configuracion del navegador
private:
    Configuracion();
	Configuracion(int, int);
    ~Configuracion();
	static Configuracion* instancia;
	std::chrono::duration<int> tiempoExpiracionHistorial;
	int maximoSitiosHistorial;
	

public:
	static Configuracion& getInstancia();
	std::chrono::duration<int> getTiempoExpiracionHistorial();
	void setTiempoExpiracionHistorial(std::chrono::duration<int>);
	int getMaximoSitiosHistorial();
	void setMaximoSitiosHistorial(int);

	std::string toString();

};

#endif // !CONFIGURACION_H
