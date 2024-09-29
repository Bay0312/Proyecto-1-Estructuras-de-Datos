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

	while (opcion != 10) {
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

		std::cout << "1.  Ir a un sitio web\n2.  Nueva Pestaña\n3.  Cerrar Pestaña Actual\n4.  Marcadores\n"
			<< "5.  Modo Incognito\n6.  Busqueda/Filtros\n7.  Configuración\n8.  Navegación con teclas\n"
			<< "9.  Sesión\n10. Salir\n\nIngrese una opción: ";

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

		case 6: menuBusqueda();
			break;

		case 7: cambiarConfiguracion();
			break;

		case 8: navegacionConTeclas();
			break;

		case 9:
			gestionarSesion();
			break;

		case 10:
			system("CLS");
			std::cout << "\nEl navegador se ha cerrado!\n";
			break;

		default:
			std::cout << "\nLa opción ingresada no existe. Intente nuevamente.\n";
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
		std::cout << "Precione las teclas Arriba/Abajo para navegar entre pestañas...\n";
		std::cout << "Precione las teclas Izquierda/Derecha para navegar entre sitios web...\n";
		std::cout << "Precione la tecla Esc para salir...\n";
		int a = _getch();

		if (a == 0 || a == 224) {
			a = _getch();

			switch (a) {
			case 72:
				navegador->avanzarEnTabs();
				break;
			case 80:
				navegador->retrocederEnTabs();

				break;
			case 75:
				navegador->retrocederEnHistorial();
				break;
			case 77:
				navegador->avanzarEnHistorial();
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
		std::cout << "---------Microsoft Edge---------\n\t < Pestaña " << navegador->numeroTab() << " >\n";
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

		case 3:
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
		std::cerr << "Error: Debes ingresar un número válido.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("PAUSE");
		return false;
	}
	return true;
}

void Menu::menuBusqueda() {
	int opcionBusqueda = 0;

	while (opcionBusqueda != 3) { 
		system("CLS");
		std::cout << "---------Búsqueda y Filtros---------\n\n";
		std::cout << "1. Filtrar sitios por letra en el URL\n2. Buscar sitio web por palabra clave\n3. Volver al menú principal\n\nIngrese una opción: ";

		if (!leerOpcion(opcionBusqueda)) { continue; }

		switch (opcionBusqueda) {
		case 1:
			filtrarSitiosPorLetra(); 
			break;

		case 2:
			buscarSitioPorPalabra();
			break;

		case 3:
			return; 

		default:
			std::cout << "\nLa opción ingresada no existe. Intente nuevamente.\n";
			system("PAUSE");
			break;
		}
	}
}


void Menu::gestionarSesion() {
	int opcionSesion = 0;

	while (opcionSesion != 3) {
		system("CLS");
		std::cout << "---------Gestionar Sesión---------\n\n";
		std::cout << "1. Exportar Sesión (Guardar datos)\n2. Importar Sesión (Recuperar datos)\n3. Volver al menú principal\n\nIngrese una opción: ";

		if (!leerOpcion(opcionSesion)) { continue; }

		switch (opcionSesion) {
		case 1:
			guardarSesion(); 
			std::cout << "Sesión guardada exitosamente.\n";
			system("PAUSE");
			break;

		case 2:
			recuperarSesion();
			std::cout << "Sesión restaurada exitosamente.\n";
			system("PAUSE");
			break;

		case 3:
			return; 

		default:
			std::cout << "\nLa opción ingresada no existe. Intente nuevamente.\n";
			system("PAUSE");
			break;
		}
	}
}

void Menu::filtrarSitiosPorLetra() {
	char letra;
	std::cout << "Ingrese la letra por la cual desea filtrar los sitios: ";
	std::cin >> letra;

	bool encontrado = false;

	for (Tab* tab : navegador->getTabs()) {
		SitioWeb* sitio = tab->getSitioActual();
		if (sitio != nullptr && sitio->getUrl().find(tolower(letra)) != std::string::npos) {
			std::cout << "Sitio encontrado: " << sitio->getTitulo() << " | " << sitio->getUrl() << "\n";
			encontrado = true;
		}
	}

	if (!encontrado) {
		std::cout << "No se encontraron sitios con la letra '" << letra << "' en el URL.\n";
	}
	system("PAUSE");
}

void Menu::buscarSitioPorPalabra() {
	std::string palabraClave;
	std::cout << "Ingrese la palabra clave para buscar en el URL: ";
	std::cin >> palabraClave;

	bool encontrado = false;

	auto& tabs = navegador->gettTabs();
	for (auto it = tabs.begin(); it != tabs.end(); ++it) {
		Tab* tab = *it;
		if (tab != nullptr) {
			SitioWeb* sitio = tab->getSitioActual();
			if (sitio != nullptr && sitio->getUrl().find(palabraClave) != std::string::npos) {
				navegador->setTabActual(it);
				std::cout << "Sitio encontrado: " << sitio->getTitulo() << " | " << sitio->getUrl() << "\n";
				encontrado = true;
				break;
			}
		}
	}

	if (!encontrado) {
		std::cout << "No se encontró ningún sitio web con la palabra clave '" << palabraClave << "' en el URL.\n";
	}
	system("PAUSE");
}




void Menu::guardarSesion() {
	std::ofstream outFile("sesion_guardada.bin", std::ios::binary);
	if (!outFile) {
		std::cerr << "Error al abrir el archivo para guardar la sesión.\n";
		return;
	}

	navegador->guardar(outFile); 
	outFile.close();

	std::cout << "La sesión se ha guardado exitosamente.\n";
}

void Menu::recuperarSesion() {
	std::ifstream inFile("sesion_guardada.bin", std::ios::binary);
	if (!inFile) {
		std::cerr << "No se encontró ninguna sesión guardada.\n";
		return;
	}

	//delete navegador;  
	navegador = new Navegador();
	navegador->recuperar(inFile);
	inFile.close();

	std::cout << "La sesión anterior se ha recuperado exitosamente.\n";
}


