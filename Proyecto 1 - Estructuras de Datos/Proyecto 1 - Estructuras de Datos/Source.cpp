#include <iostream>
#include "Menu.h"


int main() {
	setlocale(LC_CTYPE, "Spanish"); //Define el español como lenguaje del programa, permitiendo leer letras tildadas, "ñ", "¿" y demás
	Menu* menu = nullptr;
	
	try {
		menu = new Menu();
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Error de memoria al intentar crear el menú: " << e.what() << std::endl;
		/*Con este try y catch logramos mantener control general de todas las creaciones de objetos con new que haya en el constructor del Menu.
		Esto significa que tambien cubre todos los objetos que se crean en cascada a partir de la creacion del Menu, como el navegador, los tabs,
		la configuracion o los sitios disponibles. Por supuesto, esto es conveniente dado que si no es posible crear el menu y todos esos objetos, no tendria
		sentido el programa, ya que no contariamos con elementos fundamentales de su funcionamiento. Por otro lado, esto simplifica el hecho de ir a cada
		asignacion con new en todos los constructores de las clases y poner un try y catch en cada uno.
		*/
	}
	
	if (menu != nullptr) { 
		menu->menuPrincipal();
		delete menu; 
	}	
 
	_CrtDumpMemoryLeaks(); //Muestra en consola si hay fugas de memoria al finalizar el programa
	
	return 0;
}

/*
Recursos:

https://en.cppreference.com/w/cpp/container/list

https://en.cppreference.com/w/cpp/container/deque

https://en.cppreference.com/w/cpp/container/map


*/