#include "Menu.h"

Menu::Menu() : navegador{ new Navegador }, sitiosDisponibles { std::map<std::string, SitioWeb*>()} {
	cargarSitios("sitios.csv");
}
Menu::~Menu() { 
	delete navegador; 
	for (auto& sitio : sitiosDisponibles) {
		delete sitio.second;
	}
}

void Menu::menuPrincipal() {
	int opcion = 0;

	while (opcion != 9) {
		system("CLS");
		std::cout << "---------Microsoft Edge---------\n\t < Pesta�a " << navegador->numeroTab() << " >\n";
		if (navegador->getModoIncognitoTabActual()) std::cout << "\t(Estas Viajando en Modo Incognito)\n\n";
		else std::cout << "\n\n";

		if (navegador->getSitioActual() == nullptr) {
			std::cout << "Trata de acceder a un sitio web!\n\n";
		}
		else {
			std::cout << " | " << navegador->getSitioActual()->getTitulo() << " |\n";
			std::cout << " | " << navegador->getSitioActual()->getUrl() << " |\n\n";
		}

		std::cout << "1. Ir a un sitio web\n2. Nueva Pesta�a\n3. Cerrar Pesta�a Actual\n4. Marcadores\n5. Modo Incognito\n6. Busqueda/Filtros\n7. Configuraci�n\n8. Navegaci�n con teclas\n9. Salir\n\nIngrese una opcion: ";
		if (!leerOpcion(opcion)) { continue; }

		switch (opcion) {
		case 1: irSitioWeb();
			break;

		case 2: navegador->nuevaTab();
			break;

		case 3: navegador->cerrarTab();
			break;

		case 4: menuMarcadores();
			break;

		case 5: navegador->cambiarModoIncognitoTabActual();
			break;

		case 6: //Busqueda/Filtros
			break;

		case 7: cambiarConfiguracion();
			break;

		case 8:
			navegacionConTeclas();
			break;

		case 9:
			system("CLS");
			std::cout << "\nEl navegador se ha cerrado!\n";
			break;

		default: std::cout << "\nLa opcion ingresada no existe. Intente nuevamente.\n";
			system("PAUSE");
			break;
		}
	}
}

void Menu::menuMarcadores() {
	int opcion = 0;
	std::string titulo;

	while (opcion != 4) {
		system("CLS");
		std::cout << "---------Microsoft Edge---------\n\t < Pesta�a " << navegador->numeroTab() << " >\n";
		if (navegador->getModoIncognitoTabActual()) std::cout << "\t(Estas Viajando en Modo Incognito)\n\n";
		else std::cout << "\n\n";

		if (navegador->getSitioActual() == nullptr) {
			std::cout << "Trata de acceder a un sitio web!\n\n";
		}
		else {
			std::cout << " | " << navegador->getSitioActual()->getTitulo() << " |\n";
			std::cout << " | " << navegador->getSitioActual()->getUrl() << " |\n\n";
		}

		std::cout << "---------Marcadores---------\n";

		std::cout << "1. Agregar sitio actual como marcador. \n2. Agregar tag. \n3. Buscar marcadores. \n4. Salir \n\nIngrese una opcion: "; std::cin >> opcion;

		switch (opcion) {
		case 1:
			system("CLS");
			navegador->agregarMarcador(navegador->getSitioActual());
			std::cout << navegador->toStringMarcadores();
			system("pause");
			break;

		case 2:
			system("CLS");
			navegador->agregarEtiquetas(navegador->getSitioActual());
			std::cout << navegador->toStringMarcadores();
			system("pause");
			break;

		case 3:
			system("CLS");
			std::cout << "---------Buscar Marcador---------\n\n";
			std::cout << "Ingrese el titulo del marcador que desea buscar: "; std::cin >> titulo;

			navegador->buscarMarcadores(titulo);
			system("pause");

			break;

		default: break;
		}

	}
}

void Menu::navegacionConTeclas() {
	while (true) {
		system("CLS");
		std::cout << "---------Microsoft Edge---------\n\t < Pesta�a " << navegador->numeroTab() << " >\n";
		if (navegador->getModoIncognitoTabActual()) std::cout << "\t(Estas Viajando en Modo Incognito)\n\n";
		else std::cout << "\n\n";

		if (navegador->getSitioActual() == nullptr) {
			std::cout << "Trata de acceder a un sitio web!\n\n";
		}
		else {
			std::cout << " | " << navegador->getSitioActual()->getTitulo() << " |\n";
			std::cout << " | " << navegador->getSitioActual()->getUrl() << " |\n\n";
		}

		int a = _getch();

		if (a == 0 || a == 224) {
			a = _getch();

			switch (a) {
			case 72:
				std::cout << "You pressed the UP arrow key.\n";
				navegador->avanzarEnTabs();
				system("pause");
				break;
			case 80:
				std::cout << "You pressed the DOWN arrow key.\n";
				navegador->retrocederEnTabs();
				system("pause");
				break;
			case 75:
				std::cout << "You pressed the LEFT arrow key.\n";
				navegador->retrocederEnHistorial();
				system("pause");
				break;
			case 77:
				std::cout << "You pressed the RIGHT arrow key.\n";
				navegador->avanzarEnHistorial();
				system("pause");
				break;
			default:
				std::cout << "Unknown special key pressed.\n";
			}
		}
		else if (a == 27) {
			std::cout << "Exiting...\n";
			break;
		}
		else {
			std::cout << "You pressed a non-arrow key: " << a << "\n";
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
		std::cout << "---------Microsoft Edge---------\n\t < Pesta�a " << navegador->numeroTab() << " >\n";
		if (navegador->getModoIncognitoTabActual()) std::cout << "\t(Estas Viajando en Modo Incognito)\n\n";
		else std::cout << "\n\n";

		Configuracion& configuracion = Configuracion::getInstancia();

		std::cout << "----------------Configuracion Actual----------------\n";
		std::cout << "Tiempo de Expiracion del Historial: " << configuracion.getTiempoExpiracionHistorial().count() << " segundos\n";
		std::cout << "Maximo de Sitios en el Historial: " << configuracion.getMaximoSitiosHistorial() << "\n";
		std::cout << "----------------------------------------------------\n\n";

	
		std::cout << "1. Cambiar el tiempo de expiracion del historial\n2. Cambiar la cantidad maxima de sitios que guarda el historial\n3. Volver\n\nIngrese una opcion: ";
		if (!leerOpcion(opcion)) { continue; }


		switch (opcion) {
		case 1:
			std::cout << "Ingrese el nuevo tiempo de expiracion del historial en segundos: ";
			if (!leerOpcion(aux)) { continue; }
			configuracion.setTiempoExpiracionHistorial(std::chrono::seconds(aux));
			break;

		case 2:
			std::cout << "Ingrese la nueva cantidad maxima de sitios que guarda el historial: ";
			if (!leerOpcion(aux)) { continue; }
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

bool Menu::leerOpcion(int& opcion) {
	if (!(std::cin >> opcion) || std::cin.peek() != '\n') {
		std::cerr << "Error: Debes ingresar un n�mero v�lido.\n";
		std::cin.clear();  // Limpia el estado de error
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar cualquier entrada incorrecta
		system("PAUSE");
		return false;
	}
	return true;
}

