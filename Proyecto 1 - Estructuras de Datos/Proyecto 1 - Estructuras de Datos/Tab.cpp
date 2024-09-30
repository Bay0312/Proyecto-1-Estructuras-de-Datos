#include "Tab.h"

Tab::Tab() : historial{ new Historial() }, nombre{ "Tab Nuevo" }, abierto{ nullptr }, modoIncognito{ false } {}
Tab::~Tab() { 
	delete historial; 
	if(abierto != nullptr) delete abierto;
}


std::string Tab::getNombre() {
	return nombre;
}

SitioWeb* Tab::getSitioAbierto() { return abierto; }

void Tab::setSitioAbierto(SitioWeb* abre){ 
	delete abierto;
	abierto = abre;
}

void Tab::irSitio(SitioWeb* sitio) {
	historial->cambiaTamanioHistorial();

	if (abierto != nullptr) {
		delete abierto;
	}

	abierto = sitio;
	

	if (!modoIncognito) { //Unicamente guardamos en historial si no estamos en modo incognito
		if (historial->limpiarHistorial() == 1) { //Nos aseguramos de quitar las paginas expiradas si es que hay.
			//Si se eliminó la pagina en la que estaba el iterador cuando retrocedimos, entonces se asigna al principio al momento de ir a una nueva para no perder todos los datos
			historial->AsignaInicioIteradorActual();
		}
		SitioWeb* nuevo = nullptr;
		try {
			nuevo = new SitioWeb(sitio->getUrl(), sitio->getDominio(), sitio->getTitulo()); //Nuevo puntero a SitioWeb para guardarlo en historial (Se crea uno nuevo para evitar problemas al borrar el historial)
		}
		catch (const std::bad_alloc& e) {
			std::cerr << "Error de memoria al intentar crear el SitioWeb para historial: " << e.what() << std::endl;
			return;
		}
		

		if (historial->getVisitados().size() != 0) {
			//Si no estamos en el primer sitio significa que volvimos, por lo que, si tratamos de ir a un nuevo sitio, borramos los sitios que estan adelante, igual que lo hace un navegador real.
			historial->borraDeInicioAIter();
		}

		historial->agregarSitio(nuevo);
	}

	
}

void Tab::avanzarEnHistorial() {
	if (historial->cambiaTamanioHistorial()) return;
	
	if (!historial->iterApuntaInvalido()) { //Se hace esta verificacion fuera por si el iterActual llegara a ser invalido
		if (historial->limpiarHistorial() != 0) return;  //Se borro el iter, ya fuera por que expiro la pagina o se cambio el tamaño a uno mas bajo, por lo tanto, se activa return, pues estamos al final de la lista, y no hace falta avanzar tras la limpieza del historial
		historial->avanzaIter();
	}

}
//Retroceder y avanzar estan invertidos con el "++" y "--" porque se inserta al frente en el historial.
void Tab::retrocederEnHistorial() { 
	if (historial->cambiaTamanioHistorial()) return; 
	if (!historial->iterApuntaInvalido()) { //Se hace esta verificacion fuera por si el iterActual llegara a ser invalido
		if (historial->limpiarHistorial() != 0) return; //Se borran paginas expiradas del historial
		historial->retrocedeIter();
	}
}

SitioWeb* Tab::getSitioActual() {
	if (modoIncognito) {
		return abierto;
	}

	SitioWeb* aux = historial->getSitioIterActual();
	if (aux != nullptr) {
		return aux;
	}
	return abierto;
}

bool Tab::getModoIncognito() { return modoIncognito; }

void Tab::cambiaModoIncognito(){ modoIncognito = !modoIncognito; }

std::string Tab::toString() {
	return historial->toString();
}

void Tab::guardar(std::ofstream& out) {
	size_t nombreLength = nombre.size();
	out.write(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength));
	out.write(nombre.c_str(), nombreLength);

	out.write(reinterpret_cast<char*>(&modoIncognito), sizeof(modoIncognito));

	bool tieneSitioAbierto = (abierto != nullptr);
	out.write(reinterpret_cast<char*>(&tieneSitioAbierto), sizeof(tieneSitioAbierto));
	if (tieneSitioAbierto) {
		abierto->guardar(out);
	}
	historial->guardar(out);
}

Tab* Tab::recuperar(std::ifstream& in) {
	size_t nombreLength;
	in.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength));
	nombre.resize(nombreLength);
	in.read(&nombre[0], nombreLength);

	in.read(reinterpret_cast<char*>(&modoIncognito), sizeof(modoIncognito));

	bool tieneSitioAbierto;
	in.read(reinterpret_cast<char*>(&tieneSitioAbierto), sizeof(tieneSitioAbierto));
	if (tieneSitioAbierto) {
		abierto = new SitioWeb();
		abierto->recuperar(in);
	}
	else {
		abierto = nullptr;
	}
	historial->recuperar(in);
	return this;
}
