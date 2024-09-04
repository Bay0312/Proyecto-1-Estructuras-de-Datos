#include "Menu.h"

Menu::Menu() : navegador{ new Navegador }, sitiosDisponibles { std::map<std::string, SitioWeb*>()} {
	cargarSitios("sitios.csv");
}
Menu::~Menu() { delete navegador; }

void Menu::menuPrincipal() {
	int opcion = 0;

	while (opcion != 8) {
		system("CLS");
		std::cout << "---------Microsoft Edge---------\n\t < Pestaña " << navegador->numeroTab() << " >\n";
		if (navegador->getModoIncognitoTabActual()) std::cout << "\t(Estas Viajando en Modo Incognito)\n\n";
		else std::cout << "\n\n";

		if (navegador->getSitioActual() == nullptr) {
			std::cout << "Trata de acceder a un sitio web!\n\n";
		}
		else {
			std::cout << " | " << navegador->getSitioActual()->getTitulo() << " |\n";
			std::cout << " | " << navegador->getSitioActual()->getUrl() << " |\n\n";
		}

		std::cout << "1. Ir a un sitio web\n2. Nueva Pestaña\n3. Cerrar Pestaña Actual\n4. Marcadores\n5. Modo Incognito\n6. Busqueda/Filtros\n7. Configuración\n8. Salir\n\nIngrese una opcion: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1: irSitioWeb();
			break;

		case 2: navegador->nuevaTab();
			break;

		case 3: navegador->cerrarTab();
			break;

		case 4: //Marcadores
			break;

		case 5: navegador->cambiarModoIncognitoTabActual();
			break;

		case 6: //Busqueda/Filtros
			break;

		case 7: cambiarConfiguracion();
			break;

		case 8:
			system("CLS");
			std::cout << "\nEl navegador se ha cerrado!\n";
			break;

		case 9:
			navegador->avanzarEnHistorial();
			break;

		case 10:
			navegador->retrocederEnHistorial();
			break;

		case 11:
			navegador->avanzarEnTabs();
			break;

		case 12:
			navegador->retrocederEnTabs();
			break;

		default: std::cout << "\nLa opcion ingresada no existe. Intente nuevamente.\n";
			system("PAUSE");
			break;
		}
	}
}


void Menu::irSitioWeb() {
	std::string url;
	std::cout << "Ingrese la URL del sitio web: ";
	std::cin >> url;
	navegador->irSitio(traeSitioWeb(url));
}

SitioWeb* Menu::traeSitioWeb(std::string url) {
	if (sitiosDisponibles.find(url) != sitiosDisponibles.end()) {
		return sitiosDisponibles[url];
	}
	return nullptr;
}

void Menu::cargarSitios(std::string nombreArchivo) {
	std::ifstream archivo(nombreArchivo);

	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
		return;
	}

	std::string linea;
	while (std::getline(archivo, linea)) {
		std::istringstream ss(linea);
		std::string url, dominio, titulo;

		if (std::getline(ss, url, ',') && std::getline(ss, dominio, ',') && std::getline(ss, titulo)) {
			sitiosDisponibles[url] = new SitioWeb(url, dominio, titulo);
		}
	}
	archivo.close();
}

void Menu::cambiarConfiguracion() {
	int opcion = 0, aux = 0;
	while (opcion != 3) {

		system("CLS");
		std::cout << "---------Microsoft Edge---------\n\t < Pestaña " << navegador->numeroTab() << " >\n";
		if (navegador->getModoIncognitoTabActual()) std::cout << "\t(Estas Viajando en Modo Incognito)\n\n";
		else std::cout << "\n\n";

		Configuracion& configuracion = Configuracion::getInstancia();

		std::cout << "----------------Configuracion Actual----------------\n";
		std::cout << "Tiempo de Expiracion del Historial: " << configuracion.getTiempoExpiracionHistorial().count() << " segundos\n";
		std::cout << "Maximo de Sitios en el Historial: " << configuracion.getMaximoSitiosHistorial() << "\n";
		std::cout << "----------------------------------------------------\n\n";

		std::cout << "1. Cambiar el tiempo de expiracion del historial\n2. Cambiar la cantidad maxima de sitios que guarda el historial\n3. Volver\n\nIngrese una opcion: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			std::cout << "Ingrese el nuevo tiempo de expiracion del historial en segundos: ";
			std::cin >> aux;
			configuracion.setTiempoExpiracionHistorial(std::chrono::seconds(aux));
			break;

		case 2:
			std::cout << "Ingrese la nueva cantidad maxima de sitios que guarda el historial: ";
			std::cin >> aux;
			configuracion.setMaximoSitiosHistorial(aux);
			break;

		case 3: //No se hace nada
			break;
		default:
			std::cout << "\nLa opcion ingresada no existe. Intente nuevamente.\n";
			system("PAUSE");
			break;
		}

	}
}